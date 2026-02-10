#include <iostream>
#include <cassert>

enum class VehicleMode { ECO, SPORT, OFF_ROAD };

// ==========================================
// 1. INTERFACE (Contract)
// ==========================================
class IVehicleModeProvider {
public:
    virtual ~IVehicleModeProvider() = default;
    virtual VehicleMode getCurrentMode() const = 0;
};

// ==========================================
// 2. REAL MANAGER (Service)
// ==========================================
// Bây giờ nó là class bình thường, không phải Singleton
class VehicleModeManager : public IVehicleModeProvider {
private:
    VehicleMode m_currentMode = VehicleMode::SPORT;
public:
    VehicleMode getCurrentMode() const override {
        return m_currentMode;
    }
    // Các logic setMode, state machine... ở đây
};

// ==========================================
// 3. CRASH DETECTION SWC (Client)
// ==========================================
class CrashDetection_SWC {
private:
    // Dependency được lưu dưới dạng Interface Pointer
    IVehicleModeProvider* m_modeProvider;

public:
    // DEPENDENCY INJECTION (DI) via Constructor
    // "Ai muốn dùng tôi, hãy đưa cho tôi một người cung cấp chế độ xe."
    CrashDetection_SWC(IVehicleModeProvider* provider) : m_modeProvider(provider) {}

    void onCollisionDetected() {
        if (!m_modeProvider) return;

        std::cout << "[Crash] Collision detected!\n";
        
        // Gọi qua Interface (Decoupled)
        VehicleMode mode = m_modeProvider->getCurrentMode();
        
        std::cout << "[Crash] Logged Mode: " << (int)mode << "\n";
    }
};

// ==========================================
// 4. MOCK OBJECT (For Testing Only)
// ==========================================
class MockVehicleModeProvider : public IVehicleModeProvider {
private:
    VehicleMode m_fakeMode;
public:
    MockVehicleModeProvider(VehicleMode mode) : m_fakeMode(mode) {}

    // Hàm giả, luôn trả về giá trị ta muốn test
    VehicleMode getCurrentMode() const override {
        return m_fakeMode;
    }
};

// ==========================================
// 5. UNIT TEST RUNNER
// ==========================================
void test_CrashLogging_In_EcoMode() {
    std::cout << "Running Test: Crash in ECO Mode...\n";

    // 1. Arrange: Tạo môi trường giả (Mock trả về ECO)
    MockVehicleModeProvider mockEco(VehicleMode::ECO);
    
    // 2. Act: Tiêm Mock vào CrashDetection (Dependency Injection)
    CrashDetection_SWC crashSystem(&mockEco);
    
    // 3. Assert: Chạy thử logic
    // (Ở đây ta chỉ in ra, trong framework thật ta sẽ dùng assert)
    crashSystem.onCollisionDetected(); 
    
    std::cout << "Test Passed! (System logged 0 for ECO without needing real Manager)\n\n";
}

void test_CrashLogging_In_OffRoadMode() {
    std::cout << "Running Test: Crash in OFF_ROAD Mode...\n";

    // Dễ dàng tái sử dụng với kịch bản khác
    MockVehicleModeProvider mockOffRoad(VehicleMode::OFF_ROAD);
    CrashDetection_SWC crashSystem(&mockOffRoad);
    
    crashSystem.onCollisionDetected();
    
    std::cout << "Test Passed!\n";
}

int main() {
    test_CrashLogging_In_EcoMode();
    test_CrashLogging_In_OffRoadMode();
    return 0;
}
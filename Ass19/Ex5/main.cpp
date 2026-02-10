
/**
 * Observer Pattern
 */

#include <iostream>
#include <vector>
#include <algorithm> // Cho std::remove
#include <string>
#include <memory>


enum class VehicleMode {
    ECO,
    SPORT,
    OFF_ROAD,
};

// Observer Interface
class IObserver {
public:
    virtual ~IObserver() = default;

    // Hàm này sẽ được Manager gọi khi có biến
    virtual void onModeChanged(VehicleMode newMode) = 0;
};

// Đây là "Đài phát thanh". Nó giữ danh sách các thính giả.
class VehicleModeManager {
private:
    VehicleMode m_currentMode;
    
    // Danh sách các "đăng ký viên" (Observers)
    // Lưu con trỏ thô (Raw Pointer) vì Manager KHÔNG sở hữu Observers.
    // (Observers sống chết do Main quản lý).
    std::vector<IObserver*> m_observers;

public:
    VehicleModeManager() : m_currentMode(VehicleMode::ECO) {}

    // --- OBSERVER MANAGEMENT ---
    void attach(IObserver* observer) {
        m_observers.push_back(observer);
        std::cout << "[Manager] Observer attached.\n";
    }

    void detach(IObserver* observer) {
        // Xóa observer khỏi vector (Idiom Erase-Remove)
        m_observers.erase(
            std::remove(m_observers.begin(), m_observers.end(), observer),
            m_observers.end()
        );
        std::cout << "[Manager] Observer detached.\n";
    }

    // Hàm quan trọng nhất: Thông báo cho toàn bộ làng xóm
    void notify() {
        std::cout << "   >>> [Manager] Notifying all observers...\n";
        for (IObserver* obs : m_observers) {
            obs->onModeChanged(m_currentMode);
        }
    }

    // --- BUSINESS LOGIC ---
    // (Đây là nơi tích hợp logic State Pattern của Part 3)
    // Để ngắn gọn, mình giả lập việc đổi state thành công.
    void changeMode(VehicleMode newMode) {
        if (m_currentMode == newMode) return;

        std::cout << "\n[Manager] Switching State to " << (int)newMode << "...\n";
        m_currentMode = newMode;

        // SAU KHI ĐỔI TRẠNG THÁI THÀNH CÔNG -> GỌI NOTIFY
        notify();
    }
};


// SWC 1: Màn hình Taplo (Instrument Cluster)
class InstrumentCluster_SWC : public IObserver {
public:
    void onModeChanged(VehicleMode newMode) override {
        std::string icon;
        switch(newMode) {
            case VehicleMode::ECO: icon = "GREEN LEAF"; break;
            case VehicleMode::SPORT: icon = "RED FLAG"; break;
            case VehicleMode::OFF_ROAD: icon = "MOUNTAIN"; break;
        }
        std::cout << "      [Cluster Display] Update UI: Show icon [" << icon << "]\n";
    }
};

// SWC 2: Bộ điều khiển Động cơ (Engine Control)
class EngineControl_SWC : public IObserver {
public:
    void onModeChanged(VehicleMode newMode) override {
        switch(newMode) {
            case VehicleMode::ECO: 
                std::cout << "      [ECU] Map: Lean Burn (Save Fuel)\n"; 
                break;
            case VehicleMode::SPORT: 
                std::cout << "      [ECU] Map: Aggressive (Max Power)\n"; 
                break;
            case VehicleMode::OFF_ROAD: 
                std::cout << "      [ECU] Map: Low-End Torque (Traction)\n"; 
                break;
        }
    }
};


// SWC 3: Hệ thống treo khí nén (Air Suspension)
class Suspension_SWC : public IObserver {
public:
    void onModeChanged(VehicleMode newMode) override {
        if (newMode == VehicleMode::OFF_ROAD) {
            std::cout << "      [Suspension] Lifting Chassis +50mm.\n";
        } else if (newMode == VehicleMode::SPORT) {
            std::cout << "      [Suspension] Lowering Chassis -20mm.\n";
        } else {
            std::cout << "      [Suspension] Normal Height.\n";
        }
    }
};


int main() {
    // 1. Khởi tạo Manager (Subject)
    VehicleModeManager vehicleManager;

    // 2. Khởi tạo các SWC (Observers)
    InstrumentCluster_SWC cluster;
    EngineControl_SWC ecu;
    Suspension_SWC airSuspension;

    std::cout << "--- 1. System Bootup & Subscription ---\n";
    // Đăng ký nghe tin (Wiring)
    vehicleManager.attach(&cluster);
    vehicleManager.attach(&ecu);
    vehicleManager.attach(&airSuspension);

    std::cout << "\n--- 2. Driver switches to SPORT ---\n";
    // Giả lập việc Command Pattern gọi vào Manager
    vehicleManager.changeMode(VehicleMode::SPORT);
    // KẾT QUẢ: 3 dòng log từ 3 SWC sẽ hiện ra tự động.

    std::cout << "\n--- 3. Driver switches to OFF_ROAD ---\n";
    vehicleManager.changeMode(VehicleMode::OFF_ROAD);

    std::cout << "\n--- 4. Dynamic Detach ---\n";
    // Ví dụ: Hệ thống treo bị hỏng, không muốn nhận lệnh nữa
    vehicleManager.detach(&airSuspension);
    
    std::cout << "Switching to ECO (Suspension should remain silent)...\n";
    vehicleManager.changeMode(VehicleMode::ECO);

    return 0;
}

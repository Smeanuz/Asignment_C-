
/**
 * Command Pattern
 */

#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <string>

enum class VehicleMode {
    ECO,
    SPORT,
    OFF_ROAD,
};

class VehicleModeManager {
public:
    void requestEco() {
        std::cout << "   [Receiver] Processing ECO Request...\n";
        // (Logic chuyển State của Part 3 nằm ở đây)
    }

    void requestSport() {
        std::cout << "   [Receiver] Processing SPORT Request...\n";
        // (Logic chuyển State của Part 3 nằm ở đây)
    }

    void requestOffRoad() {
        std::cout << "   [Receiver] Processing OFF-ROAD Request...\n";
        // (Logic chuyển State của Part 3 nằm ở đây)
    }
};

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0; // Hàm duy nhất để kích hoạt lệnh
};

class ChangeModeCommand : public ICommand {
private:
    VehicleModeManager& m_manager; // Ai sẽ thực thi?
    VehicleMode m_targetMode;      // Thực thi cái gì?


// Lệnh chuyển đổi chế độ.
// Nó "gói" (encapsulate) mọi thứ cần thiết: Receiver + Tham số.
public:
    ChangeModeCommand(VehicleModeManager& mgr, VehicleMode mode)
        : m_manager(mgr), m_targetMode(mode) {}

    void execute() override {
        // Ánh xạ từ Enum sang hàm cụ thể của Receiver
        switch (m_targetMode) {
            case VehicleMode::ECO:      m_manager.requestEco(); break;
            case VehicleMode::SPORT:    m_manager.requestSport(); break;
            case VehicleMode::OFF_ROAD: m_manager.requestOffRoad(); break;
        }
    }
};


// Class này không biết logic chuyển đổi xe là gì.
class CAN_Parser {
private:
    // Hàng đợi chứa các con trỏ lệnh (Polymorphic)
    std::queue<std::unique_ptr<ICommand>> m_commandQueue;
    VehicleModeManager& m_targetSystem; // Tham chiếu đến hệ thống xe

public:
    CAN_Parser(VehicleModeManager& sys) : m_targetSystem(sys) {}

    // Giả lập nhận tín hiệu CAN từ đường dây vật lý
    void onCanMessageReceived(int canID, int data) {
        if (canID == 0x100) { // Ví dụ ID 0x100 là lệnh đổi Mode
            VehicleMode requestedMode;
            if (data == 1) requestedMode = VehicleMode::ECO;
            else if (data == 2) requestedMode = VehicleMode::SPORT;
            else if (data == 3) requestedMode = VehicleMode::OFF_ROAD;
            else return;

            std::cout << "[CAN Parser] Received ID 0x100 Data " << data << ". Queuing Command.\n";

            // TẠO COMMAND VÀ ĐẨY VÀO QUEUE
            auto cmd = std::make_unique<ChangeModeCommand>(m_targetSystem, requestedMode);
            m_commandQueue.push(std::move(cmd));
        }
    }

    // Hàm này được gọi bởi Main Loop của ECU
    void processQueue() {
        while (!m_commandQueue.empty()) {
            // Lấy lệnh ra
            auto cmd = std::move(m_commandQueue.front());
            m_commandQueue.pop();

            // THỰC THI (Late Binding)
            // CAN Parser không cần biết bên trong execute() làm gì
            cmd->execute(); 
        }
    }
};


int main() {
    // 1. Hệ thống lõi (Receiver)
    VehicleModeManager engineControlUnit;

    // 2. Hệ thống giao tiếp (Invoker)
    CAN_Parser canInterface(engineControlUnit);

    std::cout << "--- 1. CAN Bus Activity (Interrupts) ---\n";
    // Giả lập tín hiệu CAN đến dồn dập
    canInterface.onCanMessageReceived(0x100, 2); // Request Sport
    canInterface.onCanMessageReceived(0x100, 3); // Request OffRoad
    canInterface.onCanMessageReceived(0x100, 1); // Request Eco

    std::cout << "\n--- 2. Main Loop Processing (Cyclic Task) ---\n";

    canInterface.processQueue();

    return 0;
}

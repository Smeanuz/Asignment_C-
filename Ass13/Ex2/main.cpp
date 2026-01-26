
#include <iostream>

class GenericAudioSource {
public:
    virtual void connect() {
        std::cout << "Playing audio from Generic Source.\n";
    }

    virtual ~GenericAudioSource() {}
};

class BluetoothAudioSource : public GenericAudioSource {
public:
    void pairAndConnect() {
        std::cout << "Pairing and connecting to Bluetooth device...\n";

        this->connect();
    }

private:
    void connect() override {
        std::cout << "Playing audio from Bluetooth Source.\n";
    }
};

void test() {
    BluetoothAudioSource* bt = new BluetoothAudioSource();

    // 1. Valid Call
    // pairAndConnect là public -> Trình biên dịch cho phép.
    // Bên trong pairAndConnect gọi connect() (là private của chính nó) -> Cho phép.
    bt->pairAndConnect(); 

    // 2. Compilation Error
    // Trình biên dịch kiểm tra class BluetoothSource.
    // Nó thấy connect() là private -> BÁO LỖI: "GenericAudioSource::connect is inaccessible"
    // bt->connect(); 
    
    delete bt;
}

void hackerMove() {
    BluetoothAudioSource* bt = new BluetoothAudioSource();
    
    // Ép kiểu về cha (Upcasting)
    GenericAudioSource* ptr = bt;
    
    // CỬA HẬU:
    // Trình biên dịch nhìn vào 'ptr', thấy nó là GenericAudioSource*.
    // Trong GenericAudioSource, hàm connect() là PUBLIC -> Cho phép gọi.
    // Tại Runtime, nhờ Virtual Table, nó sẽ nhảy vào hàm private connect() của BluetoothSource.
    ptr->connect(); // -> Vẫn chạy hàm private của con!
}

int main() {
    test();

    std::cout << "=== Hacker Move ===\n";
    hackerMove();

    return 0;
}

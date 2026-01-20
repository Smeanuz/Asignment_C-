
#include <iostream>
#include <fstream>
#include <vector>
#include <thread> // Để giả lập độ trễ khi play
#include <chrono>

// Cấu hình
const size_t CHUNK_SIZE = 4096; // 4KB mỗi lần đọc
const size_t WAV_HEADER_SIZE = 44; // Header chuẩn của file WAV

// Hàm giả lập việc gửi dữ liệu xuống phần cứng âm thanh (DAC/I2S)
void sendToAudioHardware(const char* data, size_t size) {
    // Trong thực tế: memcpy vào DMA buffer hoặc gọi ALSA API
    std::cout << "[Hardware] Playing chunk of size: " << size << " bytes" << std::endl;
    
    // Giả lập thời gian xử lý (tránh in ra quá nhanh làm tràn console)
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void rewindToStart(std::ifstream& file) {
    // Bước 1: QUAN TRỌNG NHẤT - Xóa cờ lỗi/EOF
    // Nếu không có dòng này, mọi lệnh seekg sau đó đều vô nghĩa.
    file.clear(); 

    // Bước 2: Dịch chuyển con trỏ về vị trí bắt đầu data (bỏ qua header)
    file.seekg(WAV_HEADER_SIZE, std::ios::beg);
    
    std::cout << "<<< Rewind complete. Ready to play again." << std::endl;
}

void playAudioFile(const char* filepath) {
    // 1. Mở file chế độ Binary
    std::ifstream audioFile(filepath, std::ios::binary);

    if (!audioFile.is_open()) {
        std::cerr << "[Error] Cannot open audio file: " << filepath << std::endl;
        return;
    }

    // 2. Skip Header (Bỏ qua 44 byte đầu chứa metadata)
    // seekg(offset, direction): Dịch con trỏ đọc đi 44 byte tính từ đầu file (beg)
    audioFile.seekg(WAV_HEADER_SIZE, std::ios::beg);

    // Kiểm tra nếu file quá nhỏ (không đủ header)
    if (!audioFile) {
        std::cerr << "[Error] File is too small to be a valid WAV." << std::endl;
        return;
    }

    // Chuẩn bị buffer (nằm trên Stack hoặc Heap tùy kích thước)
    // std::vector an toàn hơn mảng raw char[]
    std::vector<char> buffer(CHUNK_SIZE);

    std::cout << ">>> Start Playing: " << filepath << std::endl;

    // 3. Vòng lặp đọc file (Playback Loop)
    while (audioFile) {
        // 4. Đọc một chunk
        // .read() sẽ cố đọc đủ 4096 bytes. Nếu gần hết file, nó chỉ đọc phần còn lại.
        audioFile.read(buffer.data(), CHUNK_SIZE);

        // 5. Xử lý trường hợp cuối file (Partial Read)
        // .gcount() trả về số byte thực sự vừa đọc được trong lần gọi gần nhất
        std::streamsize bytesRead = audioFile.gcount();

        if (bytesRead > 0) {
            // Gửi đúng số byte đọc được xuống phần cứng
            sendToAudioHardware(buffer.data(), bytesRead);
        }
        
        // Nếu số byte đọc được < CHUNK_SIZE, nghĩa là đã chạm đáy file
        if (bytesRead < CHUNK_SIZE) {
            break;
        }
    }

    std::cout << ">>> Playback Finished." << std::endl;
}


// --- Main Test ---
int main() {
    // Để test, bạn cần tạo một file dummy.wav hoặc đổi tên code này trỏ tới file có thật
    // Ở đây tôi giả lập logic thôi.
    playAudioFile("song.wav");
    return 0;
}
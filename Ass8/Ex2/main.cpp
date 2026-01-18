
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 2: Using Function Pointers for Customizable Audio Effects
 * 
 * ANALYSIS: Hiệu năng thời gian thực và khả năng mở rộng.
 *  - Nếu sử dụng swithc-case, CPU sẽ phải kiểm tra từng case trong mỗi
 *    chu kỳ xử lý. Lãng phí Clock Cycle.
 *  - Mỗi khi cần mở rộng, phải sửa đổi hàm xử lý. Gây rủi ro và khó bảo trì.
 * 
 * Lý thuyết liên quan: Con trỏ hàm (Function Pointer)
 *  - Code Segment: Các lệnh nằm ở vùng Code (Text Segment) của bộ nhớ, chúng
 *    có địa chỉ cố định trong suốt thời gian chạy chương trình.
 *  - Function Pointer: Là con trỏ trỏ đến địa chỉ của hàm trong Code Segment.
 *  - Dynamic Dispatch: Khi gọi hàm thông qua cỏn trỏ hàm, CPU nhảy đến trực tiếp
 *    địa chỉ hàm
 */

#include <iostream>
#include <vector>

// Define function pointer type
using AudioEffectCallback = void(*)(float* buffer, size_t size);

// Implement Effect Functions
// Effect 1: Bass Boost
void bassBootst(float* buffer, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] > 0) buffer[i] *= 1.5f; // Simple amplification for demonstration
    }
}

// Effect 2: Reverb
void reverb(float* buffer, size_t size)
{
    for (size_t i = 1; i < size; ++i) {
        buffer[i] += 0.5f * buffer[i - 1]; // Simple echo effect for demonstration
    }
}

// Effect 3: Bypass (No effect)
void bypass(float* buffer, size_t size)
{
    // Do nothing
}

enum class EffectType {
    BASS_BOOST,
    REVERB,
    BYPASS
};

class AudioProcessor {
private:
    AudioEffectCallback activeEffect;
public:
    AudioProcessor() : activeEffect(bypass) {}

    void setEffect(EffectType effect) {
        switch (effect) {
            case EffectType::BASS_BOOST:
                activeEffect = &bassBootst;
                std::cout << "-> Set Effect: Bass Boost" << std::endl;
                break;
            case EffectType::REVERB:
                activeEffect = &reverb;
                std::cout << "-> Set Effect: Reverb" << std::endl;
                break;
            case EffectType::BYPASS:
            default:
                activeEffect = &bypass;
                std::cout << "-> Set Effect: Bypass" << std::endl;
                break;
        }
    }

    void processAudio(float* buffer, size_t size) {
        activeEffect(buffer, size);
    }

};


int main() {
    AudioProcessor processor;
    
    // Giả lập một block âm thanh (10 mẫu)
    float audioData[10] = {0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.5f, 0.4f, 0.3f, 0.2f, 0.1f};
    size_t bufferSize = 10;

    // Kịch bản 1: Mặc định (Bypass)
    processor.processAudio(audioData, bufferSize);

    // Kịch bản 2: Người dùng chọn Bass Boost
    processor.setEffect(EffectType::BASS_BOOST);
    processor.processAudio(audioData, bufferSize); 
    // Kiểm tra dữ liệu
    std::cout << "Sample 0 value: " << audioData[0] << " (Expected > 0.1)\n";

    // Kịch bản 3: Người dùng chọn Reverb
    processor.setEffect(EffectType::REVERB);
    processor.processAudio(audioData, bufferSize);

    return 0;
}
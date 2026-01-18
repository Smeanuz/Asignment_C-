
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 4: Using const with Pointers to Protect Data
 */

#include <iostream>
#include <cstdint>

struct Config {
    int id;
    float calibrationValue;
};

// 1. Pointer to Constant Data (dữ liệu bí khoá, con trỏ có thể thay đổi)
// Dùng để đọc thanh ghi trạng thái hoặc duyệt mảng read-only.
const uint32_t* dacRegisterPtr;

// 2. Constant Pointer to Data (con trỏ cố định, dữ liệu có thể thay đổi)
// Buffer âm thanh tại địa chỉ cố định, nhưng nội dung buffer có thể thay đổi.
float* const activeAudioBuffer = (float*)0x20004000;

// 3. Constant Pointer to Constant Data (cả con trỏ và dữ liệu đều cố định)
// Cấu hình hệ thống không thay đổi trong suốt thời gian chạy.
const Config* const rom_config = (Config*)0x08001000;

int main() {
    return 0;
}
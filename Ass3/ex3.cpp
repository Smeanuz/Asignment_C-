
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 14/01/2026
 * 
 * Exercise 3: Storing and Accessing the Firmware Version
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Chuỗi được lưu trữ trong vùng Read-only Data (Text segment) của chương trình.
 * Khi gọi hàm getFirmwareVersion():
 *  - Trả về con trỏ tới chuỗi hằng trong text segment.
 *  - Chuỗi này tồn tại trong suốt thời gian chạy của chương trình.
 *  - Chuỗi này chỉ đọc và không thể thay đổi.
 * 
 * Khái niệm liên quan: TEXT SEGMENTS
 * - Vùng bộ nhớ chứa mã chương trình và dữ liệu hằng.
 * - Thường được đánh dấu là chỉ đọc (read-only).
 * - Dữ liệu trong text segment tồn tại trong suốt thời gian chạy của chương trình.
 * - Không chiemh bộ nhớ heap hay stack. 
 * 
 * SOLUTION:
 * ---------------------
 * Copy chuỗi hằng vào biến local (trên stack) khi hàm được gọi:
 * - Tạo bản sao của chuỗi trong bộ nhớ stack.
 * - Bộ nhớ này được giải phóng khi hàm kết thúc.
 * - Tránh việc trả về con trỏ tới vùng nhớ không hợp lệ.
 * - Có thể thay đổi bản sao này nếu cần.
 * 
 */


#include <iostream>
#include <string>
#include <cstring>

const char* getFirmwareVersion() 
{
    return "V2.1.3-PROD";
}

/*---------------------Code lỗi----------------*/
void tryToModifyFirmwareBad() {
    const char* version = getFirmwareVersion();
    // Attempt to modify the first character of the string
    // char* nonConstVersion = const_cast<char*>(version);
    // nonConstVersion[0] = 'X'; // What would happen here?
}

/*---------------------Code tối ưu----------------*/
void tryToModifyFirmware() {
    const char* version = getFirmwareVersion();
    // Copy the string to a local modifiable buffer
    char localVersion[20]; // Ensure the buffer is large enough
    std::strcpy(localVersion, version);
    localVersion[sizeof(localVersion) - 1] = '\0'; // Null-terminate

    // Now it's safe to modify the local copy
    localVersion[0] = 'X'; // Modify the first character
    std::cout << "Modified firmware version: " << localVersion << std::endl;
}

int main() {
    std::cout << "Original firmware version: " << getFirmwareVersion() << std::endl;

    std::cout << "Trying to modify firmware version (bad method)..." << std::endl;
    // tryToModifyFirmwareBad(); // Uncommenting this may lead to undefined behavior

    std::cout << "Trying to modify firmware version (safe method)..." << std::endl;
    tryToModifyFirmware();

    return 0;
}

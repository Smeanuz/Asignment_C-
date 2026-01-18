
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 14/01/2026
 * 
 * Exercise 4: Optimizing Executable File Size with the BSS Segment
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Biến g_media_database được khởi tạo với giá trị mặc định (0) và
 * không chiếm dung lượng trong file thực thi (.exe). Khi chương trình chạy,
 * hệ điều hành sẽ load biến này vào vùng BSS segment của bộ nhớ.
 * Khi chương trình chạy:
 *  - Hệ điều hành cấp phát bộ nhớ cho biến trong BSS segment.
 *  - Biến được khởi tạo với giá trị mặc định (0).
 *  - Biến tồn tại trong suốt thời gian chạy của chương trình.
 *  - Giúp giảm kích thước file thực thi vì không lưu trữ dữ liệu khởi tạo.
 * 
 * Khái niệm liên quan: BSS SEGMENT
 * - Vùng bộ nhớ dành cho biến toàn cục và static chưa được khởi tạo.
 * - Chứa các biến được khởi tạo với giá trị mặc định (0 hoặc null).
 * - Không chiếm dung lượng trong file thực thi.
 * - Bộ nhớ trong BSS segment được cấp phát khi chương trình chạy.
 * 
 * EXPLAINATION:
 * ---------------------
 * Nếu khởi tạo giá trị cho biến g_media_database:
 *  - Biến sẽ được lưu trữ trong DATA segment.
 *  - Kích thước file thực thi sẽ tăng lên do chứa dữ liệu khởi tạo.
 *  - Khi chương trình chạy, hệ điều hành vẫn cấp phát bộ nhớ cho biến.
 * 
 */


#include <iostream>
#include <cstdint>

struct SongStats {
    uint32_t play_count;
    uint8_t rating; // 1-5 stars
};

// A very large data structure, declared globally and UNINITIALIZED
SongStats g_media_database[500000]; // ~ 2.5 MB

int main() {
    // When the program starts, g_media_database[i].play_count will be 0.
    std::cout << "Initial play count: " << g_media_database[0].play_count << std::endl;
    // ...
    return 0;
}

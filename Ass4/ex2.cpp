
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 14/01/2026
 * 
 * Exercise 2: The Pitfalls of Macros and Side Effects
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Macros trong C/C++ chỉ là các phép thay thế văn bản (text substitution).
 *  - Khi sử dụng macro với các biểu thức có tác dụng phụ (side effects),
 *    như tăng biến (x++), biểu thức đó sẽ được chèn nguyên văn vào macro.
 *  - Điều này có thể dẫn đến việc biểu thức được thực thi nhiều lần.
 *  - Kết quả không mong muốn và khó dự đoán.
 * 
 * Khái niệm liên quan: SIDE EFFECTS
 * - Là những thay đổi trạng thái bên ngoài của biểu thức hoặc hàm.
 * - Ví dụ: thay đổi giá trị biến toàn cục, ghi vào file, in ra màn hình.
 * - Khi biểu thức có side effects được sử dụng trong macro, cần cẩn thận để tránh việc thực thi nhiều lần.
 * 
 * SOLUTION:
 * ---------------------
 * Sử dụng hàm inline thay vì macro:
 *  - Hàm inline được biên dịch giống như hàm thông thường nhưng có thể được tối ưu hóa để tránh overhead của lời gọi hàm.
 *  - Biểu thức chỉ được đánh giá một lần khi truyền vào hàm.
 */


#include <iostream>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

template<typename T>
inline T maxInline(const T& a, const T& b) {
    return (a > b) ? a : b;
}

/*--------------Code lỗi--------------*/
void adjustVolumeBad(int& currentVolume, int increaseAmount) {
    int maxVolume = 100;
    // Update the volume, but do not exceed maxVolume
    // A BUG OCCURS HERE
    currentVolume = MAX(currentVolume + increaseAmount, maxVolume);
}

/*--------------Code tối ưu--------------*/
void adjustVolume(int& currentVolume, int increaseAmount) {
    int maxVolume = 100;
    // Update the volume, but do not exceed maxVolume
    currentVolume = maxInline(currentVolume + increaseAmount, maxVolume);
}

int main() {
    int volume = 110;
    std::cout << "Initial Volume: " << volume << std::endl;
    adjustVolumeBad(volume, 15);
    std::cout << "After adjustVolumeBad: " << volume << std::endl;

    volume = 110; // Reset volume
    adjustVolume(volume, 15);
    std::cout << "After adjustVolume: " << volume << std::endl;
    return 0;
}
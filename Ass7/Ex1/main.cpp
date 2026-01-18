
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 1: Preserving Array Size Information When Passing to a Function
 * 
 * ANALYSIS: Khi truyền một mảng vào hàm trong C++, thông tin về kích thước
 * khi return mảng bị trả về kích thước của con trỏ.
 * 
 * 1. Array Decay (sự phân rã của mảng): là hiện tượng xảy ra khi truyền
 * vào hàm dưới dạng tham trị.
 *   - Mảng ban đầu sẽ bị phân rã thành con trỏ trỏ đến phần tử đầu tiên
 *    của mảng.
 *   - Do đó, thông tin về kích thước mảng ban đầu bị mất.
 *   - Con trỏ chỉ chứa địa chỉ bộ nhớ có kích thước là 4 hoặc 8 byte (tuỳ
 *   vào hệ thống 32-bit hay 64-bit).
 * 
 */

#include <iostream>

/*---------------Error code------------*/
// void applyEqSettings_WRONG(float settings[]) {
//     // sizeof(settings) here will return 4 or 8 (the size of a pointer)
//     // not 10 * sizeof(float)
//     std::cout << "Size inside function: " << sizeof(settings) << std::endl;
// }

/*---------------Correct code------------*/
// Using reference to an array of known size
void applyEqSettings_CORRECT(float (&settings)[10]) {

    //calculate real size
    size_t totalSize = sizeof(settings);            // Total size in bytes
    size_t elementSize = sizeof(settings[0]);       // Size of one element
    size_t numElement = totalSize / elementSize;    // Number of elements

    std::cout << "--- Inside CORRECT Function ---" << std::endl;
    std::cout << "Total Array Size in Bytes: " << totalSize << std::endl;
    std::cout << "Number of Elements: " << numElement << std::endl;
    
    // Loop through the array and print each element
    for (size_t i = 0; i < numElement; ++i) {
        std::cout << "Element " << i << ": " << settings[i] << std::endl;
    }
    return;

}

int main() {
    float eqSettings[10] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f,
                            5.0f, 6.0f, 7.0f, 8.0f, 9.0f};

    // std::cout << "--- Calling WRONG Function ---" << std::endl;
    // applyEqSettings_WRONG(eqSettings);

    std::cout << "\n--- Calling CORRECT Function ---" << std::endl;
    applyEqSettings_CORRECT(eqSettings);

    return 0;
}


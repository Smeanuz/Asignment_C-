
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 4:  Writing a Function to Handle a 2D Array
 * 
 * ANALYSIS:
 *  - Khi làm việc với mảng 2D trong C++, cần hiểu cách bộ nhớ được
 *    tổ chức và cách truyền mảng vào hàm.
 *  - Mảng 2D trong C++ thực chất là một mảng của các mảng.
 *  - Khi truyền mảng 2D vào hàm, cần chỉ định kích thước của các cột để
 *    trình biên dịch có thể tính toán đúng địa chỉ của các phần tử.
 *  - Việc sử dụng con trỏ đôi (pointer to pointer) không phù hợp cho mảng 2D
 *    được khai báo tĩnh vì cách bố trí bộ nhớ khác nhau.
 * 
 * Lý thuyết liên quan:
 *  - Mảng 2D: Là một mảng mà mỗi phần tử của nó cũng là một mảng.
 *  - Truyền mảng vào hàm: Cần chỉ định kích thước của các cột khi truyền mảng 2D.
 *  - Cách bố trí bộ nhớ: Mảng 2D được lưu trữ liên tục trong bộ nhớ theo hàng (row-major order).
 * 
 * SOLUTION:
 * - Sử dụng pointer to array. 
 * - Sử dụng reference to array.
 */


#include <iostream>

/*----Pointer to Array---*/
void loadPresetPtArray(float (*presets)[5], int numPresets) {
    for (int i = 0; i < numPresets; ++i) {
        std::cout << "Preset " << i << ": ";
        for (int j = 0; j < 5; ++j) {
            std::cout << presets[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

/*----Reference to Array---*/
void loadPresetRefArray(float (&presets)[3][5]) {
    for (int i = 0; i < 3; ++i) {
        std::cout << "Preset " << i << ": ";
        for (int j = 0; j < 5; ++j) {
            std::cout << presets[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    float eqPresets[3][5] = {
        {0.0f, 1.0f, 2.0f, 3.0f, 4.0f},
        {5.0f, 6.0f, 7.0f, 8.0f, 9.0f},
        {10.0f, 11.0f, 12.0f, 13.0f, 14.0f}
    };

    std::cout << "--- Using Pointer to Array ---" << std::endl;
    loadPresetPtArray(eqPresets, 3);

    std::cout << "\n--- Using Reference to Array ---" << std::endl;
    loadPresetRefArray(eqPresets);

    return 0;
}

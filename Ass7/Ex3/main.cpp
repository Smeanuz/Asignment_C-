
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 3:  Modifying Array Elements with a Range-Based For Loop
 * 
 * ANALYSIS:
 *  - Khi sử dụng vòng lặp for-each (range-based for loop) trong C++,
 *    các phần tử mảng được truyền vào vòng lặp theo giá trị (by value).
 *  - Điều này có nghĩa là bất kỳ sự thay đổi nào đối với biến lặp trong
 *    vòng lặp sẽ không ảnh hưởng đến mảng gốc.
 * 
 * Lý thuyết liên quan:
 *  - Truyền theo giá trị (Pass by Value): Khi một biến được truyền theo
 *    giá trị, một bản sao của biến đó được tạo ra trong phạm vi của hàm
 *    hoặc vòng lặp. Do đó, các thay đổi đối với bản sao này không ảnh hưởng
 *    đến biến gốc.
 *  - Truyền theo tham chiếu (Pass by Reference): Khi một biến được truyền
 *    theo tham chiếu, hàm hoặc vòng lặp làm việc trực tiếp với biến gốc.
 *    Do đó, bất kỳ thay đổi nào đối với biến trong hàm hoặc vòng lặp sẽ
 *    ảnh hưởng đến biến gốc.
 * 
 * SOLUTION:
 *  - Sử dụng tham chiếu trong vòng lặp for-each để đảm bảo rằng các
 *    thay đổi đối với biến lặp ảnh hưởng đến mảng gốc.
 */

#include <iostream>
#include <vector>

 struct Song {
    float volume_db = 0.0f;
    void normalize() { volume_db = -6.0f; /* Normalize to -6dB */ }
};

/*----------Error Code--------------*/
// void normalizeQueueBad(Song queue[], int size) {
//     // WRONG: This loop operates on a COPY of each song
//     for (Song s : queue) { // <-- The error is here
//         s.normalize();
//     }
// }

/*----------Correct Code--------------*/
void normalizeQueueCorrect(std::vector<Song>& queue, int size) {
    // CORRECT: This loop operates on a REFERENCE to each song
    for (Song& s : queue) { // <-- Use reference here
        s.normalize();
    }
}

int main() {
    std::vector<Song> myQueue(3);

    // normalizeQueueBad(playQueue.data(), queueSize); // This would not modify the original songs

    normalizeQueueCorrect(myQueue, 3); // This will modify the original songs
    // Verify that songs have been normalized

    for(int i=0; i<3; ++i) {
        // Prints 0.0, not -6.0 as expected
        std::cout << myQueue[i].volume_db << std::endl;
    }


    return 0;
}

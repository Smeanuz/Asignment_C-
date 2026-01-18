
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 3: Modifying a Pointer vs. Modifying the Data it Points To
 * 
 * ANALYSIS: 
 *  - Khi sử dụng Pass-pointer-by-value, ta truyền bản sao của con trỏ vào hàm.
 *    việc thay đổi con trỏ bên trong hàm sẽ không ảnh hưởng đến con trỏ gốc.
 *  - Khi sử dụng Pass-pointer-by-reference, ta truyền tham chiếu đến con trỏ.
 *    việc thay đổi con trỏ bên trong hàm sẽ ảnh hưởng đến con trỏ gốc.
 *  - Khi sử dụng Pass-pointer-by-pointer, ta truyền địa chỉ của con trỏ.
 *    việc thay đổi con trỏ bên trong hàm sẽ ảnh hưởng đến con trỏ gốc.
 */

#include <iostream>

struct Song {
    Song* next;
};

/*---Error Code---*/
// ERROR: This function only changes a local copy of the pointer
void selectNextInPlaylist_WRONG(Song* current) {
    if (current != nullptr && current->next != nullptr) {
        current = current->next; // Only changes the local 'current' pointer
    }
}

/*---Correct Code---*/
// Method 1: Reference to Pointer
void selectNextInPlaylist_Ref(Song*& current) {
    if (current != nullptr && current->next != nullptr) {
        current = current->next; // Changes the original 'current' pointer
    }
    
    return;
}

void testMethod1() {
    Song song1, song2;
    song1.next = &song2;
    song2.next = nullptr;

    Song* currentSong = &song1;
    std::cout << "Before: " << (currentSong == &song1 ? "song1" : "song2") << std::endl;

    selectNextInPlaylist_Ref(currentSong);

    std::cout << "After: " << (currentSong == &song1 ? "song1" : "song2") << std::endl;
}

// Method 2: Pointer to Pointer
void selectNextInPlaylist_Ptr(Song** current) {
    if (current != nullptr && *current != nullptr && (*current)->next != nullptr) {
        *current = (*current)->next; // Changes the original 'current' pointer
    }

    return;
}

void testMethod2() {
    Song song1, song2;
    song1.next = &song2;
    song2.next = nullptr;

    Song* currentSong = &song1;
    std::cout << "Before: " << (currentSong == &song1 ? "song1" : "song2") << std::endl;

    selectNextInPlaylist_Ptr(&currentSong);

    std::cout << "After: " << (currentSong == &song1 ? "song1" : "song2") << std::endl;
}

int main() {
    std::cout << "--- Testing Method 1: Reference to Pointer ---" << std::endl;
    testMethod1();

    std::cout << "\n--- Testing Method 2: Pointer to Pointer ---" << std::endl;
    testMethod2();

    return 0;
}

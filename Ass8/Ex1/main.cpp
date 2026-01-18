
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 1: Dangling Pointer in a Dynamic Playlist
 * 
 * ANALYSIS: Con trỏ treo (dangling pointer) do cơ chế quản lý bộ nhớ động trong C++.
 *  - Khi một con trỏ trỏ đến phần tử trong vector, con trỏ trỏ đến địa chỉ
 *    của phần tử đó trong bộ nhớ heap.
 *  - Khi vector thay đổi kích thước (bằng cách thêm hoặc xóa phần tử),
 *    nó có thể cần cấp phát lại bộ nhớ để chứa các phần tử mới.
 *  - Lúc này địa chỉ cũ đã bị thay đổi, làm cho con trỏ ban đầu trở thành con trỏ treo.
 *  - Gây ra hành vi không xác định.
 * 
 * Lý thuyết liên quan:
 *  - Vector là các phần tử nằm cạnh nhau trong bộ nhớ heap.
 *  - Khi thêm phần tử vào vector, nếu không còn đủ chỗ, vector sẽ cấp phát lại
 *    một khối bộ nhớ lớn hơn, sao chép các phần tử cũ vào đó và giải phóng khối bộ nhớ cũ.
 */

#include <iostream>
#include <vector>
#include <string>

struct Song {
    std::string title;
};

/*---Error Code---*/
int Bad() {
    std::vector<Song> playlist = {{"Song A"}, {"Song B"}};
    int currentIndex = 0;
    
    // 1. Get a pointer to the current song
    Song* currentSongPtr = &playlist[currentIndex];
    std::cout << "Before reallocation: " << currentSongPtr->title << std::endl;
    
    // 2. Add many new songs, causing the vector to reallocate memory
    playlist.push_back({"Song C"});
    playlist.push_back({"Song D"});
    playlist.push_back({"Song E"});
    
    // 3. PROBLEM: The 'currentSongPtr' may now be invalid
    std::cout << "After reallocation: " << currentSongPtr->title << std::endl; // CRASH or prints garbage data!
    
    return 0;
}

/*---Correct Code---*/
// Method 1: Use index instead of pointer
void usingIndex() {
    std::vector<Song> playlist = {{"Song A"}, {"Song B"}};
    
    // SOLUTION: Dùng index thay vì pointer
    size_t currentIndex = 0; 
    
    std::cout << "Before: " << playlist[currentIndex].title << std::endl;
    
    // Gây ra reallocation
    playlist.push_back({"Song C"});
    playlist.push_back({"Song D"});
    playlist.push_back({"Song E"});
    
    // Vẫn an toàn tuyệt đối
    std::cout << "After: " << playlist[currentIndex].title << std::endl;
    
    return;
}

// Method 2: Use std::list
/*
Là danh sách liên kết đôi (doubly linked list), trong đó mỗi phần tử (node) chứa
một giá trị và con trỏ đến phần tử trước và sau nó. Khi thêm hoặc xóa phần tử,
chỉ cần cập nhật các con trỏ mà không cần di chuyển các phần tử khác trong bộ nhớ.

Ưu điểm: Đảm bảo con tor trỏ đến phần tử hiện tại luôn hợp lệ,
cho đến khi chính phần tử đó bị xóa khỏi danh sách.

Nhược điểm: Truy cập phần tử chậm hơn so với vector do không có truy cập ngẫu nhiên (random access).
(do phải lưu 2 con trỏ next và prev trong mỗi node)
*/
#include <list>
void usingList() {
    std::list<Song> playlist = {{"Song A"}, {"Song B"}};
    
    // Lấy iterator hoặc pointer tới phần tử đầu tiên
    // Trong std::list, địa chỉ của phần tử KHÔNG đổi khi thêm mới
    Song* currentSongPtr = &playlist.front(); 
    
    std::cout << "Before: " << currentSongPtr->title << std::endl;
    
    // Thêm bao nhiêu cũng không sợ reallocation
    playlist.push_back({"Song C"});
    playlist.push_back({"Song D"});
    
    // Pointer vẫn hợp lệ
    std::cout << "After: " << currentSongPtr->title << std::endl;
    
    return;
}



int main() {
    std::cout << "---- Demonstrating Dangling Pointer Issue ----" << std::endl;
    Bad();
    
    std::cout << "\n---- Correct Approach Using Index ----" << std::endl;
    usingIndex();
    
    std::cout << "\n---- Correct Approach Using std::list ----" << std::endl;
    usingList();
    
    return 0;
}

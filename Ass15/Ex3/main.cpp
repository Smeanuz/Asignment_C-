
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 27/01/2026
 * 
 * Exercise 3: Writing a Generic Search Function with a Function Template
 */

#include <iostream>
#include <vector>
#include <list>
#include <string>

// --- HELPER STRUCT FOR TESTING ---
struct Song {
    int id;
    std::string title;
};

struct Album {
    std::string id; // ID dạng chuỗi (ISBN)
    std::string name;
};

// ==========================================
// FUNCTION TEMPLATE
// ==========================================
// Container: Là kiểu dữ liệu chứa (vd: vector<Song>)
// IDType: Là kiểu dữ liệu của ID (vd: int, string)
template <typename Container, typename IDType>
typename Container::iterator findItemByID(Container& container, const IDType& id) {
    
    // Duyệt qua container bằng iterator
    // Dùng 'auto' cho gọn, nhưng bản chất nó là Container::iterator
    for (auto it = container.begin(); it != container.end(); ++it) {
        
        // Kiểm tra điều kiện: Phần tử phải có member .id
        if (it->id == id) {
            return it; // Trả về iterator trỏ tới phần tử tìm thấy
        }
    }

    // Không tìm thấy -> Trả về iterator báo hiệu kết thúc
    return container.end();
}

// ==========================================
// MAIN TEST
// ==========================================
int main() {
    // 1. Test với Vector<Song> (ID là int)
    std::vector<Song> playlist = {
        {101, "Yesterday"},
        {102, "Let It Be"},
        {103, "Hey Jude"}
    };

    std::cout << "--- Searching in Vector<Song> ---\n";
    auto itSong = findItemByID(playlist, 102);

    if (itSong != playlist.end()) {
        std::cout << "Found Song: " << itSong->title << " (ID: " << itSong->id << ")\n";
    } else {
        std::cout << "Song not found.\n";
    }

    // 2. Test với List<Album> (ID là string)
    // Chứng minh hàm này chạy tốt trên cả std::list và ID kiểu khác
    std::list<Album> albums = {
        {"ALB_001", "Abbey Road"},
        {"ALB_002", "Thriller"}
    };

    std::cout << "\n--- Searching in List<Album> ---\n";
    // Lưu ý: ID truyền vào là string literal "ALB_002"
    auto itAlbum = findItemByID(albums, std::string("ALB_002"));

    if (itAlbum != albums.end()) {
        std::cout << "Found Album: " << itAlbum->name << "\n";
    }

    return 0;
}
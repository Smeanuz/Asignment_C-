
#include <iostream>
#include <vector>
#include <string>
#include <memory> // Thư viện cho smart pointers

// 1. Base Class
class MediaItem {
public:
    virtual void play() const { 
        std::cout << "[Generic] Playing unknown media..." << std::endl; 
    }

    // QUAN TRỌNG: Luôn cần Virtual Destructor khi dùng đa hình
    // Để smart pointer có thể delete đúng đối tượng con
    virtual ~MediaItem() = default;
};

// 2. Derived Class
class Song : public MediaItem {
public:
    std::string artist;
    std::string title;

    Song(std::string t, std::string a) : title(t), artist(a) {}

    // Override hàm play
    void play() const override { 
        std::cout << "[Song] Playing: " << title << " by " << artist << std::endl; 
    }
};

// 3. Another Derived Class (Ví dụ thêm)
class Podcast : public MediaItem {
public:
    void play() const override { 
        std::cout << "[Podcast] Playing episode #42..." << std::endl; 
    }
};

int main() {
    // --- FIX: Sử dụng Vector chứa Unique Pointer ---
    // Vector này chỉ chứa các "tờ giấy ghi địa chỉ", không chứa vật thể
    std::vector<std::unique_ptr<MediaItem>> playlist;

    // --- Thêm bài hát vào playlist ---
    // std::make_unique tạo đối tượng Song trên Heap và trả về con trỏ quản lý nó
    playlist.push_back(std::make_unique<Song>("Bohemian Rhapsody", "Queen"));
    
    // --- Thêm podcast vào playlist ---
    playlist.push_back(std::make_unique<Podcast>());

    // --- Duyệt và phát nhạc ---
    std::cout << "--- Playlist Start ---\n";
    
    for (const auto& item : playlist) {
        // item ở đây là unique_ptr&
        // Toán tử -> sẽ truy cập vào đối tượng thực sự trên Heap
        item->play(); 
    }
    
    // Khi vector bị hủy, unique_ptr sẽ tự động delete các đối tượng Song/Podcast.
    // Không lo rò rỉ bộ nhớ (Memory Leak).

    return 0;
}
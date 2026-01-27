
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 27/01/2026
 * 
 * Exercise 2: Building a Generic Playlist Class with a Class Template
 * 
 * 
 * Cần phải method body trong file header vì:
 *  - Khi sử dụng class template, thì chỉ mới hướng dẫn trình biên dịch cách tạo class.
 *  - Mã máy chỉ sinh ra khi có instantiation (sử dụng template với kiểu cụ thể). 
 *  Khi khai báo Playlist<Song>, trình biên dịch mới tạo ra class Playlist_Song, để thay thế T bằng Song.
 *  - Nếu khai báo trong .h và nội dung trong .cpp. Khi biên dịch file, nó chỉ thhấy file .h nhưng không thấy nội dung
 *  hàm để tạo mã máy cho Playlist<Song>. Nó để lại một symbol reference cho linker.
 *      + Khi biên dịch Playlist.cpp, trình biên dịch thấy code của Template nhưng không biết T là gì.
 *     Nên nó không tạo mã máy cho bất cứ kiểu nào. Linker báo lỗi Undefined Reference.
 * -> Do đó, tất cả code của template phải nằm trong file header để trình biên dịch có thể tạo mã máy
 *    khi gặp instantiation với kiểu cụ thể.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept> // Thư viện cho ngoại lệ

// Class Template
template <typename T>
class Playlist {
private:
    std::vector<T> items; // Vector chứa các mục trong playlist
    size_t currentIndex = 0; // Chỉ mục của mục hiện tại

public:
    // Them mục vào playlist
    void addItem(const T& item) {
        items.push_back(item);
    }

    T& getCurrentItem() {
        if (items.empty()) {
            throw std::out_of_range("Playlist is empty");
        }
        return items[currentIndex];
    }

        

    void removeCurrent() {
        if (items.empty()) return;

        // Xoá phần tử tại ví trí currentIndex và trả về nó
        items.erase(items.begin() + currentIndex);

        // Điều chỉnh currentIndex nếu cần
        if (currentIndex >= items.size() && currentIndex > 0) {
            currentIndex--; // Quay lại đầu nếu vượt quá kích thước
        }
    }

    // Có bài tiếp theo không
    bool hasNext() const {
        return !items.empty() && (currentIndex < items.size() - 1);
    }

    // Di chuyển đến bài tiếp theo
    void next() {
        if (hasNext()) {
            currentIndex++;
        } else {
            std::cout << "End of playlist reached.\n";
        }
    }


    size_t size() const { return items.size(); }


};


// Helper struct
struct Song {
    std::string title;
    std::string artist;

    friend std::ostream& operator<<(std::ostream& os, const Song& song) {
        os << song.title << " by " << song.artist;
        return os;
    }
};

struct Podcast {
    std::string episodeTitle;
    int durationMin;

    friend std::ostream& operator<<(std::ostream& os, const Podcast& podcast) {
        os << podcast.episodeTitle << " (" << podcast.durationMin << " mins)";
        return os;
    }
};


int main() {
    // --- TEST 1: Playlist cho SONG ---
    std::cout << "--- Music Playlist ---\n";
    
    // Instantiation: Trình biên dịch tạo ra class Playlist_Song
    Playlist<Song> musicPlaylist; 
    
    musicPlaylist.addItem({"Bohemian Rhapsody", "Queen"});
    musicPlaylist.addItem({"Hotel California", "Eagles"});

    // Thử truy cập
    std::cout << "Now Playing: " << musicPlaylist.getCurrentItem() << "\n";
    
    // Thử next
    if (musicPlaylist.hasNext()) {
        musicPlaylist.next();
        std::cout << "Next Playing: " << musicPlaylist.getCurrentItem() << "\n";
    }

    // --- TEST 2: Playlist cho PODCAST ---
    std::cout << "\n--- Podcast Playlist ---\n";
    
    // Instantiation: Trình biên dịch tạo ra class Playlist_PodcastEpisode
    Playlist<Podcast> podcastPlaylist;
    
    podcastPlaylist.addItem({"Tech Talk Ep.1", 45});
    podcastPlaylist.addItem({"History of Rome", 60});

    std::cout << "Current Pod: " << podcastPlaylist.getCurrentItem() << "\n";
    
    // Thử xóa
    std::cout << "Removing current item...\n";
    podcastPlaylist.removeCurrent();
    std::cout << "New Current Pod: " << podcastPlaylist.getCurrentItem() << "\n";

    return 0;
}
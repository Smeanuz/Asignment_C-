#include <vector>
#include <string>
#include <array>

struct Song {
    int id;
    std::string title;
};


class MusicLibrarySolution1 {
private:
    std::vector<Song> m_songs;
    const size_t MAX_SONGS = 2000; // Giới hạn cứng

public:
    void init() {
        // [QUAN TRỌNG] Xin cấp phát 1 lần duy nhất ngay lúc khởi động
        // Vector sẽ chiếm sẵn chỗ cho 2000 bài.
        m_songs.reserve(MAX_SONGS); 
    }

    void addSong(const Song& s) {
        if (m_songs.size() < MAX_SONGS) {
            // Thao tác này bây giờ luôn là O(1) vì bộ nhớ đã có sẵn
            m_songs.push_back(s); 
        } else {
            // Xử lý lỗi: Bộ nhớ đầy
        }
    }
};


class MusicLibrarySolution2 {
private:
    // Cấp phát tĩnh: Nằm trong vùng nhớ BSS/Data hoặc Stack của class cha.
    // KHÔNG bao giờ gọi 'new' hay 'malloc'.
    static const size_t MAX_SONGS = 2000;
    std::array<Song, MAX_SONGS> m_songs; 
    
    size_t m_currentSize = 0; // Biến đếm thủ công

public:
    void addSong(const Song& s) {
        // Kiểm tra biên (Bounds Check) cực nhanh
        if (m_currentSize < MAX_SONGS) {
            // Gán trực tiếp vào ô nhớ tĩnh -> O(1) tuyệt đối
            m_songs[m_currentSize] = s;
            m_currentSize++;
        } else {
            // Error handling: Database Full
        }
    }
    
    // Helper functions để giả lập hành vi vector
    size_t size() const { return m_currentSize; }
    Song& operator[](size_t index) { return m_songs[index]; }
};
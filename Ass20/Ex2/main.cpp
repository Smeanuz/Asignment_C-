#include <array>
#include <vector>
#include <cstring>
#include <cstdint>

// Hàm băm đơn giản (Trong thực tế dùng CRC32 hoặc FNV-1a)
uint32_t stringHash(const char* str) {
    uint32_t hash = 5381;
    int c;
    while ((c = *str++)) hash = ((hash << 5) + hash) + c;
    return hash;
}

// 1. HOT DATA (Cache Friendly)
// Kích thước: 4 + 4 + 4 = 12 bytes.
// Một Cache Line (64 bytes) chứa được 5 bài hát!
struct SongHot {
    uint32_t id;
    uint32_t artistKey; // Hash của tên ca sĩ
    uint32_t duration;
};

// 2. COLD DATA (UI Only)
// Kích thước: ~200 bytes. Chỉ load khi user bấm vào bài hát để xem chi tiết.
struct SongCold {
    char title[64];
    char artist[64];
    char album[64];
};

class MusicLibrary {
private:
    static const size_t MAX_SONGS = 2000;

    // HAI MẢNG SONG SONG (Parallel Arrays)
    // Index 'i' của m_hot tương ứng với Index 'i' của m_cold
    std::array<SongHot, MAX_SONGS> m_hotData;      
    std::array<SongCold, MAX_SONGS> m_coldData;
    
    size_t m_count = 0;

public:
    void addSong(int id, const char* title, const char* artist, const char* album, int duration) {
        if (m_count >= MAX_SONGS) return;

        // 1. Lưu vào Hot Data (Tính toán Hash ngay lúc thêm)
        m_hotData[m_count].id = id;
        m_hotData[m_count].artistKey = stringHash(artist); // Pre-calculate Hash
        m_hotData[m_count].duration = duration;

        // 2. Lưu vào Cold Data
        std::strncpy(m_coldData[m_count].title, title, 63);
        std::strncpy(m_coldData[m_count].artist, artist, 63);
        std::strncpy(m_coldData[m_count].album, album, 63);

        m_count++;
    }

    // --- OPTIMIZED SEARCH FUNCTION ---
    // Hàm này chỉ chạm vào m_hotData. 
    // m_coldData hoàn toàn không được load vào Cache.
    void findSongsByArtist(const char* artistName, std::vector<int>& outResultIDs) {
        uint32_t searchKey = stringHash(artistName);

        // Duyệt tuyến tính (Linear Scan) nhưng cực nhanh
        for (size_t i = 0; i < m_count; ++i) {
            // So sánh số nguyên (Integer Comparison) thay vì chuỗi
            if (m_hotData[i].artistKey == searchKey) {
                outResultIDs.push_back(m_hotData[i].id);
            }
        }
    }
    
    // Hàm lấy chi tiết để hiển thị (Chỉ gọi khi cần)
    const SongCold& getSongMetadata(int index) {
        return m_coldData[index];
    }
};
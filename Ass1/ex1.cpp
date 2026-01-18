/**
 * Exercise 1: Maintaining Playback State When Switching Screens
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Biến currentSong và playbackTime luôn bị reset vì chúng là BIẾN CỤC BỘ (local variables).
 * Mỗi khi hàm renderMediaPlayerScreen() được gọi:
 *   1. Các biến cục bộ được tạo mới trên stack
 *   2. Chúng được khởi tạo với giá trị mặc định (song đầu tiên, time = 0)
 *   3. Khi hàm kết thúc, các biến này bị hủy
 *   4. Lần gọi tiếp theo, quá trình lặp lại -> mất hết trạng thái
 * 
 * Khái niệm liên quan: VARIABLE LIFECYCLE (Vòng đời của biến)
 *   - Biến cục bộ chỉ tồn tại trong phạm vi (scope) của hàm
 *   - Khi hàm return, stack frame bị hủy và biến biến mất
 * 
 * SOLUTION:
 * ---------------------
 * Sử dụng từ khóa STATIC để biến:
 *   - Chỉ được khởi tạo MỘT LẦN (lần gọi hàm đầu tiên)
 *   - GIỮ GIÁ TRỊ giữa các lần gọi hàm
 *   - Tồn tại cho đến khi chương trình kết thúc
 */


#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Song {
    int id;
    string title;
    int duration;
};

struct MediaPlayerState {
    Song currentSong;
    int playBackTime;
    int currentSongIndex;
    bool isInitialized;

    MediaPlayerState() : playBackTime(0), currentSongIndex(0), isInitialized(false) {
        currentSong = {-1, "Unknown", 0};
    }
};

struct Playlist {
    vector<Song> songs;

    Song getSong(int index) const {
        if (index >= 0 && index < static_cast<int>(songs.size())) {
            return songs[index];
        }
        return Song{-1, "Unknown", 0};
    }

    int size() const {
        return static_cast<int>(songs.size());
    }
};

/**
 * Meyers' Singleton Pattern
 * Hàm lấy trạng thái Media Player (Singleton pattern với static)
 * @return MediaPlayerState& - tham chiếu đến trạng thái Media Player
 */
MediaPlayerState& getMediaPlayerState() {
    static MediaPlayerState state; // Static: tồn tại suốt chương trình
    return state;
}

void renderMediaPlayerScreen(const Playlist& currentPlaylist)
{
    MediaPlayerState& state = getMediaPlayerState();
    // Initialize on first call
    if (!state.isInitialized && currentPlaylist.size() > 0) {
        state.currentSong = currentPlaylist.getSong(0);
        state.currentSongIndex = 0;
        state.playBackTime = 0;
        state.isInitialized = true;
    }

    cout << "========== MEDIA PLAYER SCREEN ==========" << endl;
    cout << "Now Playing: " << state.currentSong.title << endl;
    cout << "Playback Time: " << state.playBackTime << "s / " 
    << state.currentSong.duration << "s" << endl;
    cout << "==========================================" << endl;   

}

void updatePlaybackTime(int elapsedSeconds)
{
    MediaPlayerState& state = getMediaPlayerState();
    state.playBackTime = elapsedSeconds;
    cout << "[System] Updated playback time to " << state.playBackTime << "s" << endl;
}

void selectNewSong(const Playlist& currentPlaylist, int songIndex)
{
    MediaPlayerState& state = getMediaPlayerState();

    if (songIndex >= 0 && songIndex < currentPlaylist.size()) {
        state.currentSong = currentPlaylist.getSong(songIndex);
        state.currentSongIndex = songIndex;
        state.playBackTime = 0; // Reset time ONLY when user selects new song
        cout << "[System] User selected new song: " << state.currentSong.title << endl;
    }
}

int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}
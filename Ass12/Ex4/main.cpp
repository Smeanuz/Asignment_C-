
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 26/01/2026
 * 
 * Exercise 4: Applying the Template Method Pattern for a Playlist Importer
 * 
 */

#include <iostream>
#include <vector>
#include <string>

/*---Abstract base class---*/
class PlaylistImporter {
protected:
    // Dữ liệu chung sau khi parse
    std::vector<std::string> loadedSongs;
    std::string currentFilePath;

    // Bước 1: Mở file (bước chung)
    bool openFile(const char* path) {
        std::cout << "\n[Step 1] Opening file: " << path << "...\n";
        currentFilePath = path;

        // Giả sử file luôn mở thành công
        return true;
    }

    // Bước 2: Parse file (bước khác nhau)
    virtual void parseContents() = 0;

    // Bước 3: Validate data (bước riêng)
    virtual bool validateSongs() = 0;

    // Bước 4: Add to library (bước chung)
    void addToLibrary() {
        std::cout << "[Step 4] Adding " << loadedSongs.size() << " songs to Library DB.\n";
        for (const auto& song : loadedSongs) {
            std::cout << "   -> Added: " << song << "\n";
        }
        loadedSongs.clear();
    }

    // Bước 5: Close file (bước chung)
    void closeFile() {
        std::cout << "[Step 5] Closing file handle."  << "\n";
    }

public:
    virtual ~PlaylistImporter() {}

    /*---Template Method---*/
    /**
     * Hàm này quy định thuật toán chung.
     * Nó thường không phải là virtual để class con không phá vỡ quy trình.
     */
    void importPlaylist(const char* path) {
        // Mở file
        if (!openFile(path)) return;

        // Parse nội dung file (Class con tự quy định)
        parseContents();

        // Validate dữ liệu (Class con tự quy định)
        if (validateSongs()) {
            // Nếu hợp lệ, thêm vào thư viện
            addToLibrary();
        } else {
            std::cout << "[Error] Validation failed! Import aborted.\n";
        }

        // Đóng file
        closeFile();
    }
};

/*---Concrete class: TXT Importer---*/
class TxtPlaylistImporter : public PlaylistImporter {
protected:
    void parseContents() override {
        std::cout << "[Step 2 - TXT] Reading line by line...\n";
        // Giả sử ta đọc file và tìm thấy 2 bài hát
        loadedSongs.push_back("Song A.mp3");
        loadedSongs.push_back("Song B.mp3");
    }

    bool validateSongs() override {
        std::cout << "[Step 3 - TXT] Validating TXT songs...\n";
        // Giả sử tất cả bài hát đều hợp lệ
        return true;
    }
};


/*---Concrete class: XML Importer---*/
class XmlPlaylistImporter : public PlaylistImporter {
protected:
    void parseContents() override {
        std::cout << "[Step 2 - XML] Parsing XML Tags <Song>...</Song>...\n";
        // Giả lập đọc file .xml
        loadedSongs.push_back("Artist - Title (XML)");
    }

    bool validateSongs() override {
        std::cout << "[Step 3 - XML] Validating Metadata tags (Artist, Album)...\n";
        // Giả sử logic validate XML khắt khe hơn
        return true;
    }
};


int main() {
    // Kịch bản 1: Import file TXT
    std::cout << "=== IMPORTING TXT ===\n";
    TxtPlaylistImporter txtImporter;
    
    // Gọi Template Method
    txtImporter.importPlaylist("playlist_old.txt");

    // Kịch bản 2: Import file XML
    std::cout << "\n=== IMPORTING XML ===\n";
    XmlPlaylistImporter xmlImporter;
    xmlImporter.importPlaylist("metadata_export.xml");

    return 0;
}

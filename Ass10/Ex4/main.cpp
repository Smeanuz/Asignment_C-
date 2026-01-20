
/**
 * Author: Nhat Minh
 * Date: 19/01/2026
 * 
 * Exercise 4: Implementing a "Safe Save" Mechanism
 * 
 * 2. Rename an toàn:
 *  - Nếu sử dụng direct overwrite , hệ điều hành sẽ xoá nội dung file cũ,
 *  và bắt đầu ghi dữ liệu vào. Nếu quá trình ghi bị lỗi (ví dụ: mất điện, lỗi ổ đĩa),
 *  file có thể bị hỏng và mất dữ liệu.
 *  - Thay vào đó, ta có thể ghi dữ liệu vào một file tạm thời trước. Hàm rename() 
 *  không sao chép nội dung file, mà chỉ thay đổi metadata của file trong hệ thống.
 *  File temp mới được ghi xong và nằm trên ô nhớ khác của ổ đĩa, file gốc vẫn
 *  nằm nguyên ở địa chỉ cũ. Khi rename() được gọi, hệ điều hành chỉ cần cập nhật
 *  con trỏ từ file gốc sang file tạm, quá trình này rất nhanh và ít rủi ro. Nếu có lỗi trong quá trình ghi file tạm,
 *  file gốc vẫn còn nguyên vẹn. 
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>  // for std::remove and std::rename
#include <vector>

struct Song {
    std::string title;
    int duration;       // duration in seconds
};

// Function to save songs to a file safely
bool safeSavePlaylist(const std::vector<Song>& playlist, const std::string& filename) 
{
    // Create a temporary file name
    std::string tempFilename = filename + ".tmp";

    // Open the temporary file for writing
    std::ofstream outFile(tempFilename);

    if (!outFile) {
        std::cerr << "[ERR] Canot open temp file.\n";
        return false;
    }

    // Write songs to the temporary file
    for (const auto& song : playlist) {
        outFile << song.title << "," << song.duration << std::endl;
    }

    // Check for write errors (Stream State)
    if (outFile.fail()) {
        std::cerr << "[ERR] Write operation failed.\n";
        outFile.close();
        std::remove(tempFilename.c_str()); // Remove temp file
        return false;
    }

    // Close the temporary file and make sure flush is successful
    outFile.close();


    int result = std::rename(tempFilename.c_str(), filename.c_str());

    if (result != 0) {
        std::cerr << "[ERR] Failed to rename temp file to target file.\n";
        return false;
    }

    std::cout << "[INFO] Playlist saved successfully to " << std::endl;
    return true;
}

int main() 
{
    std::vector<Song> playlist = {
        {"Song A", 210},
        {"Song B", 180},
        {"Song C", 240}
    };

    std::string filename = "playlist.txt";

    if (safeSavePlaylist(playlist, filename)) {
        std::cout << "Playlist saved successfully." << std::endl;
    } else {
        std::cout << "Failed to save playlist." << std::endl;
    }

    return 0;
}
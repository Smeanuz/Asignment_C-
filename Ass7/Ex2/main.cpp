
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 2: The Pitfall of Returning a Reference to a Local Variable
 * 
 * ANALYSIS: Dangling pointer
 *  - Khi một hàm trả về tham chiếu hoặc con trỏ đến một biến cục bộ,
 *    biến đó sẽ bị hủy khi hàm kết thúc.
 *  - Việc truy cập biến này sau đó dẫn đến hành vi không xác định (undefined behavior).
 *  - Chương trình có thể bị crash (Segmentation Fault)
 *  - Hoặc có thể trả về giá trị rác (garbage value), dẫn đến lỗi logic khó phát hiện.
 * 
 * Các lý thuyết liên quan:
 *  - Stack frame: mỗi khi hàm được gọi, mot khung ngăn xếp (stack frame) mới
 *    được tạo ra để lưu trữ các biến cục bộ và thông tin điều khiển.
 *  - Biến cục bộ được lưu trữ trong stack frame của hàm. Khi hàm kết thúc,
 *    stack frame bị hủy và bộ nhớ được giải phóng.
 *  - Vì biến cục bộ không còn tồn tại sau khi hàm kết thúc,
 *    tham chiếu hoặc con trỏ trỏ đến biến đó trở thành "dangling".
 */

#include <iostream>

struct Song {
    std::string title;
};

Song g_playlist[100];

/*----------Error Code--------------*/
Song& findSongByTitleBad(const std::string& title) {
    for (int i = 0; i < 100; ++i) {
        if (g_playlist[i].title == title) {
            return g_playlist[i]; // OK: Returning a reference to a global object
        }
    }
    
    Song dummySong; // Local variable, exists on the STACK
    dummySong.title = "Not Found";
    return dummySong; // VERY DANGEROUS: Returning a reference to a local variable
}

// Method 1: Using pointer:
Song* findSongByTitlePointer(const std::string& title) {
    for (int i = 0; i < 100; ++i) {
        if (g_playlist[i].title == title) {
            return &g_playlist[i]; // OK: Returning address of a global object
        }
    }
    
    return nullptr; // Indicate not found
}

// Method2: Using std::optional (C++17 and later)
#include <optional>
#include <functional>

std::optional<std::reference_wrapper<Song>> findSongByTitleOOptional(const std::string& title) {
    for (int i = 0; i < 100; ++i) {
        if (g_playlist[i].title == title) {
            return std::ref(g_playlist[i]); // OK: Returning a reference to a global object
        }
    }
    
    return std::nullopt; // Indicate not found
}

// Method 3: Exeption Handling
#include <stdexcept>
Song& findSongByTitleException(const std::string& title) {
    for (int i = 0; i < 100; ++i) {
        if (g_playlist[i].title == title) {
            return g_playlist[i]; // OK: Returning a reference to a global object
        }
    }
    
    throw std::runtime_error("Song not found");
}

int main() {
    // Populate playlist for demonstration
    g_playlist[0].title = "Song A";
    g_playlist[1].title = "Song B";

    // Error Code Demonstration
    // Song& songBad = findSongByTitleBad("Song C");
    // std::cout << "Bad Method: " << songBad.title << std::endl; // Undefined behavior

    // Pointer Method Demonstration
    Song* songPtr = findSongByTitlePointer("Song C");
    if (songPtr) {
        std::cout << "Pointer Method: " << songPtr->title << std::endl;
    } else {
        std::cout << "Pointer Method: Song not found" << std::endl;
    }

    // Optional Method Demonstration
    auto songOpt = findSongByTitleOOptional("Song C");
    if (songOpt) {
        std::cout << "Optional Method: " << songOpt->get().title << std::endl;
    } else {
        std::cout << "Optional Method: Song not found" << std::endl;
    }

    // Exception Handling Method Demonstration
    try {
        Song& songEx = findSongByTitleException("Song C");
        std::cout << "Exception Method: " << songEx.title << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Exception Method: " << e.what() << std::endl;
    }

    return 0;
}

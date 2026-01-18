
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 14/01/2026
 * 
 * Exercise 2: Optimizing The Memory Buffwe for Album Art
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Stack memory có kích thước hạn chế (thường vài MB). Khi lưu trữ dung lượng lớn
 * có thể khiến gây tràn stack (stack overflow).
 * Khi khởi tạo biến imageBuffer trên stack:
 *   - Bộ nhớ được cấp phát trên stack.
 *   - Kích thước lớn có thể vượt quá giới hạn stack.
 *   - Khi hàm kết thúc, bộ nhớ bị giải phóng.
 *   - Lần gọi tiếp theo, bộ nhớ lại được cấp phát lại trên stack. 
 *  
 * SOLUTION:
 * ---------------------
 * Sử dụng bộ nhớ heap để lưu trữ buffer:
 *  - Cấp phát bộ nhớ động với new/malloc.
 *  - Kích thước lớn không bị giới hạn như stack.
 *  - Bộ nhớ tồn tại cho đến khi giải phóng thủ công với delete/free.
 *  - Cần quản lý bộ nhớ để tránh rò rỉ (memory leak).
 */

#include <iostream>

/*---------------Code lỗi-------------------*/
bool processAlbumArtBad(const char* imagePath) {
    // ...
    // PROBLEM: Allocating a 5MB array on the STACK memory
    char imageBuffer[5 * 1024 * 1024]; 
    
    // ... logic to read the image file into imageBuffer and process it
    // The allocation above can cause an immediate crash on a system
    // with a limited stack (e.g., 1MB).
    
    return true;
}

/*---------------Code tối ưu-------------------*/
bool processAlbumArt(const char* imagePath) {
    // Allocate a 5MB buffer on the HEAP memory
    char* imageBuffer = new char[5 * 1024 * 1024]; 
    
    // ... logic to read the image file into imageBuffer and process it
    
    // Free the allocated memory to avoid memory leaks
    delete[] imageBuffer; 
    
    return true;
}


int main() {
    const char* dummyImagePath = "path/to/album_art.jpg";

    std::cout << "Processing album art with bad method (stack allocation)..." << std::endl;
    // if (processAlbumArtBad(dummyImagePath)) {
    //     std::cout << "Processed album art (bad method) successfully." << std::endl;
    // } else {
    //     std::cout << "Failed to process album art (bad method)." << std::endl;
    // }

    std::cout << "Processing album art with optimized method (heap allocation)..." << std::endl;
    if (processAlbumArt(dummyImagePath)) {
        std::cout << "Processed album art (optimized method) successfully." << std::endl;
    } else {
        std::cout << "Failed to process album art (optimized method)." << std::endl;
    }

    return 0;
}


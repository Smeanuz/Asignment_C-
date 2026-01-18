
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 14/01/2025
 * 
 * Exercise 1: Stack Overflow Error from Recursive Playlist Parsing]
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Việc sử dụng đệ quy sâu để phân tích playlist có thể dẫn đến lỗi tràn stack (stack overflow).
 * Mỗi lần gọi hàm đệ quy, một khung ngăn xếp (stack frame) mới được tạo trên stack.
 * Nếu độ sâu đệ quy quá lớn, nó có thể vượt quá giới hạn kích thước stack của hệ thống,
 * dẫn đến lỗi tràn stack và chương trình bị crash.         
 * 
 * Khái niệm liên quan: STACK OVERFLOW
 * - Xảy ra khi ngăn xếp (stack) vượt quá giới hạn bộ nhớ được cấp phát.
 * - Thường do đệ quy quá sâu hoặc khai báo biến cục bộ quá lớn.
 * - Khi stack overflow xảy ra, chương trình thường bị crash hoặc hành vi không xác định.
 * 
 * SOLUTION:
 * ---------------------
 * Sử dụng iteration (vòng lặp) thay vì đệ quy để phân tích playlist:
 * - Giảm thiểu việc tạo nhiều khung ngăn xếp.
 * - Kiểm soát tốt hơn việc sử dụng bộ nhớ stack.
 * - Tránh nguy cơ tràn stack do đệ quy sâu.
 * - Cải thiện hiệu suất và độ ổn định của chương trình.
 * - Sử dụng heap thay vì stack cho các cấu trúc dữ liệu lớn nếu cần.
 */     

#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>

// Mock playlist structure
struct Playlist {
    std::vector<Playlist> nestedPlaylists;
};


/*--------------Code lỗi--------------*/
void parsePlaylistBad(Playlist list) {
    // Each time this function is called, a new "stack frame" is created on STACK memory
    for (const auto& nestedList : list.nestedPlaylists) {
        parsePlaylistBad(nestedList); // Recursive call
    }
}

/*--------------Code tối ưu--------------*/
void parsePlaylist(const Playlist& root) 
{
    std::stack<const Playlist*> stack;
    std::unordered_set<const Playlist*> visited;

    stack.push(&root);

    while(!stack.empty()) {
        const Playlist* current = stack.top();
        stack.pop();

        //Phát hiện vòng lặp
        if (visited.count(current)) {
            continue;
        }
        visited.insert(current);

        // Xử lý playlist hiện tại
        for (const auto& nestedList : current->nestedPlaylists) {
            stack.push(&nestedList);
        }
    }
}


int main()
{
    Playlist root;
    // ... populate playlist with nested playlists

    std::cout << "Parsing playlist with optimized method (iteration)..." << std::endl;
    parsePlaylist(root);
    std::cout << "Finished parsing playlist." << std::endl;

    return 0;
}

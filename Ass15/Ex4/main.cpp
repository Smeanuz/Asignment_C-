
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 27/01/2026
 * 
 * Exercise 4: Template Specialization for Data Serialization
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring> // Cho memcpy (nếu cần)

// Định nghĩa struct Song để test
struct Song {
    int id;
    std::string title;
};

// ==========================================
// 1. BASE TEMPLATE (Generic Case)
// ==========================================
// Mặc định: Coi T là POD (Plain Old Data) và copy thẳng bộ nhớ (Raw Copy).
// Dành cho: int, float, double, bool, struct đơn giản...
template <typename T>
void serialize(std::ostream& stream, const T& data) {
    std::cout << "[Base Template] Serializing POD type of size " << sizeof(T) << " bytes.\n";
    // Ép kiểu địa chỉ của data thành char* để ghi từng byte
    stream.write(reinterpret_cast<const char*>(&data), sizeof(T));
}

// ==========================================
// 2. TEMPLATE SPECIALIZATION: std::string
// ==========================================
// std::string chứa con trỏ heap bên trong. Nếu dùng Base Template, ta chỉ ghi được địa chỉ con trỏ
// (vô nghĩa khi đọc lại). Ta phải ghi: [Độ dài] + [Nội dung chuỗi].
template <>
void serialize<std::string>(std::ostream& stream, const std::string& data) {
    std::cout << "[Specialization] Serializing std::string: \"" << data << "\"\n";

    // Bước 1: Ghi độ dài chuỗi (size_t)
    size_t len = data.size();
    // Tận dụng Base Template để ghi số nguyên size_t (vì size_t là POD)
    serialize(stream, len); 

    // Bước 2: Ghi nội dung chuỗi (Raw chars)
    // data.data() trả về con trỏ tới mảng ký tự thực tế
    stream.write(data.data(), len);
}

// ==========================================
// 3. TEMPLATE SPECIALIZATION: Song
// ==========================================
// Song là struct phức tạp (chứa string), không thể raw copy cả cục.
// Ta phải serialize từng thành viên một.
template <>
void serialize<Song>(std::ostream& stream, const Song& data) {
    std::cout << "[Specialization] Serializing Song object...\n";

    // Member 1: ID (int) -> Trình biên dịch sẽ chọn Base Template
    serialize(stream, data.id);

    // Member 2: Title (string) -> Trình biên dịch sẽ chọn String Specialization
    serialize(stream, data.title);
}

// ==========================================
// MAIN TEST
// ==========================================
int main() {
    // Mở file giả lập (chỉ để demo luồng, không ghi thật ra đĩa để code gọn)
    // std::ofstream file("data.bin", std::ios::binary); 
    // Ta dùng std::cout như một stream để xem log, trong thực tế sẽ là file stream.
    // Để code chạy được với cout (vì cout không có write kiểu binary), 
    // ta sẽ giả lập stream bằng một stringstream hoặc chỉ in log logic.
    
    // Ở đây tôi dùng một dummy stream để code biên dịch và chạy đúng logic phân luồng.
    std::stringstream buffer; 

    // --- TEST 1: Serialize POD (int) ---
    int myNumber = 42;
    std::cout << "--- Test 1: Integer ---\n";
    serialize(buffer, myNumber); 
    // -> Gọi Base Template

    std::cout << "\n";

    // --- TEST 2: Serialize Complex Object (Song) ---
    Song mySong;
    mySong.id = 101;
    mySong.title = "Shape of You";

    std::cout << "--- Test 2: Song Object ---\n";
    serialize(buffer, mySong);
    // -> Gọi Song Specialization
    //    -> Bên trong gọi Base Template (cho id)
    //    -> Bên trong gọi String Specialization (cho title)

    return 0;
}


// Tại sao trình biên dịch biết hàm nào để gọi? Quá trình này gọi là Template Instantiation & Overload Resolution.
// Khi bạn viết serialize(buffer, mySong); trong hàm main:
// Bước 1: Tra cứu (Lookup): Trình biên dịch tìm thấy tên hàm serialize. Nó thấy có một Base Template và các bản Specialization.
// Bước 2: So khớp kiểu (Type Matching):
// Đối số truyền vào là Song.
// Trình biên dịch kiểm tra: "Có bản chuyên biệt hóa (Specialization) nào dành riêng cho Song không?".
// Có! (template <> void serialize<Song>...).
// -> Quyết định: Sử dụng bản Specialization này.
// Khi bên trong hàm serialize<Song>, bạn gọi serialize(stream, data.id) (với id là int):
// Trình biên dịch kiểm tra: "Có bản chuyên biệt hóa nào cho int không?".
// Không.
// -> Quyết định: Sử dụng Base Template, tự động sinh ra code serialize<int> từ khuôn mẫu gốc.
// Tại sao Base Template nguy hiểm cho std::string?
// Giả sử bộ nhớ của std::string title = "Hello" trông như thế này:
// Stack (Tại địa chỉ 0x100): [ Size: 5 | Capacity: 15 | Pointer: 0x9000 ]
// Heap (Tại địa chỉ 0x9000): {'H', 'e', 'l', 'l', 'o'}
// Nếu dùng Base Template (Raw Copy):
// Nó sẽ copy đúng cái cụm ở Stack (Size, Capacity, Pointer 0x9000) ghi vào file.
// Khi bạn đọc file này lên ở một lần chạy sau (hoặc máy khác), chương trình sẽ load lại con trỏ 0x9000.
// Nhưng lúc này địa chỉ 0x9000 trên Heap là rác hoặc thuộc về người khác!
// -> Kết quả: Truy cập bộ nhớ trái phép (Segfault) hoặc hiện ký tự rác.
// Đó là lý do ta BẮT BUỘC phải dùng Specialization để "Deep Copy" (lưu nội dung thực sự) cho các kiểu dữ liệu phức tạp.
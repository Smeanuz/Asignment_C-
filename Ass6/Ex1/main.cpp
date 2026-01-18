
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 18/01/2026
 * 
 * Exercise 1: Analyzing the Trade-offs of Linking a Codec Library
 * 
 * 1. Kích thước của file thực thi:
 *  - Static Linking: File thực thi sẽ lớn hơn vì toàn bộ mã của thư viện
 *    được nhúng trực tiếp vào trong file thực thi.
 *  - Dynamic Linking: File thực thi nhỏ hơn vì chỉ chứa các tham chiếu
 *    đến thư viện bên ngoài.
 * 
 * 2. Tổng mức sử dụng RAM:
 *  - Static Linking: Mỗi tiến trình sử dụng file thực thi sẽ có bản sao riêng
 *   của mã thư viện trong bộ nhớ, dẫn đến sử dụng RAM cao hơn.
 *  - Dynamic Linking: Thư viện được load một lần và chia sẻ giữa các tiến trình,
 *   giảm mức sử dụng RAM tổng thể.
 * 
 * 3. Thời gian khởi động của ứng dụng:
 *  - Static Linking: Thời gian khởi động nhanh hơn vì không cần phải tìm và
 *    load thư viện bên ngoài.
 *  - Dynamic Linking: Thời gian khởi động chậm hơn do cần phải load thư viện
 *    từ đĩa.
 * 
 * -> Đánh giá rủi ro và lợi ích:
 *  - Static Linking - An toàn và ổn định.
 *      + Không phụ thuộc vào thư viện bên ngoài.
 *      + Tránh các rủi ro thiếu file, phiên bản không tương thích.
 * 
 *  - Dynamic Linking - Linh hoạt và tiết kiệm tài nguyên.
 *      + Cập nhật thư viện dễ dàng mà không cần biên dịch lại ứng dụng.
 *      + Tiết kiệm bộ nhớ khi nhiều ứng dụng sử dụng cùng một thư viện.
 * 
 *  Câu lệnh build:
 *   - Static Linking:
 *    g++ main.cpp /path/to/libFLAC.a -o app
 *   - Dynamic Linking:
 *    g++ main.cpp -lFLAC -L/path/to/lib -o app
 */
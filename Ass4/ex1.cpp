
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 14/01/2026
 * 
 * Exercise 1: Conditional Compilation for Different Car Models
 * 
 * ANALYSIS:
 * ---------------------
 * Vấn đề: Mã nguồn cần được biên dịch khác nhau tùy theo mẫu xe hơi.
 *  - Không sử dụng else/if vì phải link cả 2 thư viện.
 *  - Dùng #ifdef để chọn mã nguồn phù hợp tại thời điểm biên dịch.
 *  - Chỉ một nhánh code được compile, tránh xung đột.
 */


// Mock libraries from different vendors
void NVIDIA_init() { /* ... */ }
void BOSCH_init() { /* ... */ }
void initializeAudioHardware() {
// TODO: Use preprocessor directives here
// to call the correct init() function for each model.
    #if defined(MODEL_S)
        NVIDIA_init();
    #elif defined(MODEL_X)
        BOSCH_init();
    #else
// TODO: Add an #error directive if no model is selected.
        #error "No car model defined! Please compile with -DMODEL_S or -DMODEL_X."
    #endif
}

int main() {
    initializeAudioHardware();
    return 0;
}


/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 27/01/2026
 * 
 * Exercise 1: Organizing Code with Namespaces and Name Collisions
 * 
 * 
 * Không nên sử dụng 'using namespace' trong file header vì gây Namespace Pollution.
 *  - Lệnh #include thực chất copy toàn bộ nội dung file header vào file hiện tại.
 *  Nếu header có 'using namespace', nó sẽ ảnh hưởng đến tất cả file cpp nào include header đó.
 *  Nó sẽ ép buộc mọi file cpp phải chịu ảnh hưởng của namespace đó.
 *  - Nếu có nhiều header cùng sử dụng 'using namespace' giống nhau, nhưng có chung một class.
 *  Trình biên dịch sẽ không biết sử dụng class nào.
 * 
 */

// --- AudioEngine.h ---
#pragma once
#include <iostream>

namespace Audio {
    struct Manager {
        void init() {
            std::cout << "[Audio] Sound Engine Initialized.\n";
        }
    };
}

// --- UIFramework.h ---
#pragma once
#include <iostream>

namespace UI {
    struct Manager {
        void draw() {
            std::cout << "[UI] Interface Rendered.\n";
        }
    };
}

// --- Database.h ---
#pragma once
#include <iostream>
namespace Database {
    struct Manager {
        void connect() {
            std::cout << "[Database] Database Connection Established.\n";
        }
    };
}


// #include "AudioEngine.h"
// #include "UIFramework.h"
// #include "Database.h"

int main() {
    // Sử dụng các Manager từ các namespace khác nhau
    Audio::Manager audioMgr;
    UI::Manager uiMgr;
    Database::Manager dbMgr;

    std::cout << "--- Initializing Systems ---\n";
    audioMgr.init();
    uiMgr.draw();
    dbMgr.connect();

    std::cout << "\n--- Inside local Scope ---\n";
    {
        using Database::Manager; // Chỉ dùng Manager từ namespace Database trong scope này
        Manager localDbMgr; // Tương đương Database::Manager
        localDbMgr.connect();

        Audio::Manager anotherAudioMgr; // Vẫn có thể dùng Audio::Manager bằng cách chỉ định rõ ràng
        anotherAudioMgr.init();
    }

    // Ra ngoài scope, không còn sử dụng được manager nữa.

    return 0;
}
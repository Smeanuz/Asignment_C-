
#include <iostream>

class MediaObject {
public:
    MediaObject() { std::cout << "1. MediaObject Constructor\n"; }
    // Destructor phải là virtual 
    virtual ~MediaObject() { std::cout << "8. MediaObject Destructor\n"; }
};

class AudioTrack : public MediaObject {
public:
    AudioTrack() { std::cout << "2. AudioTrack Constructor\n"; }
    ~AudioTrack() { std::cout << "7. AudioTrack Destructor\n"; }
};

class LosslessAudioTrack : public AudioTrack {
public:
    LosslessAudioTrack() { std::cout << "3. LosslessAudioTrack Constructor\n"; }
    ~LosslessAudioTrack() { std::cout << "6. LosslessAudioTrack Destructor\n"; }
};

class FLACFile : public LosslessAudioTrack {
public:
    FLACFile() { std::cout << "4. FLACFile Constructor\n"; }
    ~FLACFile() { std::cout << "5. FLACFile Destructor\n"; }
};

int main() {
    std::cout << "--- Creating FLACFile ---\n";
    {
        FLACFile myFile; 
    } // myFile đi ra khỏi phạm vi (Scope) -> Destructor được gọi tự động
    std::cout << "--- End of Scope ---\n";
    return 0;
}

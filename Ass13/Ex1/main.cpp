
#include <iostream>

class DigitalAsset {
public:
    long licenseID;

    // Constructor
    DigitalAsset(long id = 0) : licenseID(id) {}
};

class AudioTrack : virtual public DigitalAsset {
public:
    int bitrate;      // in kbps
};

class Playable : virtual public DigitalAsset {
public:
    float duration;   // in seconds     
};

class PlayableSong : public AudioTrack, public Playable {
public:
    void showInfo() {
        std::cout << "License ID: " << licenseID << "\n";
        std::cout << "Bitrate: " << bitrate << " kbps\n";
        std::cout << "Duration: " << duration << " seconds\n";
    }
};

void test() {
    PlayableSong song;
    song.licenseID = 123456;

    song.showInfo();
}

int main() {
    test();
    return 0;
}
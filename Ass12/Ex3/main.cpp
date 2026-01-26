
/**
 * Author: Nhat Minh (MinhNN115)
 * Date: 26/01/2026
 * 
 * Exercise 3: Applying the Abstract Factory Pattern for Audio Decoders
 * 
 * 
 */

#include <iostream>
#include <vector>
#include <string>

struct Buffer {
    std::vector<char> data;
};

// Abstract product: AudioDecoder
class AudioDecoder {
public:
    // Vitual destructor
    virtual ~AudioDecoder() {};

    // Pure virtual function: Giải mã 1 chunk dữ liệu
    virtual bool decodeChunk(const Buffer& input, Buffer& output) = 0;

    // Debug
    virtual std::string getName() const = 0;

};

// Concrete product: MP3Decoder
class MP3Decoder : public AudioDecoder {
public:
    bool decodeChunk(const Buffer& input, Buffer& output) override {
        std::cout << "   [MP3 Algorithm] Decoding frame header & Huffman data...\n";
        return true;
    }

    std::string getName() const override {
        return "MP3 Decoder";
    }
};


// Concrete product: FLACDecoder
class FLACDecoder : public AudioDecoder {
public:
    bool decodeChunk(const Buffer& input, Buffer& output) override {
        std::cout << "   [FLAC Algorithm] Decoding Rice-coded data...\n";
        return true;
    }

    std::string getName() const override {
        return "FLAC Decoder";
    }
};

//--------------------------------

// Abstract factory: DecoderFactory
class DecoderFactory {
public:
    virtual ~DecoderFactory() {};

    // Factory method: Trả con trỏ tới class abstract cha
    virtual AudioDecoder* createDecoder() = 0;
};

// Concrete factory: MP3DecoderFactory
class MP3DecoderFactory : public DecoderFactory {
public: 
    AudioDecoder* createDecoder() override {
        return new MP3Decoder();
    }
};

// Concrete factory: FLACDecoderFactory
class FLACDecoderFactory : public DecoderFactory {
public:
    AudioDecoder* createDecoder() override {
        return new FLACDecoder();
    }
};

//--------------------------------

// Client code

/**
 * Hàm này đại diện cho core Engine của Player
 * QUAN TRỌNG: Hàm này không biết gì về các class con của AudioDecoder
 * Nó chỉ làm việc với abstract class
 */
void playAudioFile(DecoderFactory* factory) {
    // Tạo decoder thông qua factory
    AudioDecoder* decoder = factory->createDecoder();

    std::cout << ">>> Initializing Player with: " << decoder->getName() << "\n";

    // Mô phỏng quá trình decode
    Buffer rawData, pcmData;
    decoder->decodeChunk(rawData, pcmData);     // Đa hình ở đây

    // Giải phóng bộ nhớ
    delete decoder;
}

int main() {
    // Kịch bản A: Người dùng mở file .mp3
    // Ứng dụng chỉ cần chọn đúng Factory ở lớp ngoài cùng
    std::cout << "--- User selects song.mp3 ---\n";
    DecoderFactory* mp3Factory = new MP3DecoderFactory();
    playAudioFile(mp3Factory);

    // Kịch bản B: Người dùng mở file .flac
    std::cout << "\n--- User selects song.flac ---\n";
    DecoderFactory* flacFactory = new FLACDecoderFactory();
    playAudioFile(flacFactory);

    // Clean up factories
    delete mp3Factory;
    delete flacFactory;

    return 0;
}

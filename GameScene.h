#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "Types.h"
#include <vector>

class GameScene {
private:
    int currentFrame;
    Resolution res;

public:
    GameScene(int width, int height) : currentFrame(0), res{width, height} {}

    // Cập nhật trạng thái chuyển động theo thời gian thực
    void update() {
        currentFrame++;
    }

    int getFrameNumber() const {
        return currentFrame;
    }

    Resolution getResolution() const {
        return res;
    }

    // Mô phỏng vẽ trạng thái trò chơi ra bộ đệm điểm ảnh
    void renderFrameToBuffer(std::vector<Color>& pixelBuffer) const {
        pixelBuffer.clear();
        for (int y = 0; y < res.height; ++y) {
            for (int x = 0; x < res.width; ++x) {
                unsigned char r = static_cast<unsigned char>((x + currentFrame * 5) % 255);
                unsigned char g = static_cast<unsigned char>((y + currentFrame * 3) % 255);
                unsigned char b = 150;
                
                pixelBuffer.push_back({r, g, b});
            }
        }
    }
};

#endif // GAME_SCENE_H

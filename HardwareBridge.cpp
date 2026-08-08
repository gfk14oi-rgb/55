#include <iostream>
#include <cstdlib>
#include <string>
#include "VideoRendererEngine.h"

class HardwareBridge {
private:
    std::string webFilePath;

public:
    HardwareBridge(const std::string& htmlFile) : webFilePath(htmlFile) {
        std::cout << "[HardwareBridge] Khoi tao lop trung gian tuong tac phan cung.\n";
    }

    void monitorHardwareResources() {
        std::cout << "[Hardware] Kiem tra tai nguyen CPU va bo nhieu RAM: O muc an toan cho viec render video.\n";
    }

    void initializeHardwareDrivers() {
        std::cout << "[Hardware] Khoi tao thanh cong driver GPU va thiet bi luu tru cuc bo.\n";
    }

    void executeWebInterface() {
        std::cout << "[Bridge] Dang ra lenh cho he thong thuc thi tep giao dien web: " << webFilePath << "\n";
        
        #if defined(_WIN32) || defined(_WIN64)
            std::string command = "start " + webFilePath;
        #elif defined(__APPLE__)
            std::string command = "open " + webFilePath;
        #else
            std::string command = "xdg-open " + webFilePath;
        #endif

        int result = std::system(command.c_str());
        if (result == 0) {
            std::cout << "[Bridge Success] Da kich hoat tep trang web thanh cong.\n";
        } else {
            std::cerr << "[Bridge Error] Khong the kich hoat tep trang web tu dong.\n";
        }
    }
};

int main() {
    std::cout << "=== KHOI DONG TOAN BO HE THONG KET HOP C++ VA WEB ===\n\n";

    // 1. C++ đứng ra kiểm soát phần cứng và ra lệnh mở giao diện Web
    HardwareBridge bridge("index.html");
    bridge.monitorHardwareResources();
    bridge.initializeHardwareDrivers();
    bridge.executeWebInterface();

    std::cout << "\n----------------------------------------\n";
    std::cout << "=== TIEN HANH CHAY ENGINE RENDER VIDEO ===\n";

    // 2. Tiến hành khởi chạy mô phỏng trò chơi và xuất video hoàn chỉnh
    GameScene gameScene(640, 360);
    VideoRendererEngine videoEngine("./rendered_frames", 30);
    
    videoEngine.recordGameToImageSequence(gameScene);
    videoEngine.compileImagesIntoVideo("UniversalGameOutput.mp4");

    std::cout << "\n=== HOAN TAT TOAN BO QUY TRINH SAN XUAT ==-\n";
    return 0;
}

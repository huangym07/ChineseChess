#include <Windows.h>
#include "Game.h"

// // ANSI 转义序列颜色
// const std::string RESET = "\033[0m";
// const std::string RED = "\033[31;47m"; // 白底红字
// const std::string BLACK = "\033[30;47m"; // 白底黑字

int main() {
    // Windows API, 设置控制台为 UTF-8 模式
    SetConsoleOutputCP(CP_UTF8);

    Game game;
    game.start();
   
    return 0;
}
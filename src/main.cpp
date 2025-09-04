#include <Windows.h>
#include "Game.h"

int main() {
    // Windows API, 设置控制台为 UTF-8 模式
    SetConsoleOutputCP(CP_UTF8);

    Game game;
    game.start();
   
    return 0;
}
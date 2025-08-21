#include <iostream>
#include <Windows.h>

// ANSI 转义序列颜色
const std::string RESET = "\033[0m";
const std::string RED = "\033[31;47m"; // 白底红字
const std::string BLACK = "\033[30;47m"; // 白底黑字

// 获取棋子
std::string chess_piece(const std::string &piece, const std::string &color) {
    return color + piece + RESET;
}

int main() {
    // Windows API, 设置控制台为 UTF-8 模式
    SetConsoleOutputCP(CP_UTF8);
    
    std::cout << "中国象棋红帅：" << chess_piece("帅", RED) << std::endl;
    std::cout << "中国象棋黑将：" << chess_piece("将", BLACK) << std::endl;
    std::cout << "中国象棋黑将：" << chess_piece("", RED) << std::endl;
    std::cout << "中国象棋黑将：" << chess_piece("空", RED) << std::endl;
    
    return 0;
}
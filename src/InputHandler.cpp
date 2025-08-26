#include "InputHandler.h"
#include <ios>
#include <iostream>
#include <limits>

int InputHandler::read_int_range(int min, int max) {
    std::cout << "请输入 [" << min << ", " << max << "] 中的整数: ";

    int op = 0;
    while (true) {
        if ((std::cin >> op) && op <= max && op >= min) {
            // 清除缓冲区残留的换行符，
            // 避免影响后续可能进行的字符串读取操作（如 getline）
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return op;
        }

        std::cout << "输入不合法，请重新输入: ";
        // 清除错误状态
        std::cin.clear();
        // 清除缓冲区的错误内容
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
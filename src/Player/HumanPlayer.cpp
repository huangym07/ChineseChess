#include "Player/HumanPlayer.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include <limits>
#include <string>
#include <utility>

HumanPlayer::HumanPlayer(PlayerInfo player_info) : Player(player_info) {}

std::pair<Position, Position> HumanPlayer::move_chess(GameContext &context) const {
    std::pair<Position, Position> ret;
    std::string input;

    while (true) {
        std::cout << "请按照 (x1, y1) -> (x2, y2) 的形式输入走棋决策(用半角符号): ";

        std::getline(std::cin, input);

        if (4 == sscanf(input.c_str(), "(%d, %d) -> (%d, %d)", &ret.first.x, &ret.first.y,
                        &ret.second.x, &ret.second.y)) {
            break;
        }

        std::cout << "输入格式不合法" << std::endl;

        std::cin.clear();
    }

    return ret;
}

bool HumanPlayer::ask_undo_request() const {
    std::cout << "是否悔棋(请输入 y or n, 分别表示悔棋或不悔棋): ";

    // 默认不悔棋
    char op = 'n';
    while (std::cin >> op) {
        if (op == 'y') {
            std::cout << "已悔棋\n";
            break;
        } else if (op == 'n') {
            std::cout << "不进行悔棋\n";
            break;
        } else {
            std::cout << "输入有误, 请重新输入: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<int>::max(), '\n');
        }
    }

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<int>::max(), '\n');
    return op == 'y';
}
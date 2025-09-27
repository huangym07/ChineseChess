#include "Player/HumanPlayer.h"
#include "Common/CoreType.h"
#include "GameContext.h"
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
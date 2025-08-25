#include "Game.h"
#include "GameMode.h"
#include "GameModeFactory.h"
#include <cassert>
#include <ios>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

const std::vector<std::pair<GameOption, std::string>> Game::menu_{
    {GameOption::STANDARD_PvE, "标准象棋人机对战"},
    {GameOption::EXIT, "退出游戏"},
};

GameOption Game::menu() const {
    int op = 0;

    std::cout << "开始菜单\n";
    for (int i = 0; i < menu_.size(); ++i) {
        std::cout << i + 1 << ". " << menu_[i].second << '\n';
    }
    std::cout << "请输入 1~" << menu_.size() << " 之间的整数来选择：";

    while (true) {
        if ((std::cin >> op) && op >= 1 && op <= menu_.size()) {
            std::cout << "您选择了 " << op << ". " << menu_[op - 1].second << '\n';
            return menu_[op - 1].first;
        } else {
            std::cout << "输入不合法，请重新选择：";
            // 清除错误状态
            std::cin.clear();
            // 丢弃缓冲区错误内容
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Game::start() {
    GameOption op = menu();
    if (GameOption::EXIT == op) {
        std::cout << "已退出游戏\n";
        return;
    }
    auto game_mode = GameModeFactory::create_mode(op);
    if (game_mode) {
        game_mode->start(context_);
    } else {
        assert(false && "游戏模式创建失败");
        std::cerr << "创建游戏模式时发生未知错误，请联系开发者\n";
    }
}
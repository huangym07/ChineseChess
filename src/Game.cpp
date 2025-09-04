#include "Game.h"
#include "Common/InputHandler.h"
#include "GameMode/GameMode.h"
#include "GameMode/GameModeFactory.h"
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

const std::vector<std::pair<GameOption, std::string>> Game::menu_{
    {GameOption::STANDARD_PvE, "标准象棋人机对战"},
    {GameOption::EXIT, "退出游戏"},
};

GameOption Game::menu() const {
    std::cout << "开始菜单\n";
    for (int i = 0; i < menu_.size(); ++i) {
        std::cout << i + 1 << ". " << menu_[i].second << '\n';
    }

    int op = InputHandler::read_int_range(1, menu_.size());
    return menu_[op - 1].first;
}

void Game::start() {
    GameOption op = menu();
    if (GameOption::EXIT == op) {
        std::cout << "已退出游戏\n";
        return;
    }

    // 经上面的 GameOption::EXIT 过滤，传入的 op 一定合法，工厂必返回有效实例
    auto game_mode = GameModeFactory::create_mode(op);
    game_mode->init(context_); // 无需对 game_mode 进行 nullptr 检查
}
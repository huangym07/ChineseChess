#include "Game.h"
#include "GameMode.h"
#include "GameModeFactory.h"
#include "InputHandler.h"
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
    auto game_mode = GameModeFactory::create_mode(op);
    if (game_mode) {
        game_mode->init(context_);
    } else {
        assert(false && "游戏模式创建失败");
        std::cerr << "创建游戏模式时发生未知错误，请联系开发者\n";
    }
}
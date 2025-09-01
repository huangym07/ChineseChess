#include "StandardPveMode.h"
#include "AiPlayer.h"
#include "CoreType.h"
#include "GameContext.h"
#include "HumanPlayer.h"
#include "InputHandler.h"
#include "PlayerInfo.h"
#include <cassert>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>

// 初始化玩家：确定阵营，设置难度
// 初始化棋子 TODONEXT：去写 ChessPiece 子类
// 初始化地图
// 初始化流程
// TODO 调用 context.action.run_game() 开始游戏流程
void StandardPveMode::init(GameContext &context) const {
    init_players(context);
    init_pieces(context);
    init_board(context);
    init_action(context);
}

void StandardPveMode::init_players(GameContext &context) const {
    std::cout << "选择阵营: 1. 红方 2. 黑方 3. 随机分配\n";

    int op = InputHandler::read_int_range(1, 3);

    if (3 == op) {
        std::mt19937 engine(std::time(nullptr));
        std::uniform_int_distribution<int> dist(1, 2);
        op = dist(engine);
    }

    // StandardPveMode 游戏模式中，
    // context.players 中先红方，后黑方
    if (1 == op) {
        context.players.push_back(
            std::make_unique<HumanPlayer>(PlayerInfo{PlayerType::Human, SideTag::RED}));
        context.players.push_back(
            std::make_unique<AiPlayer>(PlayerInfo{PlayerType::AI, SideTag::BLACK}));

        assert(nullptr != dynamic_cast<AiPlayer*>(context.players.back().get()));
        set_difficulty(*static_cast<AiPlayer*>(context.players.back().get()));
    } else {
        context.players.push_back(
            std::make_unique<AiPlayer>(PlayerInfo{PlayerType::AI, SideTag::RED}));

        assert(nullptr != dynamic_cast<AiPlayer*>(context.players.back().get()));
        set_difficulty(*static_cast<AiPlayer*>(context.players.back().get()));

        context.players.push_back(
            std::make_unique<HumanPlayer>(PlayerInfo{PlayerType::Human, SideTag::BLACK}));
    }
}

void StandardPveMode::set_difficulty(AiPlayer &ai_player) const {
    std::cout << "选择游戏难度\n";
    int depth = InputHandler::read_int_range(AiPlayer::min_depth(), AiPlayer::max_depth());
    ai_player.set_depth(depth);
}

void StandardPveMode::init_pieces(GameContext &context) const {

}
void StandardPveMode::init_board(GameContext &context) const {
}
void StandardPveMode::init_action(GameContext &context) const {
}
#include "GameMode/StandardPveMode.h"
#include "Common/InputHandler.h"
#include "GameContext.h"
#include "Player/AiPlayer.h"
#include "Player/HumanPlayer.h"
#include "ChessBoard.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "ChessPiece/PieceFactory.h"
#include "Action/TraditionalAction.h"
#include "Evaluator/StandardEvaluator.h"

#include <cassert>
#include <ctime>
#include <iostream>
#include <memory>
#include <random>

// 初始化玩家：确定阵营，设置难度
// 初始化棋子
// 初始化棋盘
// 初始化流程
// 初始化评价器
// 调用 context.action.run_game() 开始游戏流程
void StandardPveMode::init(GameContext &context) const {
    init_players(context);
    init_pieces(context);
    init_board(context);
    init_action(context);
    init_evaluator(context);

    context.action->run_game(context);
}

void StandardPveMode::init_players(GameContext &context) const {
    std::cout << "选择阵营: 1. 红方 2. 黑方 3. 随机分配\n";

    int op = InputHandler::read_int_range(1, 3);

    if (3 == op) {
        std::mt19937 engine(std::time(nullptr));
        std::uniform_int_distribution<int> dist(1, 2);
        op = dist(engine);
    }

    std::cout << "您当前是 " << (op == 1 ? "红" : "黑") << "方 玩家\n";

    // StandardPveMode 游戏模式中，
    // context.players 中先红方，后黑方
    if (1 == op) {
        context.players.push_back(
            std::make_unique<HumanPlayer>(PlayerInfo{PlayerType::Human, SideTag::RED}));
        context.players.push_back(
            std::make_unique<AiPlayer>(PlayerInfo{PlayerType::AI, SideTag::BLACK}));

        assert(nullptr != dynamic_cast<AiPlayer *>(context.players.back().get()));
        set_difficulty(*static_cast<AiPlayer *>(context.players.back().get()));
    } else {
        context.players.push_back(
            std::make_unique<AiPlayer>(PlayerInfo{PlayerType::AI, SideTag::RED}));

        assert(nullptr != dynamic_cast<AiPlayer *>(context.players.back().get()));
        set_difficulty(*static_cast<AiPlayer *>(context.players.back().get()));

        context.players.push_back(
            std::make_unique<HumanPlayer>(PlayerInfo{PlayerType::Human, SideTag::BLACK}));
    }
}

void StandardPveMode::set_difficulty(AiPlayer &ai_player) const {
    std::cout << "选择游戏难度\n";
    int depth = InputHandler::read_int_range(AiPlayer::min_depth(), AiPlayer::max_depth());

    ai_player.set_depth(depth);

    std::cout << "您选择了游戏难度" << depth << "，祝您游戏愉快！\n";
}

void StandardPveMode::init_pieces(GameContext &context) const {
    const auto &piece_configs = StandardChineseChessConfig::get_piece_configs();

    for (const auto &piece_config : piece_configs) {
        context.pieces[piece_config.side_tag].push_back(PieceFactory::create_piece(piece_config));
    }
}
void StandardPveMode::init_board(GameContext &context) const {
    context.board = std::make_unique<ChessBoard>(
        StandardChineseChessConfig::WIDTH, StandardChineseChessConfig::HEIGHT, context.pieces);
}
void StandardPveMode::init_action(GameContext &context) const {
    context.action = std::make_unique<TraditionalAction>();
}
void StandardPveMode::init_evaluator(GameContext &context) const {
    context.evaluator = std::make_unique<StandardEvaluator>();
}
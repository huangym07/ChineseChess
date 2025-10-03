#ifndef CHINESECHESS_GAMECONTEXT_H
#define CHINESECHESS_GAMECONTEXT_H

#include "Action/Action.h"
#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "Command/CommandManager.h"
#include "Common/CoreType.h"
#include "Evaluator/Evaluator.h"
#include "Player/Player.h"
#include <memory>
#include <vector>

struct GameContext {
    std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> pieces; // 棋子序列
    std::vector<std::unique_ptr<Player>> players; // 玩家序列
    std::unique_ptr<ChessBoard> board; // 棋盘
    CommandManager cmd_manager; // 命令管理器
    std::unique_ptr<Action> action; // 流程控制器
    std::unique_ptr<Evaluator> evaluator; // 棋局评价器

    /*
        功能：根据阵营 side_tag 获取只读棋子序列
    */
    const std::vector<std::unique_ptr<ChessPiece>> &get_pieces(SideTag side_tag) const;
};

#endif // CHINESECHESS_GAMECONTEXT_H
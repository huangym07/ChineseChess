#ifndef CHINESECHESS_GAMECONTEXT_H
#define CHINESECHESS_GAMECONTEXT_H

#include "Action/Action.h"
#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "Command/CommandManager.h"
#include "Common/CoreType.h"
#include "Player/Player.h"
#include <memory>
#include <vector>

struct GameContext {
    std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>> pieces;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<ChessBoard> board;
    CommandManager cmd_manager;
    std::unique_ptr<Action> action;

    const std::vector<std::unique_ptr<ChessPiece>> &get_pieces(SideTag side_tag) const;
};

#endif // CHINESECHESS_GAMECONTEXT_H
#ifndef CHINESECHESS_GAMECONTEXT_H
#define CHINESECHESS_GAMECONTEXT_H

#include <memory>
#include <vector>
#include "ChessPiece/ChessPiece.h"
#include "Player/Player.h"
#include "ChessBoard.h"
#include "Command/CommandManager.h"
#include "Action/Action.h"

struct GameContext {
    std::vector<std::unique_ptr<ChessPiece>> pieces;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<ChessBoard> board;
    CommandManager cmd_manager;
    std::unique_ptr<Action> action;
};

#endif // CHINESECHESS_GAMECONTEXT_H
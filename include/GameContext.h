#ifndef CHINESECHESS_GAMECONTEXT_H
#define CHINESECHESS_GAMECONTEXT_H

#include <memory>
#include <vector>
#include "CommandManager.h"

class ChessPiece;
class Player;
class ChessBoard;
class Action;

struct GameContext {
    std::vector<std::unique_ptr<ChessPiece>> pieces;
    std::vector<std::unique_ptr<Player>> players;
    std::unique_ptr<ChessBoard> board;
    CommandManager cmd_manager;
    std::unique_ptr<Action> action;
};

#endif // CHINESECHESS_GAMECONTEXT_H
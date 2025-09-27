#ifndef CHINESECHESS_PLAYER_PLAYER_H
#define CHINESECHESS_PLAYER_PLAYER_H

#include "Common/CoreType.h"
#include <utility>

class GameContext;
class ChessPiece;

class Player {
  protected:
    PlayerInfo player_info_;

  public:
    Player(PlayerInfo player_info);
    PlayerType player_type() const { return player_info_.player_type; }
    SideTag side_tag() const { return player_info_.side_tag; }

    virtual std::pair<Position, Position> move_chess(GameContext &context) const = 0;
    /*
        TODO 为单回速序全动棋预留的接口，未实现
        功能：为参数 piece 进行走棋决策
        返回值：目标位置
    */
    // virtual Position move_chess(GameContext &context, ChessPiece *piece) const = 0;

    /*
        询问是否悔棋
        返回值：true 悔棋，false 不悔棋
    */
    virtual bool ask_undo_request() const { return false; }

    virtual ~Player() = default;
};

#endif // CHINESECHESS_PLAYER_PLAYER_H
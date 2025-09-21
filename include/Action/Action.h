#ifndef CHINESECHESS_ACTION_ACTION_H
#define CHINESECHESS_ACTION_ACTION_H

#include "Common/CoreType.h"
#include <vector>

class GameContext;
class Player;

class Action {
  public:
    virtual void run_game(GameContext &context) const = 0;

    // 检测当前玩家 current_player 是否失败
    // virtual bool check_game_over(GameContext &context, const Player *currrent_palyer) const = 0;

    // virtual std::vector<std::pair<Position, Position>>
    // generate_all_valid_moves(GameContext &context, const Player *current_player) const = 0;

    // TODO
    virtual ~Action() = default;
};

#endif // CHINESECHESS_ACTION_ACTION_H
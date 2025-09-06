#ifndef CHINESECHESS_ACTION_TRADITIONAL_H
#define CHINESECHESS_ACTION_TRADITIONAL_H

#include "Action/Action.h"
#include "GameContext.h"

class TraditionalAction : public Action {
  public:
    void run_game(GameContext &context) const override;

    bool check_game_over(GameContext &context, const Player *cur_player) const override;

    // TODO
};

#endif // CHINESECHESS_ACTION_TRADITIONAL_H
#ifndef CHINESECHESS_ACTION_TRADITIONAL_H
#define CHINESECHESS_ACTION_TRADITIONAL_H

#include "Action/Action.h"
#include "Common/CoreType.h"
#include "GameContext.h"

class TraditionalAction : public Action {
  private:
    // 检测 side_tag 阵营是否被将军
    bool is_checked(const GameContext &context, SideTag side_tag) const;
  public:
    void run_game(GameContext &context) const override;

    // bool check_game_over(GameContext &context, const Player *current_player) const override;

    // std::vector<std::pair<Position, Position>>
    // generate_all_valid_moves(GameContext &context, const Player *current_player) const override;

    // TODO
};

#endif // CHINESECHESS_ACTION_TRADITIONAL_H
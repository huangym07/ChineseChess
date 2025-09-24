#ifndef CHINESECHESS_ACTION_ACTION_H
#define CHINESECHESS_ACTION_ACTION_H

#include "Common/CoreType.h"
#include <vector>

class GameContext;
class Player;

class Action {
  public:
    virtual void run_game(GameContext &context) const = 0;

    // 为阵营 side_tag 生成全部合法走法
    virtual std::vector<std::pair<ChessPiece*, Position>>
    generate_all_valid_moves(GameContext &context, SideTag side_tag) const = 0;

    /*
        检测阵营 side_tag 是否失败
        返回值：true side_tag 阵营游戏失败，false side_tag 阵营游戏未失败
    */
    virtual bool check_game_over(GameContext &context, SideTag side_tag) const = 0;

    virtual ~Action() = default;
};

#endif // CHINESECHESS_ACTION_ACTION_H
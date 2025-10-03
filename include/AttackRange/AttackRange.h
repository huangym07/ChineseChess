#ifndef CHINESECHESS_ATTACKRANGE_ATTACKRANGE_H
#define CHINESECHESS_ATTACKRANGE_ATTACKRANGE_H

#include "Common/CoreType.h"
#include <vector>

class ChessBoard;

class AttackRange {
  protected:
    virtual ~AttackRange() = default;

  public:
    /*
        获取攻击范围
        参数：pos 攻击的发起位置, board 棋盘
        返回值：可以攻击到的位置
    */
    virtual std::vector<Position> get_range(Position pos, const ChessBoard &board) const = 0;
    /*
        获取能攻击到目标位置的攻击发起位置
        参数：target_pos 想要攻击到的目标位置
        返回值：能够攻击到 target_pos 的攻击发起位置
    */
    virtual std::vector<Position> where_can_attack(Position target_pos) const = 0;
};

#endif // CHINESECHESS_ATTACKRANGE_ATTACKRANGE_H
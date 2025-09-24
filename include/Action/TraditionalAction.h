#ifndef CHINESECHESS_ACTION_TRADITIONAL_H
#define CHINESECHESS_ACTION_TRADITIONAL_H

#include "Action/Action.h"
#include "Common/CoreType.h"
#include "GameContext.h"

class TraditionalAction : public Action {
  protected: // 本为 private，为了将军检测单元测试，改成 protected
    // 检测 side_tag 阵营是否被将军
    bool is_checked(const GameContext &context, SideTag side_tag) const;
    /*
        返回值：true 合法，false 不合法
        走棋前合法性判断，用于外界输入的（源坐标，目标坐标）的走棋，包含：
        出界判断，源位置是否有与走棋方阵营一致的棋子，自占判断，棋子基本移动规则，棋子特殊移动规则
    */
    bool check_move_before(const GameContext &context, SideTag side_tag, Position src, Position target) const;
    /*
        返回值：true 合法，false 不合法
        走棋前合法性判断，用于棋子自身生成的符合基本移动规则的走棋，包含：
        出界判断，自占判断，棋子特殊移动规则
    */
    bool check_move_before(const GameContext &context, const ChessPiece *piece, Position target) const;
    /*
        返回值：true 合法，false 不合法
        走棋后合法性判断，包含：
        走棋后不得使将帅照面判断，自毙判断（走棋后不得使走棋方阵营被将军）
    */
    bool check_move_after(const GameContext &context, SideTag side_tag) const;
  public:
    void run_game(GameContext &context) const override;

    std::vector<std::pair<ChessPiece*, Position>>
    generate_all_valid_moves(GameContext &context, SideTag side_tag) const override;

    bool check_game_over(GameContext &context, SideTag side_tag) const override;
};

#endif // CHINESECHESS_ACTION_TRADITIONAL_H
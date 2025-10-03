#ifndef CHINESECHESS_ACTION_TRADITIONAL_H
#define CHINESECHESS_ACTION_TRADITIONAL_H

#include "Action/Action.h"
#include "Common/CoreType.h"
#include "GameContext.h"

class TraditionalAction : public Action {
  protected: // 本为 private，为了将军检测单元测试，改成 protected
    /*
        将军检测
        功能：检测 side_tag 阵营是否被将军
    */
    bool is_checked(const GameContext &context, SideTag side_tag) const;
    /*
        （通用）走棋前走棋的合法性检测
        功能：在走棋前对走棋进行合法性检测，用于判定棋子是否可移动到目标位置，包含出界判断，源位置是否有与走棋方阵营一致的棋子，自占判断，棋子基本移动规则，棋子特殊移动规则
        返回值：true - 合法，false - 不合法
    */
    bool check_move_before(const GameContext &context, SideTag side_tag, Position src, Position target) const;
    /*
        （棋子生成的走棋专用）走棋前走棋的合法性检测
        功能：在走棋前对走棋进行合法性检测，用于判定棋子是否可移动到目标位置，包含出界判断，自占判断，棋子特殊移动规则
        返回值：true - 合法，false - 不合法
    */
    bool check_move_before(const GameContext &context, const ChessPiece *piece, Position target) const;
    /*
        走棋后走棋的合法性检测
        功能：在走棋后对走棋进行合法性检测，用于判定棋子移动与攻击造成的影响是否合法，包含：将帅照面判断（走棋后不得使将帅照面），自毙判断（走棋后不得使走棋方阵营被将军）
        返回值：true - 合法，false - 不合法
    */
    bool check_move_after(const GameContext &context, SideTag side_tag) const;
  public:
    void run_game(GameContext &context) const override;

    std::vector<std::pair<ChessPiece*, Position>>
    generate_all_valid_moves(GameContext &context, SideTag side_tag) const override;

    bool check_game_over(GameContext &context, SideTag side_tag) const override;
};

#endif // CHINESECHESS_ACTION_TRADITIONAL_H
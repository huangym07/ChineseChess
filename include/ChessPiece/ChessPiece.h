#ifndef CHINESECHESS_CHESSPIECE_CHESSPIECE_H
#define CHINESECHESS_CHESSPIECE_CHESSPIECE_H

#include "AttackRange/AttackRange.h"
#include "Common/CoreType.h"
#include <string>

class ChessPiece {
  protected:
    PieceType piece_type_;
    SideTag side_tag_;
    Position pos_;
    std::string display_info_;
    std::unordered_map<AttributeType, int> attributes_;
    const AttackRange *attack_range_;

  protected:
    ChessPiece(PieceType piece_type, SideTag side_tag, Position pos, std::string display_info,
               std::unordered_map<AttributeType, int> attributes,
               const AttackRange *attack_range = nullptr)
        : piece_type_(piece_type), side_tag_(side_tag), pos_(pos),
          display_info_(std::move(display_info)), attributes_(std::move(attributes)),
          attack_range_(attack_range) {}

  public:
    PieceType piece_type() const { return piece_type_; }
    SideTag side_tag() const { return side_tag_; }
    Position pos() const { return pos_; }
    void set_pos(Position pos) { pos_ = pos; }
    const std::string &display_info() const { return display_info_; }

    int get_attribute(AttributeType type) const;
    void set_attribute(AttributeType type, int value);

    /*
        基本移动生成
        功能：生成符合基本移动规则的走棋（即符合移动模式——移动方向与距离）
    */
    virtual std::vector<Position> basic_moves_gen(const ChessBoard &board) const = 0;
    /*
        基本移动规则检测
        功能：检测目标位置是否符合基本移动规则
        返回值：true 合法，false 非法
    */
    virtual bool basic_check_move(Position target) const = 0;
    /*
        特殊移动规则检测
        功能：检测目标位置是否符合特殊移动规则
        返回值：true 合法，false 非法
    */
    virtual bool special_check_move(Position target, const ChessBoard &board) const = 0;

    /*
        获取攻击范围
        参数：pos - 攻击发起位置
        功能：获取在参数 pos 位置发起攻击时的攻击范围
    */
    std::vector<Position> get_atk_range(Position pos, const ChessBoard &board) const {
        return attack_range_ ? attack_range_->get_range(pos, board) : std::vector<Position>{};
    }
    /*
        获取可攻击到目标位置的攻击发起位置列表
        功能：返回所有能够攻击到目标位置的位置列表，即棋子移动到这些位置后，发动攻击，根据其攻击范围可以攻击到目标位置
        参数：target_pos - 目标位置
        返回值：可攻击到目标位置的位置列表
    */
    std::vector<Position> where_can_attack(Position target_pos) const {
        return attack_range_ ? attack_range_->where_can_attack(target_pos) : std::vector<Position>{};
    }

    /*
        计算攻击伤害
        功能：采用 max(0, 攻击方物攻 - 防守方物防，攻击方魔攻 - 防守方魔防) 作为伤害值
        返回值：伤害值
    */
    int calc_damage(const ChessPiece *defender) const;
    /*
        移动并攻击
        功能：棋子移动并攻击的实际执行者，会更新棋子与棋盘的状态
        参数：target_pos - 移动目标位置（亦攻击发起位置）
        返回值：受影响的棋子的快照列表（攻击者棋子在列表最后）
    */
    std::vector<PieceSnapshot> move_attack(ChessBoard &board, Position target_pos);
    /*
        撤销攻击与移动
        功能：撤销棋子攻击与移动的实际执行者
        参数：piece_snaps - 待撤销的棋子攻击与移动中的受影响棋子的快照
    */
    void undo_attack_move(ChessBoard &board, const std::vector<PieceSnapshot> &piece_snaps);
    /*
        能否吃子检测
        参数：target_piece - 目标棋子
        功能：检测当前棋子能否吃掉目标棋子
        约束：目标棋子不应为空指针；当前棋子应存活；目标棋子应存活
        返回值：true - 能吃掉，false - 不能吃掉
    */
    bool can_capture(const ChessBoard &board, const ChessPiece *target_piece) const;

    virtual ~ChessPiece() = default;
};

#endif // CHINESECHESS_CHESSPIECE_CHESSPIECE_H
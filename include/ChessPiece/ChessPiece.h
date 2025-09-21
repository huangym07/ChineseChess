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

    virtual std::vector<Position> basic_moves_gen(const ChessBoard &board) const = 0;
    virtual bool basic_check_move(Position target) const = 0;
    virtual bool special_check_move(Position target, const ChessBoard &board) const = 0;

    std::vector<Position> get_atk_range(Position pos, const ChessBoard &board) const {
        return attack_range_ ? attack_range_->get_range(pos, board) : std::vector<Position>{};
    }
    std::vector<Position> where_can_attack(Position target_pos) const {
        return attack_range_ ? attack_range_->where_can_attack(target_pos) : std::vector<Position>{};
    }

    int calc_damage(const ChessPiece *defender) const;
    std::vector<PieceSnapshot> move_attack(ChessBoard &board, Position target_pos);
    void undo_attack_move(ChessBoard &board, const std::vector<PieceSnapshot> &piece_snaps);
    /*
        参数：board 棋盘，targer_piece 目标棋子
        功能：检测当前棋子能否吃掉目标棋子
        约束：目标棋子不应为空指针；当前棋子应存活；目标棋子应存活
    */
    bool can_capture(const ChessBoard &board, const ChessPiece *target_piece) const;

    virtual ~ChessPiece() = default;
};

#endif // CHINESECHESS_CHESSPIECE_CHESSPIECE_H
#ifndef CHINESECHESS_CHESSPIECE_CHESSPIECE_H
#define CHINESECHESS_CHESSPIECE_CHESSPIECE_H

#include "AttackRange/AttackRange.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include "PieceAttributes.h"
#include <cassert>
#include <memory>
#include <optional>
#include <string>

class ChessPiece {
  protected:
    PieceType piece_type_;
    SideTag side_tag_;
    Position pos_;
    std::string display_info_;
    std::unique_ptr<PieceAttributes> attributes_;
    const AttackRange *attack_range_;

  protected:
    ChessPiece(PieceType piece_type, SideTag side_tag, Position pos, std::string display_info,
               std::unique_ptr<PieceAttributes> attributes = nullptr,
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

    std::optional<int> get_attribute(AttributeType type) const {
        return attributes_ ? attributes_->get_attribute(type) : std::nullopt;
    }
    bool modify_attribute(AttriOpType op, AttributeType type, int value) {
        return attributes_ ? attributes_->modify_attribute(op, type, value) : false;
    }

    void remove_attribute(AttributeType type) {
        if (attributes_)
            attributes_->remove_attribute(type);
    }

    virtual std::vector<Position> basic_moves_gen(const ChessBoard &board) const = 0;
    virtual bool basic_check_move(Position target, const ChessBoard &board) const = 0;
    virtual bool special_check_move(Position target, const ChessBoard &board) const = 0;

    std::vector<Position> get_atk_range(Position pos, const ChessBoard &board) const {
        return attack_range_ ? attack_range_->get_range(pos, board) : std::vector<Position>{};
    }

    std::vector<ChessPiece *> move_attack(ChessBoard &board, Position target);
    void undo_attack_move(ChessBoard &board, Position src, std::vector<Position> captured_pieces);
    bool cap_capture(const ChessBoard &board, ChessPiece *target_piece) const;

    virtual ~ChessPiece() = default;
};

#endif // CHINESECHESS_CHESSPIECE_CHESSPIECE_H
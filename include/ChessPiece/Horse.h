#ifndef CHINESECHESS_CHESSPIECE_HORSE_H
#define CHINESECHESS_CHESSPIECE_HORSE_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"
#include <array>

class Horse : public ChessPiece {
  private:
    constexpr static std::array<Position, 8> basic_move_offsets{{
        {-2, -1}, {-2, +1}, {+2, -1}, {+2, +1},
        {-1, -2}, {+1, -2}, {-1, +2}, {+1, +2}
    }};
  public:
    Horse(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::HORSE, side_tag, pos,
                     SideTag::RED == side_tag ? AnsiColor::colored_text(AnsiColor::RED, "马")
                                              : AnsiColor::colored_text(AnsiColor::BLACK, "马"),
                     PieceAttributes::create_default_instance(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_HORSE_H
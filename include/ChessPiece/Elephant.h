#ifndef CHINESECHESS_CHESSPIECE_ELEPHANT_H
#define CHINESECHESS_CHESSPIECE_ELEPHANT_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"
#include <array>

class Elephant : public ChessPiece {
  private:
    constexpr static std::array<Position, 4> basic_move_offsets {{
        {-2, -2}, {-2, +2},
        {+2, -2}, {+2, +2}
    }};
  public:
    Elephant(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::ELEPHANT, side_tag, pos,
                     SideTag::RED == side_tag ? AnsiColor::colored_text(AnsiColor::RED, "相")
                                              : AnsiColor::colored_text(AnsiColor::BLACK, "象"),
                     PieceAttributes::create_default_instance(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_ELEPHANT_H
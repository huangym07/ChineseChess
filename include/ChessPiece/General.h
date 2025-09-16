#ifndef CHINESECHESS_CHESSPIECE_GENERAL_H
#define CHINESECHESS_CHESSPIECE_GENERAL_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"
#include <array>

class General : public ChessPiece {
  private:
    constexpr static std::array<Position, 4> basic_move_offsets{{
        {-1, 0}, {+1, 0},
        {0, -1}, {0, +1}
    }};
  public:
    General(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::GENERAL, side_tag, pos,
                     SideTag::RED == side_tag ? AnsiColor::colored_text(AnsiColor::RED, "帅")
                                              : AnsiColor::colored_text(AnsiColor::BLACK, "将"),
                     PieceAttributes::create_default_instance(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_GENERAL_H
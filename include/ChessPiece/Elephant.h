#ifndef CHINESECHESS_CHESSPIECE_ELEPHANT_H
#define CHINESECHESS_CHESSPIECE_ELEPHANT_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"

class Elephant : public ChessPiece {
  public:
    Elephant(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::ELEPHANT, side_tag, pos, side_tag == SideTag::RED ? "相" : "象",
                     PieceAttributes::create_default_instance(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target, const ChessBoard &board) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_ELEPHANT_H
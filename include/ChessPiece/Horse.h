#ifndef CHINESECHESS_CHESSPIECE_HORSE_H
#define CHINESECHESS_CHESSPIECE_HORSE_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"

class Horse : public ChessPiece {
  public:
    Horse(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::HORSE, side_tag, pos, "马",
                     PieceAttributes::create_default_instance(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target, const ChessBoard &board) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_HORSE_H
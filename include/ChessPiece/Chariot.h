#ifndef CHINESECHESS_CHESSPIECE_CHARIOT_H
#define CHINESECHESS_CHESSPIECE_CHARIOT_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"

class Chariot : public ChessPiece {
  public:
    Chariot(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::CHARIOT, side_tag, pos,
                     SideTag::RED == side_tag ? AnsiColor::colored_text(AnsiColor::RED, "车")
                                              : AnsiColor::colored_text(AnsiColor::BLACK, "车"),
                     PieceAttributes::create_default_instance(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_CHARIOT_H
#ifndef CHINESECHESS_CHESSPIECE_CANNON_H
#define CHINESECHESS_CHESSPIECE_CANNON_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"
#include "StandardChineseChessConfig.h"

class Cannon : public ChessPiece {
  public:
    Cannon(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::CANNON, side_tag, pos,
                     SideTag::RED == side_tag ? AnsiColor::colored_text(AnsiColor::RED, "炮")
                                              : AnsiColor::colored_text(AnsiColor::BLACK, "炮"),
                     StandardChineseChessConfig::create_default_attributes(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_CANNON_H
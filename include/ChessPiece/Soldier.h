#ifndef CHINESECHESS_CHESSPIECE_SOLDIER_H
#define CHINESECHESS_CHESSPIECE_SOLDIER_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece/ChessPiece.h"
#include "Common/CoreType.h"
#include "PieceAttributes.h"
#include <map>

class Soldier : public ChessPiece {
  public:
    Soldier(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::SOLDIER, side_tag, pos, side_tag == SideTag::RED ? "兵" : "卒",
                     std::make_unique<PieceAttributes>(
                         std::map<AttributeType, int>{{AttributeType::HP, 1},
                                                      {AttributeType::PHYSICAL_ATK, 1},
                                                      {AttributeType::PHYSICAL_DEF, 0},
                                                      {AttributeType::MAGIC_ATK, 0},
                                                      {AttributeType::MAGIC_DEF, 0},
                                                      {AttributeType::SPEED, 1}}),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target, const ChessBoard &board) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_SOLDIER_H
#ifndef CHINESECHESS_CHESSPIECE_SOLDIER_H
#define CHINESECHESS_CHESSPIECE_SOLDIER_H

#include "ChessPiece/ChessPiece.h"
#include "Common/CoreType.h"
#include "AttackRange/SinglePosAtkRange.h"

class Soldier : public ChessPiece {
  public:
    Soldier(SideTag side_tag, Position pos, bool has_attributes)
        : ChessPiece(PieceType::SOLDIER, side_tag, pos, side_tag == SideTag::RED ? "兵" : "卒",
                     &SinglePosAtkRange::get_instance()) {
        // TODO
        // 初始化棋子属性
        // if (has_attributes) {
        //     attributes_ = std::make_unique<ConcreteAttributes>(std::map<AttributeType,
        //     int>{{AttributeType::HP, 1}, });
        // }
    }

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target, const ChessBoard &board) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_SOLDIER_H
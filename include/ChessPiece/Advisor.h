#ifndef CHINESECHESS_CHESSPIECE_ADVISOR_H
#define CHINESECHESS_CHESSPIECE_ADVISOR_H

#include "AttackRange/SinglePosAtkRange.h"
#include "ChessPiece.h"
#include "Common/CoreType.h"
#include "StandardChineseChessConfig.h"
#include <array>

class Advisor : public ChessPiece {
  private:
    constexpr static std::array<Position, 4> basic_move_offsets = {
        {{-1, -1}, {-1, +1}, {+1, -1}, {+1, +1}}};

  public:
    Advisor(SideTag side_tag, Position pos)
        : ChessPiece(PieceType::ADVISOR, side_tag, pos,
                     SideTag::RED == side_tag ? AnsiColor::colored_text(AnsiColor::RED, "仕")
                                              : AnsiColor::colored_text(AnsiColor::BLACK, "士"),
                     StandardChineseChessConfig::create_default_attributes(),
                     &SinglePosAtkRange::get_instance()) {}

    std::vector<Position> basic_moves_gen(const ChessBoard &board) const override;
    bool basic_check_move(Position target) const override;
    bool special_check_move(Position target, const ChessBoard &board) const override;
};

#endif // CHINESECHESS_CHESSPIECE_ADVISOR_H
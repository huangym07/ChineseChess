#ifndef CHINESECHESS_CHESSPIECE_H
#define CHINESECHESS_CHESSPIECE_H

#include "AttackRange.h"
#include "CoreType.h"
#include "PieceAttributes.h"
#include <memory>
#include <string>

class ChessPiece {
  private:
    PieceType piece_type_;
    SideTag side_tag_;
    Position pos_;
    std::string display_info_;
    std::unique_ptr<PieceAttributes> attributes_;
    std::shared_ptr<AttackRange> attack_range_;

  public:
    ChessPiece(const PieceType &type, const SideTag &side_tag, const Position &pos, const std::string &display_info);

    // TODO
};

#endif // CHINESECHESS_CHESSPIECE_H
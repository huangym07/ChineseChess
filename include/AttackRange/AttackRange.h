#ifndef CHINESECHESS_ATTACKRANGE_ATTACKRANGE_H
#define CHINESECHESS_ATTACKRANGE_ATTACKRANGE_H

#include "Common/CoreType.h"
#include "GameContext.h"
#include <vector>

class AttackRange {
  protected:
    virtual ~AttackRange() = default;

  public:
    virtual std::vector<Position> get_range(Position pos, const ChessBoard &board) const = 0;
};

#endif // CHINESECHESS_ATTACKRANGE_ATTACKRANGE_H
#ifndef CHINESECHESS_ATTACKRANGE_H
#define CHINESECHESS_ATTACKRANGE_H

#include "CoreType.h"
#include <vector>

class AttackRange {
  public:
    virtual std::vector<Position> get_range(const Position &pos) const = 0;
    virtual ~AttackRange() = default;
};

#endif // CHINESECHESS_ATTACKRANGE_H
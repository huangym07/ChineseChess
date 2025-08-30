#ifndef CHINESECHESS_TRADITIONALATTACKRANGE_H
#define CHINESECHESS_TRADITIONALATTACKRANGE_H

#include "AttackRange.h"

class TraditionalAttackRange : public AttackRange {
  public:
    // TODO get_range 未实现
    std::vector<Position> get_range(const Position &pos) const override;
    ~TraditionalAttackRange() = default;
};

#endif // CHINESECHESS_TRADITIONALATTACKRANGE_H
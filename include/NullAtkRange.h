#ifndef CHINESECHESS_NULLATKRANGE_H
#define CHINESECHESS_NULLATKRANGE_H

#include "AttackRange.h"
#include "CoreType.h"
#include "GameContext.h"
#include <vector>

class NullAtkRange : public AttackRange {
  private:
    NullAtkRange() = default;

  protected:
    ~NullAtkRange() = default;

  public:
    std::vector<Position> get_range(Position pos, const ChessBoard &board) const override {
        return std::vector<Position>{};
    }

    static const NullAtkRange &get_instance() {
        static NullAtkRange instance;
        return instance;
    }

    NullAtkRange(const NullAtkRange &) = delete;
    NullAtkRange &operator=(const NullAtkRange &) = delete;
    NullAtkRange(NullAtkRange &&) = delete;
    NullAtkRange &operator=(NullAtkRange &&) = delete;
};

#endif // CHINESECHESS_NULLATKRANGE_H
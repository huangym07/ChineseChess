#ifndef CHINESECHESS_SINGLEPOSATKRANGE_H
#define CHINESECHESS_SINGLEPOSATKRANGE_H

#include "AttackRange.h"
#include "CoreType.h"

class SinglePosAtkRange : public AttackRange {
  private:
    SinglePosAtkRange() = default;

  protected:
    ~SinglePosAtkRange() = default;

  public:
    std::vector<Position> get_range(Position pos, const ChessBoard &board) const override {
        return std::vector<Position>{pos};
    }

    static const SinglePosAtkRange &get_instance() {
        static SinglePosAtkRange instance;
        return instance;
    }

    SinglePosAtkRange(const SinglePosAtkRange &) = delete;
    SinglePosAtkRange &operator=(const SinglePosAtkRange &) = delete;
    SinglePosAtkRange(SinglePosAtkRange &&) = delete;
    SinglePosAtkRange &operator=(SinglePosAtkRange &&) = delete;
};

#endif // CHINESECHESS_SINGLEPOSATKRANGE_H
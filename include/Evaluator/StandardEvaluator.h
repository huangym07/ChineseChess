#ifndef CHINESECHESS_EVALUATOR_STANDARDEVALUATOR_H
#define CHINESECHESS_EVALUATOR_STANDARDEVALUATOR_H

#include "Common/CoreType.h"
#include "Evaluator/Evaluator.h"

class ChessPiece;

class StandardEvaluator : public Evaluator {
  private:
    static const std::unordered_map<PieceType, int> fixed_value_;
    static const std::unordered_map<PieceType, std::array<std::array<int, 9>, 10>> pos_value_;
  public:
    int value(const GameContext &context, SideTag side_tag) const override;
};

#endif // CHINESECHESS_EVALUATOR_STANDARDEVALUATOR_H
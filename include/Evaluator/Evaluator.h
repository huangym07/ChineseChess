#ifndef CHINESECHESS_EVALUATOR_EVALUATOR_H
#define CHINESECHESS_EVALUATOR_EVALUATOR_H

#include "Common/CoreType.h"

class GameContext;
class ChessPiece;

class Evaluator {
  public:
    virtual int value(const GameContext &context, SideTag side_tag) const = 0;

    virtual ~Evaluator() = default;
};

#endif // CHINESECHESS_EVALUATOR_EVALUATOR_H
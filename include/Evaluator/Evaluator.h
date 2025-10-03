#ifndef CHINESECHESS_EVALUATOR_EVALUATOR_H
#define CHINESECHESS_EVALUATOR_EVALUATOR_H

#include "Common/CoreType.h"

class GameContext;
class ChessPiece;

class Evaluator {
  public:
    /*
        局面评估
        功能：评估 side_tag 视角的棋局分数
    */
    virtual int value(const GameContext &context, SideTag side_tag) const = 0;

    virtual ~Evaluator() = default;
};

#endif // CHINESECHESS_EVALUATOR_EVALUATOR_H
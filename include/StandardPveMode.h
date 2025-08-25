#ifndef __STANDARDPVEMODE_H__
#define __STANDARDPVEMODE_H__

#include "GameMode.h"

class StandardPveMode : public GameMode {
  public:
    void start(GameContext &context) const override;
    // TODO

    ~StandardPveMode() = default;
};

#endif // __STANDARDPVEMODE_H__
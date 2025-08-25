#ifndef __GAMEMODE_H__
#define __GAMEMODE_H__

#include "GameContext.h"

class GameMode {
  public:
    virtual void start(GameContext &context) const = 0;
    // TODO

    virtual ~GameMode() = default;
};

#endif // __GAMEMODE_H__
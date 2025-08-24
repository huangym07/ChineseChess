#ifndef __GAMEMODEFACTORY_H__
#define __GAMEMODEFACTORY_H__

#include "CoreType.h"
#include "GameMode.h"
#include <cassert>
#include <memory>

class GameModeFactory {
  public:
    static std::unique_ptr<GameMode> create_mode(GameOption op) { 
        assert(false && "TODO"); 
    }
};

#endif // __GAMEMODEFACTORY_H__
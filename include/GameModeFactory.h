#ifndef __GAMEMODEFACTORY_H__
#define __GAMEMODEFACTORY_H__

#include "CoreType.h"
#include "GameMode.h"
#include <cassert>
#include <functional>
#include <map>
#include <memory>

class GameModeFactory {
  private:
    static const std::map<GameOption, std::function<std::unique_ptr<GameMode>()>> creators_;

  public:
    static std::unique_ptr<GameMode> create_mode(GameOption op);
};

#endif // __GAMEMODEFACTORY_H__
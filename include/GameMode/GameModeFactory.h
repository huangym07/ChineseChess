#ifndef CHINESECHESS_GAMEMODE_GAMEMODEFACTORY_H
#define CHINESECHESS_GAMEMODE_GAMEMODEFACTORY_H

#include "Common/CoreType.h"
#include <cassert>
#include <functional>
#include <map>
#include <memory>

class GameMode;

class GameModeFactory {
  private:
    static const std::map<GameOption, std::function<std::unique_ptr<GameMode>()>> creators_;

  public:
    static std::unique_ptr<GameMode> create_mode(GameOption op);
};

#endif // CHINESECHESS_GAMEMODE_GAMEMODEFACTORY_H
#ifndef __GAME_H__
#define __GAME_H__

#include "CoreType.h"
#include "GameContext.h"
#include <string>
#include <utility>
#include <vector>

class Game {
  private:
    static const std::vector<std::pair<GameOption, std::string>> menu_;
    GameContext context_;
    GameOption menu() const;

  public:
    void start();
};

#endif // __GAME_H__
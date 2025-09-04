#ifndef CHINESECHESS_GAME_H
#define CHINESECHESS_GAME_H

#include "Common/CoreType.h"
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

#endif // CHINESECHESS_GAME_H
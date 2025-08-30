#ifndef CHINESECHESS_PLAYER_H
#define CHINESECHESS_PLAYER_H

#include "PlayerInfo.h"

class Player {
  private:
    PlayerInfo player_info_;

  public:
    Player(const PlayerInfo &player_info);

    // TODO

    virtual ~Player() = default;
};

#endif // CHINESECHESS_PLAYER_H
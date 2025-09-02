#ifndef CHINESECHESS_PLAYER_PLAYER_H
#define CHINESECHESS_PLAYER_PLAYER_H

#include "Player/PlayerInfo.h"

class Player {
  protected:
    PlayerInfo player_info_;

  public:
    Player(PlayerInfo player_info);

    // TODO

    virtual ~Player() = default;
};

#endif // CHINESECHESS_PLAYER_PLAYER_H
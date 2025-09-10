#ifndef CHINESECHESS_PLAYER_PLAYER_H
#define CHINESECHESS_PLAYER_PLAYER_H

#include "Common/CoreType.h"

class Player {
  protected:
    PlayerInfo player_info_;

  public:
    Player(PlayerInfo player_info);
    PlayerType player_type() const { return player_info_.player_type; }
    SideTag side_tag() const { return player_info_.side_tag; }

    // TODO

    virtual ~Player() = default;
};

#endif // CHINESECHESS_PLAYER_PLAYER_H
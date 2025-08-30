#ifndef CHINESECHESS_HUMANPLAYER_H
#define CHINESECHESS_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
  public:
    HumanPlayer(const PlayerInfo &player_info);

    // TODO

    ~HumanPlayer() = default;
};

#endif // CHINESECHESS_HUMANPLAYER_H
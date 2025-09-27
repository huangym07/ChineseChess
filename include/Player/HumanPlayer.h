#ifndef CHINESECHESS_PLAYER_HUMANPLAYER_H
#define CHINESECHESS_PLAYER_HUMANPLAYER_H

#include "Player/Player.h"

class HumanPlayer : public Player {
  public:
    HumanPlayer(PlayerInfo player_info);

    Position move_chess(GameContext &context) const override;

    ~HumanPlayer() = default;
};

#endif // CHINESECHESS_PLAYER_HUMANPLAYER_H
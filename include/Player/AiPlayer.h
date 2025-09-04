#ifndef CHINESECHESS_PLAYER_AIPLAYER_H
#define CHINESECHESS_PLAYER_AIPLAYER_H

#include "Player/Player.h"
#include "Player/PlayerInfo.h"

class AiPlayer : public Player {
  private:
    constexpr static int MIN_SEARCH_DEPTH = 1;
    constexpr static int MAX_SEARCH_DEPTH = 9;
    int search_depth_ = 6;

  public:
    AiPlayer(PlayerInfo player_info);

    // TODO

    bool set_depth(int depth);
    int get_depth() const { return search_depth_; }
    static int min_depth() { return MIN_SEARCH_DEPTH; }
    static int max_depth() { return MAX_SEARCH_DEPTH; }

    ~AiPlayer() = default;
};

#endif // CHINESECHESS_PLAYER_AIPLAYER_H
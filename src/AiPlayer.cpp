#include "AiPlayer.h"

AiPlayer::AiPlayer(const PlayerInfo &player_info) : Player(player_info) {}

bool AiPlayer::set_depth(int depth) {
    if (depth < min_depth() || depth > max_depth())
        return false;

    search_depth_ = depth;

    return true;
}
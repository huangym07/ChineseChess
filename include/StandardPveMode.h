#ifndef CHINESECHESS_STANDARDPVEMODE_H
#define CHINESECHESS_STANDARDPVEMODE_H

#include "AiPlayer.h"
#include "GameContext.h"
#include "GameMode.h"

class StandardPveMode : public GameMode {
  public:
    void init(GameContext &context) const override;
    void init_players(GameContext &context) const override;
    void init_pieces(GameContext &context) const override;
    void init_board(GameContext &context) const override;
    void init_action(GameContext &context) const override;

    // TODO
    
    ~StandardPveMode() = default;
  private:
    void set_difficulty(AiPlayer &ai_player) const;
};

#endif // CHINESECHESS_STANDARDPVEMODE_H
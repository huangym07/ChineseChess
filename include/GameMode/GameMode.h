#ifndef CHINESECHESS_GAMEMODE_GAMEMODE_H
#define CHINESECHESS_GAMEMODE_GAMEMODE_H

class GameContext;

class GameMode {
  public:
    virtual void init(GameContext &context) const = 0;
    virtual void init_players(GameContext &context) const = 0;
    virtual void init_pieces(GameContext &context) const = 0;
    virtual void init_board(GameContext &context) const = 0;
    virtual void init_action(GameContext &context) const = 0;

    // TODO

    virtual ~GameMode() = default;
};

#endif // CHINESECHESS_GAMEMODE_GAMEMODE_H
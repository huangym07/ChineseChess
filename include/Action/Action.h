#ifndef CHINESECHESS_ACTION_ACTION_H
#define CHINESECHESS_ACTION_ACTION_H

class GameContext;
class Player;

class Action {
  public:
    virtual void run_game(GameContext &context) const = 0;

    // 检测当前玩家 cur_player 是否失败
    virtual bool check_game_over(GameContext &context, const Player *cur_palyer) const;


    // TODO
};

#endif // CHINESECHESS_ACTION_ACTION_H
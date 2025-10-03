#ifndef CHINESECHESS_GAME_H
#define CHINESECHESS_GAME_H

#include "Common/CoreType.h"
#include "GameContext.h"
#include <string>
#include <utility>
#include <vector>

class Game {
  private:
    static const std::vector<std::pair<GameOption, std::string>> menu_; // 游戏菜单选项
    GameContext context_; // 游戏上下文
    /*
        菜单交互逻辑
        功能：从标准输入流中获取玩家选择的游戏菜单选项
    */
    GameOption menu() const;

  public:
    /*
        游戏主入口
        功能：开始游戏
    */
    void start();
};

#endif // CHINESECHESS_GAME_H
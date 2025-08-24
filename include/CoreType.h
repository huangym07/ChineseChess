#ifndef __CORE_TYPE_H__
#define __CORE_TYPE_H__ 

struct Position {
    int x, y;
};

enum class AttributeType {
    HP, 
    PHYSICAL_ATK, PHYSICAL_DEF, 
    MAGIC_ATK, MAGIC_DEF, 
    SPEED,
};

enum class PieceType {
    GENERAL,        // 帅/将
    ADVISOR,        // 仕
    ELEPHANT,       // 象/相
    HORSE,          // 马
    CHARIOT,        // 车
    CANNON,         // 炮
    SOLDIER,        // 兵/卒
};

enum class GameOption {
    STANDARD_PvE,   // 标准象棋人机对战
    EXIT,           // 退出游戏
};

enum class SideTag {
    BLACK,
    RED,
};

enum class PlayerType {
    Human,
    AI,
};
#endif // __CORE_TYPE_H__
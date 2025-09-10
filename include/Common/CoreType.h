#ifndef CHINESECHESS_COMMON_CORETYPE_H
#define CHINESECHESS_COMMON_CORETYPE_H

#include <string>

namespace AnsiColor {
// ANSI 转义序列颜色
constexpr const char *RESET = "\033[0m";
constexpr const char *RED = "\033[31;47m";   // 白底红字
constexpr const char *BLACK = "\033[30;47m"; // 白底黑字

inline std::string colored_text(const char *color, const char *text) {
    return std::string{color} + text + RESET;
}

}; // namespace AnsiColor

struct Position {
    int x, y;
};

enum class AttributeType {
    HP,
    PHYSICAL_ATK,
    PHYSICAL_DEF,
    MAGIC_ATK,
    MAGIC_DEF,
    SPEED,
};
enum class AttriOpType {
    SET,    // 不管有无属性，强制覆盖，不会失败
    ADD,    // 增加属性，已存在该属性时失败
    CHANGE, // 改变属性，属性 += delta，无该属性时失败
};

enum class PieceType {
    GENERAL,  // 帅/将
    ADVISOR,  // 仕
    ELEPHANT, // 象/相
    HORSE,    // 马
    CHARIOT,  // 车
    CANNON,   // 炮
    SOLDIER,  // 兵/卒
    UNKNOWN,  // 未知
};

enum class GameOption {
    STANDARD_PvE, // 标准象棋人机对战
    EXIT,         // 退出游戏
};

enum class SideTag {
    BLACK,
    RED,
};

enum class PlayerType {
    Human,
    AI,
};

struct PieceConfig {
    PieceType piece_type;
    SideTag side_tag;
    Position pos;
};

struct PlayerInfo {
    PlayerType player_type;
    SideTag side_tag;
};

#endif // CHINESECHESS_COMMON_CORETYPE_H
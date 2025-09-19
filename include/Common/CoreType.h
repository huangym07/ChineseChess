#ifndef CHINESECHESS_COMMON_CORETYPE_H
#define CHINESECHESS_COMMON_CORETYPE_H

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

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

    constexpr int &operator[](int index) {
        assert(index >= 0 && index <= 1 && "访问 Position 的下标应为 0 或 1");
        return *(&x + index);
    }
    constexpr const int &operator[](int index) const {
        assert(index >= 0 && index <= 1 && "访问 Position 的下标应为 0 或 1");
        return *(&x + index);
    }

    constexpr bool operator==(const Position &other) const { return x == other.x && y == other.y; }
    constexpr bool operator!=(const Position &other) const { return !(*this == other); }

    constexpr Position operator+(const Position &other) const { return {x + other.x, y + other.y}; }
    constexpr Position operator/(int divisor) const { return {x / divisor, y / divisor}; }
};
inline std::ostream &operator<<(std::ostream &os, const Position &pos) {
    os << "(" << pos.x << ", " << pos.y << ")";
    return os;
}

enum class AttributeType {
    HP,
    PHYSICAL_ATK,
    PHYSICAL_DEF,
    MAGIC_ATK,
    MAGIC_DEF,
    SPEED,
};

namespace std {
template <> struct hash<AttributeType> {
    size_t operator()(const AttributeType &type) const noexcept {
        return static_cast<size_t>(type);
    }
};
} // namespace std
class ChessPiece;
struct PieceSnapshot {
    ChessPiece *piece;
    Position pos;
    std::unordered_map<AttributeType, int> attributes;

    PieceSnapshot(ChessPiece *piece_, Position pos_,
                  std::unordered_map<AttributeType, int> attributes_)
        : piece(piece_), pos(pos_), attributes(std::move(attributes_)) {}
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
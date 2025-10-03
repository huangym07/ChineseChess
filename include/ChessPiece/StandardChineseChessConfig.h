#ifndef CHINESECHESS_CHESSPIECE_STD_CHS_CONFIG_H
#define CHINESECHESS_CHESSPIECE_STD_CHS_CONFIG_H

#include "Common/CoreType.h"
#include <vector>

class StandardChineseChessConfig {
  private:
    StandardChineseChessConfig() = delete;

  public:
    static constexpr int WIDTH = 9;
    static constexpr int HEIGHT = 10;

    inline static std::unordered_map<AttributeType, int> create_default_attributes() {
        return {{AttributeType::HP, 1},           {AttributeType::PHYSICAL_ATK, 1},
                {AttributeType::PHYSICAL_DEF, 0}, {AttributeType::MAGIC_ATK, 0},
                {AttributeType::MAGIC_DEF, 0},    {AttributeType::SPEED, 1}};
    }

    inline static const std::vector<PieceConfig> &get_piece_configs() {
        // 内部表示采用 红上黑下
        static const std::vector<PieceConfig> default_configs{
            // 红方基础表示
            {PieceType::GENERAL, SideTag::RED, 4, 0},
            {PieceType::CHARIOT, SideTag::RED, 0, 0},
            {PieceType::HORSE, SideTag::RED, 1, 0},
            {PieceType::ELEPHANT, SideTag::RED, 2, 0},
            {PieceType::ADVISOR, SideTag::RED, 3, 0},
            {PieceType::ADVISOR, SideTag::RED, 5, 0},
            {PieceType::ELEPHANT, SideTag::RED, 6, 0},
            {PieceType::HORSE, SideTag::RED, 7, 0},
            {PieceType::CHARIOT, SideTag::RED, 8, 0},
            {PieceType::CANNON, SideTag::RED, 1, 2},
            {PieceType::CANNON, SideTag::RED, 7, 2},
            {PieceType::SOLDIER, SideTag::RED, 0, 3},
            {PieceType::SOLDIER, SideTag::RED, 2, 3},
            {PieceType::SOLDIER, SideTag::RED, 4, 3},
            {PieceType::SOLDIER, SideTag::RED, 6, 3},
            {PieceType::SOLDIER, SideTag::RED, 8, 3},

            // 黑方基础坐标
            {PieceType::GENERAL, SideTag::BLACK, 4, 9},
            {PieceType::CHARIOT, SideTag::BLACK, 0, 9},
            {PieceType::HORSE, SideTag::BLACK, 1, 9},
            {PieceType::ELEPHANT, SideTag::BLACK, 2, 9},
            {PieceType::ADVISOR, SideTag::BLACK, 3, 9},
            {PieceType::ADVISOR, SideTag::BLACK, 5, 9},
            {PieceType::ELEPHANT, SideTag::BLACK, 6, 9},
            {PieceType::HORSE, SideTag::BLACK, 7, 9},
            {PieceType::CHARIOT, SideTag::BLACK, 8, 9},
            {PieceType::CANNON, SideTag::BLACK, 1, 7},
            {PieceType::CANNON, SideTag::BLACK, 7, 7},
            {PieceType::SOLDIER, SideTag::BLACK, 0, 6},
            {PieceType::SOLDIER, SideTag::BLACK, 2, 6},
            {PieceType::SOLDIER, SideTag::BLACK, 4, 6},
            {PieceType::SOLDIER, SideTag::BLACK, 6, 6},
            {PieceType::SOLDIER, SideTag::BLACK, 8, 6},
        };

        return default_configs;
    }
};

#endif // CHINESECHESS_CHESSPIECE_STD_CHS_CONFIG_H
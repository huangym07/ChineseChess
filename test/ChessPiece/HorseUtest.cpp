#include "ChessBoard.h"
#include "ChessPiece/Horse.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(basic_moves_gen) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Horse horse{SideTag::RED, {2, 2}};

    auto moves = horse.basic_moves_gen(board);
    ASSERT_EQ(moves.size(), 8, "马应有 8 个符合基本移动规则的目标坐标");

    std::vector<Position> expected {
        {1, 0}, {0, 1}, {3, 0}, {4, 1},
        {1, 4}, {0, 3}, {3, 4}, {4, 3}
    };

    for (const auto &pos : expected) {
        bool found = false;
        for (const auto &move : moves) {
            if (move == pos) {
                found = true;
                break;
            }
        }
        ASSERT_TRUE(found, "基础移动位置未包含" << pos);
    }
}

TEST_CASE(basic_check_move) {
    Horse horse{SideTag::RED, {2, 2}};

    ASSERT_TRUE(horse.basic_check_move({3, 4}), "(2, 2) -> (3, 4) 符合基本移动规则");
    ASSERT_FALSE(horse.basic_check_move({3, 3}), "(2, 2) -> (3, 3) 不符合基本移动规则");
}

TEST_CASE(special_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Horse horse{SideTag::RED, {2, 2}};

    ASSERT_TRUE(horse.special_check_move({3, 4}, board), "(2, 2) -> (3, 4) 无蹩马腿棋子，符合特殊移动规则");

    Horse obstacle{SideTag::RED, {2, 3}};
    board.set_piece(obstacle.pos(), &obstacle);
    ASSERT_FALSE(horse.special_check_move({3, 4}, board), "(2, 2) -> (3, 4)，(2, 3) 处有蹩马腿棋子，不符合特殊移动规则");
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_check_move); RUN_TEST(special_check_move);)
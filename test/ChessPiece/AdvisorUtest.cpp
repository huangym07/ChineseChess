#include "ChessBoard.h"
#include "ChessPiece/Advisor.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"
#include <Windows.h>

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};

Advisor advisor{SideTag::RED, Position{4, 1}};

TEST_CASE(basic_moves_gen) {
    advisor.set_pos({4, 1});

    auto moves = advisor.basic_moves_gen(board);
    ASSERT_EQ(moves.size(), 4, "仕应生成四个符合基本移动规则的目标位置");

    std::vector<Position> expected = {{3, 0}, {5, 0}, {3, 2}, {5, 2}};
    for (auto pos : expected) {
        bool found = false;
        for (auto move : moves) {
            if (move == pos) {
                found = true;
                break;
            }
        }
        ASSERT_TRUE(found, "基础移动位置未包含" << pos);
    }
}

TEST_CASE(basic_move_check) {
    advisor.set_pos({4, 1});

    ASSERT_TRUE(advisor.basic_check_move({3, 0}), "(4, 1) -> (3, 0) 应符合基本移动规则");
    ASSERT_FALSE(advisor.basic_check_move({4, 0}), "(4, 1) -> (4, 0) 不符合基本移动规则");
}

TEST_CASE(special_move_check) {
    Advisor red_advisor{SideTag::RED, {4, 1}};

    ASSERT_TRUE(red_advisor.special_check_move({5, 2}, board),
                "(5, 2) 在九宫内，应符合特殊移动规则");
    ASSERT_FALSE(red_advisor.special_check_move({4, 3}, board),
                 "(4, 3) 不在九宫内，不符合特殊移动规则");

    Advisor black_advisor{SideTag::BLACK, {4, 8}};

    ASSERT_TRUE(black_advisor.special_check_move({5, 7}, board),
                "(5, 7) 在九宫内，应符合特殊移动规则");
    ASSERT_FALSE(black_advisor.special_check_move({4, 6}, board),
                 "(4, 6) 不在九宫内，不符合特殊移动规则");
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_move_check); RUN_TEST(special_move_check);)
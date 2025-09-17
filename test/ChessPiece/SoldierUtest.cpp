#include "ChessBoard.h"
#include "ChessPiece/Soldier.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(basic_moves_gen) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};

    // RED
    {
        Soldier red_soldier{SideTag::RED, Position{2, 3}};

        auto moves = red_soldier.basic_moves_gen(board);
        ASSERT_EQ(moves.size(), 3, "兵应有 3 个符合基本移动规则的目标坐标");

        std::vector<Position> expected{{1, 3}, {3, 3}, {2, 4}};
        for (const auto &pos : expected) {
            bool found = false;
            for (const auto &move : moves) {
                if (move == pos) {
                    found = true;
                    break;
                }
            }
            ASSERT_TRUE(found, "基本移动位置未包含" << pos);
        }
    }

    // BLACK
    {
        Soldier black_soldier{SideTag::BLACK, Position{2, 6}};

        auto moves = black_soldier.basic_moves_gen(board);
        ASSERT_EQ(moves.size(), 3, "兵应有 3 个符合基本移动规则的目标坐标");

        std::vector<Position> expected{{1, 6}, {3, 6}, {2, 5}};
        for (const auto &pos : expected) {
            bool found = false;
            for (const auto &move : moves) {
                if (move == pos) {
                    found = true;
                    break;
                }
            }
            ASSERT_TRUE(found, "基本移动位置未包含" << pos);
        }
    }
}

TEST_CASE(basic_check_move) {
    // RED
    {
        Soldier red_soldier{SideTag::RED, Position{2, 3}};

        std::vector<Position> expected{{1, 3}, {3, 3}, {2, 4}};
        for (const auto &pos : expected) {
            ASSERT_TRUE(red_soldier.basic_check_move(pos),
                        red_soldier.pos() << " -> " << pos << " 符合基本移动规则");
        }

        ASSERT_FALSE(red_soldier.basic_check_move({2, 2}),
                     "(2, 3) -> (2, 2) 后退不符合基本移动规则");
    }

    // BLACK
    {
        Soldier black_soldier{SideTag::BLACK, Position{2, 6}};

        std::vector<Position> expected{{1, 6}, {3, 6}, {2, 5}};
        for (const auto &pos : expected) {
            ASSERT_TRUE(black_soldier.basic_check_move(pos),
                        black_soldier.pos() << " -> " << pos << " 符合基本移动规则");
        }

        ASSERT_FALSE(black_soldier.basic_check_move({2, 7}),
                     "(2, 6) -> (2, 7) 后退不符合基本移动规则");
    }
}

TEST_CASE(special_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};

    // RED
    {
        Soldier red_soldier{SideTag::RED, Position{2, 3}};

        Position target = red_soldier.pos() + Position{1, 0};
        ASSERT_FALSE(red_soldier.special_check_move(target, board),
                     red_soldier.pos() << " -> " << target << " 未过河不能左右移动");

        red_soldier.set_pos({2, 6});
        target = red_soldier.pos() + Position{1, 0};
        ASSERT_TRUE(red_soldier.special_check_move(target, board),
                    red_soldier.pos() << " -> " << target << " 已过河可以左右移动");
    }

    // BLACK
    {
        Soldier black_soldier{SideTag::BLACK, Position{2, 6}};

        Position target = black_soldier.pos() + Position{1, 0};
        ASSERT_FALSE(black_soldier.special_check_move(target, board),
                     black_soldier.pos() << " -> " << target << " 未过河不能左右移动");

        black_soldier.set_pos({2, 3});
        target = black_soldier.pos() + Position{1, 0};
        ASSERT_TRUE(black_soldier.special_check_move(target, board),
                    black_soldier.pos() << " -> " << target << " 已过河可以左右移动");
    }
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_check_move); RUN_TEST(special_check_move);)
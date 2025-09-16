#include "ChessBoard.h"
#include "ChessPiece/General.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "TestFramework.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(basic_moves_gen) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    General general{SideTag::RED, Position{4, 1}};

    auto moves = general.basic_moves_gen(board);
    ASSERT_EQ(moves.size(), 4, "帅应有四个符合基本移动规则的目标坐标");

    std::vector<Position> expected{{3, 1}, {4, 0}, {5, 1}, {4, 2}

    };
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

TEST_CASE(basic_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    General general{SideTag::RED, Position{3, 1}};

    ASSERT_TRUE(general.basic_check_move({3, 2}), "(3, 1) -> (3, 2) 符合基本移动规则");
    ASSERT_FALSE(general.basic_check_move({4, 2}), "(3, 1) -> (4, 2) 不符合基本移动规则");
}

TEST_CASE(special_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    General general{SideTag::RED, Position{3, 1}};

    ASSERT_TRUE(general.special_check_move({3, 2}, board), "(3, 1) -> (3, 2) 符合特殊移动规则");
    ASSERT_FALSE(general.special_check_move({2, 1}, board), "(3, 1) -> (2, 1) 不符合特殊移动规则");
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_check_move); RUN_TEST(special_check_move);)
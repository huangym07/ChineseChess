#include "ChessBoard.h"
#include "ChessPiece/Elephant.h"
#include "TestFramework.h"
#include "ChessPiece/StandardChineseChessConfig.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(basic_moves_gen) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Elephant elephant{SideTag::RED, Position{4, 2}};

    auto moves = elephant.basic_moves_gen(board);
    ASSERT_EQ(moves.size(), 4, "Elephant 符合基本移动规则的目标坐标应有 4 个");

    std::vector<Position> expected{
        {2, 0}, {2, 4},
        {6, 0}, {6, 4}
    };

    for (auto pos : expected) {
        bool found = false;
        for (auto move : moves) {
            if (move.x == pos.x && move.y == pos.y) {
                found = true;
                break;
            }
        }
        ASSERT_TRUE(found, "基础移动位置未包含" << pos);
    }
}

TEST_CASE(basic_check_move) {
    Elephant elephant{SideTag::RED, Position{6, 4}};

    ASSERT_TRUE(elephant.basic_check_move({8, 6}), "(6, 4) -> (8, 6) 符合基本移动规则");
    ASSERT_FALSE(elephant.basic_check_move({6, 5}), "(6, 4) -> (6, 5) 不符合基本移动规则");
}

TEST_CASE(special_check_move) {
    ChessBoard board{width, height, std::map<SideTag, std::vector<std::unique_ptr<ChessPiece>>>{}};
    Elephant red_elephant{SideTag::RED, Position{6, 4}};
    Elephant black_elephant{SideTag::BLACK, Position{6, 5}};

    // 楚河汉界
    ASSERT_FALSE(red_elephant.special_check_move({8, 6}, board), "(6, 4) -> (8, 6) 跨过楚河汉界，不符合特殊移动规则");
    ASSERT_FALSE(black_elephant.special_check_move({8, 3}, board), "(6, 4) -> (8, 3) 跨过楚河汉界，不符合特殊移动规则");

    // 塞象眼
    ASSERT_TRUE(red_elephant.special_check_move({4, 2}, board), "(6, 4) -> (4, 2)，中间无棋子，符合特殊移动规则");

    Elephant obstacle{SideTag::RED, Position{5, 3}};
    board.set_piece(obstacle.pos(), &obstacle);

    ASSERT_FALSE(red_elephant.special_check_move({4, 2}, board), "(6, 4) -> (4, 2)，中间有棋子，不合符特殊移动规则");
}

TEST_MAIN(RUN_TEST(basic_moves_gen); RUN_TEST(basic_check_move); RUN_TEST(special_check_move);)
#include "Action/TraditionalAction.h"
#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "ChessPiece/PieceFactory.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include "TestFramework.h"
#include <memory>
#include <vector>

void show_moves(const std::vector<std::pair<ChessPiece*, Position>> &moves) {
    for (const auto &[piece, pos] : moves) {
        std::cout << piece->display_info() << ": " << piece->pos() << " -> " << pos << std::endl;
    }
}

void create_and_add_piece_then_add_valid_moves(const PieceConfig &config, std::vector<std::pair<ChessPiece*, Position>> &expected, std::vector<std::unique_ptr<ChessPiece>> &pieces, std::vector<Position> expected_pos) {
    std::unique_ptr<ChessPiece> piece = PieceFactory::create_piece(config);

    for (const auto &pos : expected_pos) {
        expected.emplace_back(piece.get(), pos);
    }

    pieces.push_back(std::move(piece));
}

// 测试标准象棋初始棋局的红方全走法生成
TEST_CASE(init_board_valid_moves_gen) { 
    GameContext context;

    std::vector<std::pair<ChessPiece *, Position>> expected;

    std::vector<std::unique_ptr<ChessPiece>> pieces;
    pieces.reserve(16);

    // (0, 0) 红车
    create_and_add_piece_then_add_valid_moves({PieceType::CHARIOT, SideTag::RED, {0, 0}}, expected, pieces, {{0, 1}, {0, 2}});
    
    // (1, 0) 红马
    create_and_add_piece_then_add_valid_moves({PieceType::HORSE, SideTag::RED, {1, 0}}, expected, pieces, {{0, 2}, {2, 2}});

    // (2, 0) 红相
    create_and_add_piece_then_add_valid_moves({PieceType::ELEPHANT, SideTag::RED, {2, 0}}, expected, pieces, {{0, 2}, {4, 2}});

    // (3, 0) 红仕
    create_and_add_piece_then_add_valid_moves({PieceType::ADVISOR, SideTag::RED, {3, 0}}, expected, pieces, {{4, 1}});

    // (4, 0) 红帅
    create_and_add_piece_then_add_valid_moves({PieceType::GENERAL, SideTag::RED, {4, 0}}, expected, pieces, {{4, 1}});

    // (5, 0) 红仕
    create_and_add_piece_then_add_valid_moves({PieceType::ADVISOR, SideTag::RED, {5, 0}}, expected, pieces, {{4, 1}});

    // (6, 0) 红相
    create_and_add_piece_then_add_valid_moves({PieceType::ELEPHANT, SideTag::RED, {6, 0}}, expected, pieces, {{8, 2}, {4, 2}});

    // (7, 0) 红马
    create_and_add_piece_then_add_valid_moves({PieceType::HORSE, SideTag::RED, {7, 0}}, expected, pieces, {{8, 2}, {6, 2}});

    // (8, 0) 红车
    create_and_add_piece_then_add_valid_moves({PieceType::CHARIOT, SideTag::RED, {8, 0}}, expected, pieces, {{8, 1}, {8, 2}});


    // (0, 3) 红兵
    create_and_add_piece_then_add_valid_moves({PieceType::SOLDIER, SideTag::RED, {0, 3}}, expected, pieces, {{0, 4}});
    // (2, 3) 红兵
    create_and_add_piece_then_add_valid_moves({PieceType::SOLDIER, SideTag::RED, {2, 3}}, expected, pieces, {{2, 4}});
    // (4, 3) 红兵
    create_and_add_piece_then_add_valid_moves({PieceType::SOLDIER, SideTag::RED, {4, 3}}, expected, pieces, {{4, 4}});
    // (6, 3) 红兵
    create_and_add_piece_then_add_valid_moves({PieceType::SOLDIER, SideTag::RED, {6, 3}}, expected, pieces, {{6, 4}});
    // (8, 3) 红兵
    create_and_add_piece_then_add_valid_moves({PieceType::SOLDIER, SideTag::RED, {8, 3}}, expected, pieces, {{8, 4}});


    // (1, 2) 红炮
    create_and_add_piece_then_add_valid_moves({PieceType::CANNON, SideTag::RED, {1, 2}}, expected, pieces, {{0, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {1, 1}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 9}});
    // (7, 2) 红炮
    create_and_add_piece_then_add_valid_moves({PieceType::CANNON, SideTag::RED, {7, 2}}, expected, pieces, {{2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {8, 2}, {7, 1}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 9}});



    // 添加红方棋子
    context.pieces[SideTag::RED] = std::move(pieces);
    // 添加黑方棋子
    context.pieces[SideTag::BLACK].reserve(16);
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::CHARIOT, SideTag::BLACK, {0, 9}})); // (0, 9) 黑车
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::CHARIOT, SideTag::BLACK, {8, 9}})); // (8, 9) 黑车
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::HORSE, SideTag::BLACK, {1, 9}})); // (1, 9) 黑马
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::HORSE, SideTag::BLACK, {7, 9}})); // (7, 9) 黑马
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::ELEPHANT, SideTag::BLACK, {2, 9}})); // (2, 9) 黑象
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::ELEPHANT, SideTag::BLACK, {6, 9}})); // (6, 9) 黑象
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::ADVISOR, SideTag::BLACK, {3, 9}})); // (3, 9) 黑士
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::ADVISOR, SideTag::BLACK, {5, 9}})); // (5, 9) 黑士
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::GENERAL, SideTag::BLACK, {4, 9}})); // (4, 9) 黑将

    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::SOLDIER, SideTag::BLACK, {0, 6}})); // (0, 6) 黑兵
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::SOLDIER, SideTag::BLACK, {2, 6}})); // (2, 6) 黑兵
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::SOLDIER, SideTag::BLACK, {4, 6}})); // (4, 6) 黑兵
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::SOLDIER, SideTag::BLACK, {6, 6}})); // (6, 6) 黑兵
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::SOLDIER, SideTag::BLACK, {8, 6}})); // (8, 6) 黑兵

    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::CANNON, SideTag::BLACK, {1, 7}})); // (1, 7) 黑炮
    context.pieces[SideTag::BLACK].push_back(PieceFactory::create_piece({PieceType::CANNON, SideTag::BLACK, {7, 7}})); // (7, 7) 黑炮

    // 初始化棋盘
    context.board = std::make_unique<ChessBoard>(9, 10, context.pieces);

    // 初始化标准象棋流程
    TraditionalAction traditional_action;
    // 全走法生成
    auto valid_moves = traditional_action.generate_all_valid_moves(context, SideTag::RED);

    std::vector<int> mark_expected(expected.size(), 0), mark_valid_moves(valid_moves.size(), 0);
    for (int i = 0; i < expected.size(); ++i) {
        int found = 0;
        const auto &[expected_piece, expected_pos] = expected[i];
        for (int j = 0; j < valid_moves.size(); ++j) {
            const auto &[piece, pos] = valid_moves[j];
            if (expected_piece == piece && expected_pos == pos) {
                found = 1;
                mark_valid_moves[j] = 1;
                break;
            }
        }
        mark_expected[i] = found;
    }

    std::cout << "期望走法中未被生成的有：\n";
    for (int i = 0; i < expected.size(); ++i) {
        if (!mark_expected[i]) {
            const auto &[piece, pos] = expected[i];
            std::cout << piece->display_info() << ": " << piece->pos() << " -> " << pos << std::endl;
        }
    }
    std::cout << "生成走法中未被期望的有：\n";
    for (int i = 0; i < valid_moves.size(); ++i) {
        if (!mark_valid_moves[i]) {
            const auto &[piece, pos] = valid_moves[i];
            std::cout << piece->display_info() << ": " << piece->pos() << " -> " << pos << std::endl;
        }
    }

    ASSERT_EQ(expected.size(), valid_moves.size(), "期望全部合法走法与生成全部合法走法数量不同，分别为 " << expected.size() << " 和 " << valid_moves.size());
}

TEST_MAIN(RUN_TEST(init_board_valid_moves_gen);)
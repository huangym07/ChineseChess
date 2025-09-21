#include "ChessBoard.h"
#include "ChessPiece/Advisor.h"
#include "ChessPiece/Chariot.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "TestFramework.h"

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

ChessBoard board{width, height, {}};

std::vector<PieceSnapshot> piece_snaps_eat, piece_snaps_not_eat;

// 吃子
Chariot red_chariot{SideTag::RED, {3, 1}};
Advisor black_advisor{SideTag::BLACK, {3, 9}};

// 不吃子
Chariot black_chariot{SideTag::BLACK, {5, 8}};
Advisor red_advisor{SideTag::RED, {5, 0}};

std::map<AttributeType, int> black_chariot_attrs{{AttributeType::PHYSICAL_ATK, 11},
                                                 {AttributeType::PHYSICAL_DEF, 0},
                                                 {AttributeType::MAGIC_ATK, 0},
                                                 {AttributeType::MAGIC_DEF, 0},
                                                 {AttributeType::HP, 1}};
std::map<AttributeType, int> red_advisor_attrs{{AttributeType::PHYSICAL_ATK, 1},
                                               {AttributeType::PHYSICAL_DEF, 2},
                                               {AttributeType::MAGIC_ATK, 0},
                                               {AttributeType::MAGIC_DEF, 0},
                                               {AttributeType::HP, 10}};

int res_hp = red_advisor_attrs[AttributeType::HP] -
             std::max(0, std::max(black_chariot_attrs[AttributeType::PHYSICAL_ATK] -
                                      red_advisor_attrs[AttributeType::PHYSICAL_DEF],
                                  black_chariot_attrs[AttributeType::MAGIC_ATK] -
                                      red_advisor_attrs[AttributeType::MAGIC_DEF]));

Position src_pos_eat, target_pos_eat;
Position src_pos_not_eat, target_pos_not_eat;

void init_env() {
    board.set_piece(red_chariot.pos(), &red_chariot);
    board.set_piece(black_advisor.pos(), &black_advisor);
    src_pos_eat = red_chariot.pos();
    target_pos_eat = black_advisor.pos();

    for (const auto &[type, value] : black_chariot_attrs) {
        black_chariot.set_attribute(type, value);
    }
    for (const auto &[type, value] : red_advisor_attrs) {
        red_advisor.set_attribute(type, value);
    }
    board.set_piece(black_chariot.pos(), &black_chariot);
    board.set_piece(red_advisor.pos(), &red_advisor);
    src_pos_not_eat = black_chariot.pos();
    target_pos_not_eat = red_advisor.pos();
}

TEST_CASE(move_attack) {
    { // 吃子
        src_pos_eat = red_chariot.pos();
        target_pos_eat = black_advisor.pos();
        piece_snaps_eat = red_chariot.move_attack(board, target_pos_eat);

        ASSERT_EQ(black_advisor.get_attribute(AttributeType::HP), 0, "生命值应为 0");

        ASSERT_EQ(red_chariot.pos(), target_pos_eat,
                  "吃掉目标位置棋子后，攻击者棋子的最终位置应为目标位置");
        ASSERT_TRUE(nullptr == board.get_piece(src_pos_eat),
                    "吃掉目标棋子后，棋盘上攻击者棋子源位置应为空");
        ASSERT_TRUE(&red_chariot == board.get_piece(target_pos_eat),
                    "吃掉目标位置棋子后，棋盘上目标位置应为攻击者棋子");
    }
    { // 未吃子
        src_pos_not_eat = black_chariot.pos();
        target_pos_not_eat = red_advisor.pos();
        piece_snaps_not_eat = black_chariot.move_attack(board, target_pos_not_eat);

        ASSERT_EQ(red_advisor.get_attribute(AttributeType::HP), res_hp, "生命值应为 " << res_hp);

        ASSERT_EQ(black_chariot.pos(), src_pos_not_eat,
                  "未吃掉目标位置棋子，攻击者棋子的最终位置不改变");
        ASSERT_TRUE(&black_chariot == board.get_piece(src_pos_not_eat),
                    "未吃掉目标位置棋子，棋盘上攻击者棋子源位置上应为攻击者棋子本身");
        ASSERT_TRUE(&red_advisor == board.get_piece(target_pos_not_eat),
                    "未吃掉目标位置棋子，棋盘上目标位置上的棋子不变");
    }
}

TEST_CASE(undo_attack_move) {
    { // 未吃子
        black_chariot.undo_attack_move(board, piece_snaps_not_eat);

        ASSERT_EQ(red_advisor.get_attribute(AttributeType::HP),
                  red_advisor_attrs[AttributeType::HP], "撤销移动攻击后，棋子生命值未还原");

        ASSERT_EQ(black_chariot.pos(), src_pos_not_eat, "撤销移动攻击后，攻击者棋子的位置不正确");
        ASSERT_EQ(red_advisor.pos(), target_pos_not_eat,
                  "撤销移动攻击后，目标位置棋子的位置不正确");

        ASSERT_TRUE(&black_chariot == board.get_piece(src_pos_not_eat),
                    "撤销移动攻击后，棋盘上攻击者棋子源位置上应为攻击者棋子");
        ASSERT_TRUE(&red_advisor == board.get_piece(target_pos_not_eat),
                    "撤销移动攻击后，棋盘上目标位置上应为目标位置棋子");
    }
    { // 吃子
        red_chariot.undo_attack_move(board, piece_snaps_eat);

        ASSERT_EQ(black_advisor.get_attribute(AttributeType::HP), 1,
                  "撤销移动攻击后，棋子生命值未还原");

        ASSERT_EQ(red_chariot.pos(), src_pos_eat, "撤销移动攻击后，攻击者棋子的位置不正确");
        ASSERT_EQ(black_advisor.pos(), target_pos_eat, "撤销移动攻击后，目标位置棋子的位置不正确");

        ASSERT_TRUE(&red_chariot == board.get_piece(src_pos_eat),
                    "撤销移动攻击后，棋盘上攻击者棋子源位置上应为攻击者棋子");
        ASSERT_TRUE(&black_advisor == board.get_piece(target_pos_eat),
                    "撤销移动攻击后，棋盘上目标位置上应为目标位置棋子");
    }
}

TEST_MAIN(init_env(); RUN_TEST(move_attack); RUN_TEST(undo_attack_move);)
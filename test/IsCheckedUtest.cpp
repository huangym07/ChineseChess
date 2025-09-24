#include "Action/TraditionalAction.h"
#include "ChessBoard.h"
#include "ChessPiece/General.h"
#include "ChessPiece/Soldier.h"
#include "ChessPiece/Cannon.h"
#include "ChessPiece/StandardChineseChessConfig.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include "TestFramework.h"
#include <memory>

class IsCheckedUtest : public TraditionalAction {
  public:
    bool is_checked_utest(const GameContext &context, SideTag side_tag) const;
};
bool IsCheckedUtest::is_checked_utest(const GameContext &context, SideTag side_tag) const {
    return is_checked(context, side_tag);
}

int width = StandardChineseChessConfig::WIDTH;
int height = StandardChineseChessConfig::HEIGHT;

TEST_CASE(is_checked) {
    GameContext context;

    context.pieces[SideTag::RED].push_back(std::make_unique<Soldier>(SideTag::RED, Position{4, 3}));
    context.pieces[SideTag::BLACK].push_back(std::make_unique<General>(SideTag::BLACK, Position{4, 9}));

    context.board = std::make_unique<ChessBoard>(width, height, context.pieces);

    IsCheckedUtest utest;
    ASSERT_FALSE(utest.is_checked_utest(context, SideTag::BLACK), "黑方阵营未被将军");

    std::unique_ptr<Cannon> cannon = std::make_unique<Cannon>(SideTag::RED, Position{4, 2});
    context.board->set_piece({4, 2}, cannon.get());
    context.pieces[SideTag::RED].push_back(std::move(cannon));

    ASSERT_TRUE(utest.is_checked_utest(context, SideTag::BLACK), "黑方阵营应被将军");
}

TEST_MAIN(RUN_TEST(is_checked);)
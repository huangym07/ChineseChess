#include "Action/TraditionalAction.h"
#include "ChessBoard.h"
#include "ChessPiece/ChessPiece.h"
#include "Command/SingleCommand.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include <cassert>
#include <memory>

bool TraditionalAction::is_checked(const GameContext &context, SideTag side_tag) const {
    const auto &pieces = context.get_pieces(side_tag);
    const auto &enemy_pieces =
        context.get_pieces(SideTag::RED == side_tag ? SideTag::BLACK : SideTag::RED);

    const ChessPiece *general_piece = nullptr;
    for (const auto &piece : pieces) {
        if (PieceType::GENERAL == piece->piece_type()) {
            general_piece = piece.get();
            break;
        }
    }

    assert(nullptr != general_piece && "GameContext 中不应没有将/帅棋子");

    for (const auto &enemy_piece : enemy_pieces) {
        if (enemy_piece->get_attribute(AttributeType::HP) > 0 &&
            enemy_piece->can_capture(*context.board, general_piece))
            return true;
    }

    return false;
}

bool TraditionalAction::check_move_before(const GameContext &context, SideTag side_tag,
                                          Position src, Position target) const {
    const auto &board = *context.board;

    // 出界判断
    if (board.is_out_of_board(src) || board.is_out_of_board(target))
        return false;

    // 源坐标应有与走棋方阵营一致的棋子
    const ChessPiece *attacker = board.get_piece(src);
    if (nullptr == attacker || attacker->side_tag() != side_tag)
        return false;

    // 自占判断：目标位置不应有与走棋方阵营一致的棋子
    const ChessPiece *defender = board.get_piece(target);
    if (nullptr != defender && defender->side_tag() == side_tag)
        return false;

    // 棋子基本移动规则与特殊移动规则
    if (!attacker->basic_check_move(target) || !attacker->special_check_move(target, board))
        return false;

    return true;
}
bool TraditionalAction::check_move_before(const GameContext &context, const ChessPiece *piece,
                                          Position target) const {
    const auto &board = *context.board;

    // 出界判断
    if (board.is_out_of_board(target))
        return false;

    // 自占判断：目标位置不应有与走棋方阵营一致的棋子
    const ChessPiece *defender = board.get_piece(target);
    if (nullptr != defender && defender->side_tag() == piece->side_tag())
        return false;

    // 棋子特殊移动规则
    if (!piece->special_check_move(target, board))
        return false;

    return true;
}
bool TraditionalAction::check_move_after(const GameContext &context, SideTag side_tag) const {
    const auto &board = *context.board;

    // 获取双方将/帅
    std::vector<const ChessPiece *> generals;
    for (const auto &pieces : context.pieces) {
        for (const auto &piece : pieces.second) {
            if (piece->piece_type() == PieceType::GENERAL) {
                generals.push_back(piece.get());
                break;
            }
        }
    }

    assert(generals.size() == 2 && "阵营只有两个，所以只应有两个将/帅");

    // 将帅不应照面
    if (generals[0]->pos().y == generals[1]->pos().y && 0 == board.count_straight_obstacles_between(generals[0]->pos(), generals[1]->pos())) {
        return false;
    }

    // 自毙判断：走棋后不得使走棋方阵营被将军
    if (is_checked(context, side_tag))
        return false;

    return true;
}

std::vector<std::pair<ChessPiece *, Position>>
TraditionalAction::generate_all_valid_moves(GameContext &context, SideTag side_tag) const {
    std::vector<std::pair<ChessPiece *, Position>> ret;

    auto &board = *context.board;

    const auto &pieces = context.get_pieces(side_tag);
    for (const auto &upiece : pieces) {
        if (0 >= upiece->get_attribute(AttributeType::HP)) continue;

        ChessPiece *piece = upiece.get();
        auto moves = piece->basic_moves_gen(board);

        for (auto move : moves) {
            if (!check_move_before(context, piece, move))
                continue;

            context.cmd_manager.execute(std::make_unique<SingleCommand>(piece, move, context));

            if (check_move_after(context, side_tag))
                ret.emplace_back(piece, move);

            context.cmd_manager.undo(1);
        }
    }

    return ret;
}

void TraditionalAction::run_game(GameContext &context) const {
    int mod = context.players.size();

    assert(2 == mod && "标准象棋玩家应为 2 名");

    int index = 0;
    while (true) {
        context.board->show_board();

        const auto &player = context.players[index];
        if (check_game_over(context, player->side_tag())) {
            std::cout << "游戏结束，" << (PlayerType::Human == player->player_type() ? "AI 玩家" : "人类玩家") << "获胜" << std::endl;
            return;
        }

        bool undo = player->ask_undo_request();
        if (undo) {
            if (context.cmd_manager.undo(2)) {
                std::cout << "悔棋成功" << std::endl;
                continue;
            } else {
                std::cout << "悔棋失败" << std::endl;
            }
        }

        while (true) {
            auto [src_pos, target_pos] = player->move_chess(context);
            if (!check_move_before(context, player->side_tag(), src_pos, target_pos)) {
                std::cout << "走棋不合法" << std::endl;
#ifndef NDEBUG
                std::cerr << "走棋前合法性检测失败" << std::endl;
#endif
                continue;
            }

            context.cmd_manager.execute(std::make_unique<SingleCommand>(context.board->get_piece(src_pos), target_pos, context));

            if (!check_move_after(context, player->side_tag())) {
                context.cmd_manager.undo(1);
                std::cout << "走棋不合法" << std::endl;
#ifndef NDEBUG
                std::cerr << "走棋后合法性检测失败" << std::endl;
#endif
                continue;
            }

            std::cout << "走棋成功: " << context.board->get_piece(target_pos)->display_info() << " " << src_pos << " -> " << target_pos << std::endl;
            break;
        }

        index = (index + 1) % mod;
    }
}

bool TraditionalAction::check_game_over(GameContext &context, SideTag side_tag) const {
    return 0 == generate_all_valid_moves(context, side_tag).size();
}
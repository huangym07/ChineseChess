#include "Player/AiPlayer.h"
#include "ChessPiece/ChessPiece.h"
#include "Command/SingleCommand.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include <limits>
#include <memory>
#include <utility>

AiPlayer::AiPlayer(PlayerInfo player_info) : Player(player_info) {}

bool AiPlayer::set_depth(int depth) {
    if (depth < min_depth() || depth > max_depth())
        return false;

    search_depth_ = depth;

    return true;
}

std::pair<Position, Position> AiPlayer::move_chess(GameContext &context) const {
    std::pair<Position, Position> ret;

    alpha_beta(std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), ret, context,
               side_tag(), get_depth(), side_tag());

    return ret;
}
int AiPlayer::alpha_beta(int alpha, int beta, std::pair<Position, Position> &move,
                         GameContext &context, SideTag side_tag, int depth,
                         SideTag current_side_tag) const {
    if (0 >= depth)
        return context.evaluator->value(context, side_tag);

    auto moves = context.action->generate_all_valid_moves(context, current_side_tag);
    if (0 == moves.size())
        return context.evaluator->value(context, side_tag);

    if (current_side_tag == side_tag) {
        for (auto &[piece, target_pos] : moves) {
            context.cmd_manager.execute(
                std::make_unique<SingleCommand>(piece, target_pos, context));

            int new_alpha = alpha_beta(alpha, beta, move, context, side_tag, depth - 1,
                                       flip_side(current_side_tag));

            context.cmd_manager.undo(1);

            if (new_alpha >= beta)
                return new_alpha;

            if (new_alpha > alpha) {
                alpha = new_alpha;

                if (get_depth() == depth) {
                    move.first = piece->pos();
                    move.second = target_pos;
                }
            }
        }
        return alpha;
    } else {
        for (auto &[piece, target_pos] : moves) {
            context.cmd_manager.execute(
                std::make_unique<SingleCommand>(piece, target_pos, context));

            beta = std::min(beta, alpha_beta(alpha, beta, move, context, side_tag, depth - 1,
                                             flip_side(current_side_tag)));

            context.cmd_manager.undo(1);

            if (beta <= alpha)
                break;
        }
        return beta;
    }
}
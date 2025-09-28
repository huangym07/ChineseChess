#include "Evaluator/StandardEvaluator.h"
#include "Common/CoreType.h"
#include "GameContext.h"
#include <array>
#include <unordered_map>
#include <winsock.h>

const std::unordered_map<PieceType, int> StandardEvaluator::fixed_value_{
    {PieceType::GENERAL, 1000}, {PieceType::ADVISOR, 20}, {PieceType::ELEPHANT, 20},
    {PieceType::HORSE, 40},     {PieceType::CHARIOT, 90}, {PieceType::CANNON, 45},
    {PieceType::SOLDIER, 10}};

const std::unordered_map<PieceType, std::array<std::array<int, 9>, 10>>
    StandardEvaluator::pos_value_{{PieceType::GENERAL,
                                   {{{{0, 0, 0, 15, 20, 15, 0, 0, 0}},
                                     {{0, 0, 0, 10, 10, 10, 0, 0, 0}},
                                     {{0, 0, 0, 1, 1, 1, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}}}}},
                                  {PieceType::ADVISOR,
                                   {{{{0, 0, 0, 30, 0, 30, 0, 0, 0}},
                                     {{0, 0, 0, 0, 22, 0, 0, 0, 0}},
                                     {{0, 0, 0, 30, 0, 30, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}}}}},
                                  {PieceType::ELEPHANT,
                                   {{{{0, 0, 30, 0, 0, 0, 30, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{20, 0, 0, 0, 35, 0, 0, 0, 20}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 25, 0, 0, 0, 25, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}}}}},
                                  {PieceType::HORSE,
                                   {{{{60, 70, 75, 70, 60, 70, 75, 70, 60}},
                                     {{70, 75, 75, 70, 50, 70, 75, 75, 70}},
                                     {{80, 80, 90, 90, 80, 90, 90, 80, 80}},
                                     {{80, 90, 100, 100, 90, 100, 100, 90, 80}},
                                     {{90, 100, 100, 110, 100, 110, 100, 100, 90}},
                                     {{90, 110, 110, 120, 100, 120, 110, 110, 90}},
                                     {{90, 100, 120, 130, 110, 130, 120, 100, 90}},
                                     {{90, 100, 120, 125, 120, 125, 120, 100, 90}},
                                     {{80, 110, 125, 90, 70, 90, 125, 110, 80}},
                                     {{70, 80, 90, 80, 70, 80, 90, 80, 70}}}}},
                                  {PieceType::CHARIOT,
                                   {{{{150, 160, 150, 160, 150, 160, 150, 160, 150}},
                                     {{160, 170, 160, 160, 150, 160, 160, 170, 160}},
                                     {{170, 180, 170, 170, 160, 170, 170, 180, 170}},
                                     {{170, 190, 200, 220, 240, 220, 180, 190, 170}},
                                     {{180, 220, 210, 240, 250, 240, 210, 220, 180}},
                                     {{180, 220, 210, 240, 250, 240, 210, 220, 180}},
                                     {{180, 220, 210, 240, 250, 240, 210, 220, 180}},
                                     {{170, 190, 200, 220, 240, 220, 200, 190, 170}},
                                     {{170, 180, 170, 190, 250, 190, 170, 180, 170}},
                                     {{160, 170, 160, 150, 150, 150, 160, 170, 160}}}}},
                                  {PieceType::CANNON,
                                   {{{{80, 90, 80, 70, 60, 70, 80, 90, 80}},
                                     {{80, 90, 80, 70, 65, 70, 80, 90, 80}},
                                     {{90, 100, 80, 80, 70, 80, 80, 100, 90}},
                                     {{90, 100, 90, 90, 110, 90, 90, 100, 90}},
                                     {{90, 100, 90, 110, 130, 110, 90, 100, 90}},
                                     {{90, 110, 90, 110, 130, 110, 90, 110, 90}},
                                     {{90, 110, 90, 110, 130, 110, 90, 110, 90}},
                                     {{100, 120, 90, 80, 80, 80, 90, 120, 100}},
                                     {{110, 125, 100, 70, 60, 70, 100, 125, 110}},
                                     {{125, 130, 100, 70, 60, 70, 100, 130, 125}}}}},
                                  {PieceType::SOLDIER,
                                   {{{{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{0, 0, 0, 0, 0, 0, 0, 0, 0}},
                                     {{10, 0, 10, 0, 15, 0, 10, 0, 10}},
                                     {{10, 0, 15, 0, 15, 0, 15, 0, 10}},
                                     {{15, 20, 20, 20, 20, 20, 20, 20, 15}},
                                     {{20, 25, 25, 30, 30, 30, 25, 25, 20}},
                                     {{25, 30, 30, 40, 40, 40, 30, 30, 25}},
                                     {{25, 30, 40, 50, 60, 50, 40, 30, 25}},
                                     {{10, 10, 10, 20, 25, 20, 10, 10, 10}}}}}};

int StandardEvaluator::value(const GameContext &context, SideTag side_tag) const {
    int ret = 0;

    const auto &pieces = context.get_pieces(side_tag);
    for (const auto &upiece : pieces) {
        if (0 >= upiece->get_attribute(AttributeType::HP)) continue;

        auto piece_type = upiece->piece_type();
        auto [x, y] = upiece->pos();
        ret += fixed_value_.find(piece_type)->second;
        y = SideTag::RED == side_tag ? y : 9 - y;
        ret += pos_value_.find(piece_type)->second[y][x];
    }

    const auto &enemy_pieces = context.get_pieces(SideTag::RED == side_tag ? SideTag::BLACK : SideTag::RED);
    for (const auto &upiece : enemy_pieces) {
        if (0 >= upiece->get_attribute(AttributeType::HP)) continue;

        auto piece_type = upiece->piece_type();
        auto [x, y] = upiece->pos();
        ret -= fixed_value_.find(piece_type)->second;
        y = SideTag::RED == side_tag ? y : 9 - y;
        ret -= pos_value_.find(piece_type)->second[y][x];
    }

    return ret;
}
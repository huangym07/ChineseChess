#include "ChessPiece/ChessPiece.h"
#include "ChessBoard.h"
#include "Common/CoreType.h"
#include <unordered_map>

int ChessPiece::get_attribute(AttributeType type) const {
    auto it = attributes_.find(type);
    assert(attributes_.end() != it && "查询棋子属性值时，找不到对应属性");
    return it->second;
}
void ChessPiece::set_attribute(AttributeType type, int value) {
    assert(attributes_.end() != attributes_.find(type) && "强制覆盖棋子属性值时，找不到对应属性");
    attributes_[type] = value;
}

int ChessPiece::calc_damage(const ChessPiece *defender) const {
    assert(nullptr != defender && "defender 不应为 nullptr");
    int phy_damage = get_attribute(AttributeType::PHYSICAL_ATK) -
                     defender->get_attribute(AttributeType::PHYSICAL_DEF);
    int mgc_damage = get_attribute(AttributeType::MAGIC_ATK) -
                     defender->get_attribute(AttributeType::MAGIC_DEF);
    return std::max(0, std::max(phy_damage, mgc_damage));
}

std::vector<PieceSnapshot> ChessPiece::move_attack(ChessBoard &board, Position target_pos) {
    std::vector<PieceSnapshot> piece_snaps;

    // 离开源位置，移动并攻击
    board.set_piece(pos_, nullptr);

    auto atk_range = get_atk_range(target_pos, board);
    for (const auto &atked_pos : atk_range) {
        ChessPiece *atked_piece = board.get_piece(atked_pos);
        if (nullptr != atked_piece && atked_piece->side_tag() != side_tag_) {
            // 确认该棋子会被攻击，
            // 在攻击效果实现之前，
            // 保存将要变化的状态
            auto hp = atked_piece->get_attribute(AttributeType::HP);

            assert(0 < hp && "棋盘上存在的棋子生命值应 > 0");

            piece_snaps.emplace_back(atked_piece, atked_pos, std::unordered_map<AttributeType, int>{{AttributeType::HP, hp}});

            // 实现攻击效果
            int damage = calc_damage(atked_piece);
            int new_hp = hp - damage;
            atked_piece->set_attribute(AttributeType::HP, new_hp);

            if (0 >= new_hp) {
                // 被攻击者棋子死亡，从棋盘上移除，其位置逻辑上应设置为无效状态或场外位置，但没必要
                // atked_piece->set_pos({-1, -1});

                board.set_piece(atked_pos, nullptr);
            }
        }
    }

    // 最后添加攻击者棋子的快照
    // 目前攻击者在攻击逻辑中属性不会变化，所以为空
    piece_snaps.emplace_back(this, pos_, std::unordered_map<AttributeType, int>{});

    // 确定棋子最终位置
    if (nullptr == board.get_piece(target_pos)) {
        // 目标位置为空，可以移动到目标位置
        set_pos(target_pos);
        board.set_piece(target_pos, this);
    } else {
        // 目标位置不为空，回到源位置
        board.set_piece(pos_, this);
    }

    return piece_snaps;
}


void ChessPiece::undo_attack_move(ChessBoard &board, const std::vector<PieceSnapshot> &piece_snaps) {
    // 离开当前位置，恢复攻击与移动
    board.set_piece(pos_, nullptr);

    for (const auto &piece_snap : piece_snaps) {
        ChessPiece *piece = piece_snap.piece;
        Position pos = piece_snap.pos;

        // 恢复位置
        piece->set_pos(pos);
        board.set_piece(pos, piece);

        // 强制覆盖为原本属性值
        for (const auto &[attr_type, value] : piece_snap.attributes) {
            piece->set_attribute(attr_type, value);
        }
    }
}
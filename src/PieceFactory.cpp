#include "ChessPiece/PieceFactory.h"
#include "ChessPiece/Advisor.h"
#include "ChessPiece/Cannon.h"
#include "ChessPiece/Chariot.h"
#include "ChessPiece/Elephant.h"
#include "ChessPiece/General.h"
#include "ChessPiece/Horse.h"
#include "ChessPiece/Soldier.h"
#include "Common/CoreType.h"

const std::map<PieceType, PieceFactory::CreatorFunc> PieceFactory::creators_{
    {PieceType::ADVISOR,
     [](SideTag side_tag, Position pos) { return std::make_unique<Advisor>(side_tag, pos); }},
    {PieceType::CANNON,
     [](SideTag side_tag, Position pos) { return std::make_unique<Cannon>(side_tag, pos); }},
    {PieceType::CHARIOT,
     [](SideTag side_tag, Position pos) { return std::make_unique<Chariot>(side_tag, pos); }},
    {PieceType::ELEPHANT,
     [](SideTag side_tag, Position pos) { return std::make_unique<Elephant>(side_tag, pos); }},
    {PieceType::GENERAL,
     [](SideTag side_tag, Position pos) { return std::make_unique<General>(side_tag, pos); }},
    {PieceType::HORSE,
     [](SideTag side_tag, Position pos) { return std::make_unique<Horse>(side_tag, pos); }},
    {PieceType::SOLDIER,
     [](SideTag side_tag, Position pos) { return std::make_unique<Soldier>(side_tag, pos); }},
};

std::unique_ptr<ChessPiece> PieceFactory::create_piece(const PieceConfig &config) {
    auto it = creators_.find(config.piece_type);

    // 棋子工厂预期行为：传入合法的枚举值，成功创建，不应返回 nullptr
    // 不合法的枚举值：
    //      未初始化的随机枚举值
    //      在 map 中漏写某棋子类型的映射逻辑
    // 上述不合法的枚举值属于开发阶段的问题，用 assert
    assert(it != creators_.end() &&
           "PieceFactory::create_piece: 漏写某些棋子类型的映射逻辑或者传入未初始化的随机枚举值");

    return it->second(config.side_tag, config.pos);
}
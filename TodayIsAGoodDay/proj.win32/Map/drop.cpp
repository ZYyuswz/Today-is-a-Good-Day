#include "drop.h"

// 静态成员初始化
std::mt19937 Drop::gen = std::mt19937(std::random_device{}());

// 随机生成掉落物数量
int Drop::generateRandomCount(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

// 构造函数
Drop::Drop(const Vec2& position, Layer* targetLayer) : dropPosition(position), targetLayer(targetLayer) {}

// 添加掉落物
void Drop::addDropItem(const std::string& itemType, const std::string& texturePath) {
    DropItem newItem;
    newItem.type = itemType;
    newItem.id = nextDropId++;  // 为每个掉落物分配唯一的 ID，并递增 nextDropId
    newItem.texturePath = texturePath;
    newItem.position = dropPosition;  // 初始位置为掉落物的生成位置
    dropItems.push_back(newItem);
}

// 生成掉落物
void Drop::generate() {
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    if (!targetLayer) {
        CCLOG("Drop object has no target layer!");
        return;
    }
    // 创建一个浮点型的均匀分布范围，表示掉落物偏移量
    std::uniform_real_distribution<float> dist(-spreadRadius, spreadRadius);

    for (const auto& item : dropItems) {
        auto dropSprite = Sprite::create();
        if (!dropSprite) {
            CCLOG("Failed to load drop sprite texture: %s", item.texturePath.c_str());
            continue;
        }
        // 随机偏移生成位置
        Vec2 offset(dist(gen), dist(gen));
        // 设置图片
        dropSprite->setSpriteFrame(item.texturePath);
        // 设置掉落位置
        dropSprite->setPosition(dropPosition + offset);
        // 使用 ID 设置标记
        dropSprite->setTag(item.id);
        // 将掉落物添加到目标层
        targetLayer->addChild(dropSprite);
    }
}

// 删除掉落物（根据 ID）
void Drop::removeDropItemById(int id) {
    if (!targetLayer) {
        CCLOG("Drop object has no target layer!");
        return;
    }
    // 遍历目标层的所有子节点
    for (auto& child : targetLayer->getChildren()) {
        if (child->getTag() == id) { // 检查子节点的标记是否匹配
            child->removeFromParent(); // 移除匹配的子节点
            return; // 找到并删除后返回
        }
    }
    CCLOG("Drop item with ID %d not found.", id);
}

// TreeDrop 构造函数
TreeDrop::TreeDrop(const Vec2& position, Layer* targetLayer) : Drop(position, targetLayer) {
    // 随机生成 1 到 5 个 wood
    int woodCount = generateRandomCount(1, 5);
    // 随机生成 0 到 1 个 树苗
    int saplingCount = generateRandomCount(0, 1);
    // 添加随机数量的 wood 掉落物
    for (int i = 0; i < woodCount; i++) {
        addDropItem("wood", "wood.png");
    }
    // 添加随机数量的 树苗 掉落物
    for (int i = 0; i < saplingCount; i++) {
        addDropItem("sapling", "sapling.png");
    }
}

// StoneDrop 构造函数
StoneDrop::StoneDrop(const Vec2& position, Layer* targetLayer, StoneType type) : Drop(position, targetLayer) {
    // 获取掉落物的类型和贴图路径
    auto it = stoneDropMap.find(type);
    if (it == stoneDropMap.end()) {
        CCLOG("Invalid StoneType: %d", static_cast<int>(type));
        return;
    }
    const std::string& itemType = it->second.first;
    const std::string& texturePath = it->second.second;
    // 随机生成掉落物数量
    int count = generateRandomCount(2, 4);
    // 添加随机数量的掉落物
    for (int i = 0; i < count; i++) {
        addDropItem(itemType, texturePath);
    }
}

// 静态成员初始化
const std::unordered_map<StoneType, std::pair<std::string, std::string>> StoneDrop::stoneDropMap = {
    {StoneType::Stone, {"stone_drop", "stone_drop.png"}},
    {StoneType::Copper, {"copper_drop", "copper_drop.png"}},
    {StoneType::Iron, {"iron_drop", "iron_drop.png"}},
    {StoneType::Gold, {"gold_drop", "gold_drop.png"}},
    {StoneType::Coal, {"coal_drop", "coal_drop.png"}}
};
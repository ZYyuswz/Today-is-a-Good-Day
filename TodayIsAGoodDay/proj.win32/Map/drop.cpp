#include "drop.h"

// 构造函数
Drop::Drop(const Vec2& position, Layer* targetLayer, TMXTiledMap* tileMap)
    : dropPosition(position), targetLayer(targetLayer), tileMap(tileMap) {}

// 静态成员初始化
std::mt19937 Drop::gen = std::mt19937(std::random_device{}());

// 随机生成掉落物数量
int Drop::generateRandomCount(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

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
    if (!targetLayer) {
        CCLOG("Drop object has no target layer!");
        return;
    }
    // 创建一个浮点型的均匀分布范围，表示掉落物偏移量
    std::uniform_real_distribution<float> dist(-spreadRadius, spreadRadius);

    for (const auto& item : dropItems) {
        auto dropSprite = new Dropper(dropPosition);
        if (!dropSprite) {
            CCLOG("Failed to load drop sprite texture: %s", item.texturePath.c_str());
            continue;
        }
        // 随机偏移生成位置
        Vec2 offset(dist(gen), dist(gen));
        // 设置图片
        dropSprite->setSpriteFrame(item.texturePath);
        dropSprite->setScale(DROPS_SCALE);
        // 获取像素坐标
        const Size mapSize = tileMap->getMapSize();
        const Size tileSize = tileMap->getTileSize();
        Vec2 pixelPosition = getTilePixelPosition(dropPosition, tileSize, mapSize, TileCorner::CENTER);
        // 设置锚点
        dropSprite->setAnchorPoint(Vec2(0.5, 0.5));
        // 设置掉落位置
        dropSprite->setPosition(pixelPosition + offset);
        // 使用 ID 设置标记
        dropSprite->setTag(item.id);
        // 将精灵的图像上下颠倒
        dropSprite->setFlippedY(false);
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
TreeDrop::TreeDrop(const Vec2& position, Layer* targetLayer, TMXTiledMap* tileMap)
    : Drop(position, targetLayer, tileMap) {
    // 随机生成 1 到 5 个 wood
    int woodCount = generateRandomCount(1, 5);
    // 随机生成 0 到 1 个 树苗
    int seedCount = generateRandomCount(0, 1);
    // 添加随机数量的 wood 掉落物
    for (int i = 0; i < woodCount; i++) {
        addDropItem("wood_drop", "wood_drop.png");
    }
    // 添加随机数量的种子掉落物
    for (int i = 0; i < seedCount; i++) {
        addDropItem("seed_drop", "seed_drop.png");
    }
}

// StoneDrop 构造函数
StoneDrop::StoneDrop(const Vec2& position, Layer* targetLayer, StoneType type, TMXTiledMap* tileMap) 
    : Drop(position, targetLayer, tileMap) {
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
    {StoneType::Silver, {"silver_drop", "silver_drop.png"}},
    {StoneType::Gold, {"gold_drop", "gold_drop.png"}},
    {StoneType::Coal, {"coal_drop", "coal_drop.png"}}
};


// CropsDrop 构造函数
CropsDrop::CropsDrop(const Vec2& position, Layer* targetLayer, CropsType type, TMXTiledMap* tileMap) 
    : Drop(position, targetLayer, tileMap) {
    // 获取掉落物的类型和贴图路径
    auto it = cropsDropMap.find(type);
    if (it == cropsDropMap.end()) {
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

// 农作物类型到掉落物类型和贴图路径的映射表
const std::unordered_map<CropsType, std::pair<std::string, std::string>> CropsDrop::cropsDropMap = {
    // 春季作物
    {CropsType::Carrot, {"carrot_drop", "carrot_drop.png"}},
    {CropsType::Garlic, {"garlic_drop", "garlic_drop.png"}},
    {CropsType::Potato, {"potato_drop", "potato_drop.png"}},
    // 夏季作物
    {CropsType::Corn, {"corn_drop", "corn_drop.png"}},
    {CropsType::Melon, {"melon_drop", "melon_drop.png"}},
    {CropsType::Tomato, {"tomato_drop", "tomato_drop.png"}},
    // 秋季作物
    {CropsType::Cabbage, {"cabbage_drop", "cabbage_drop.png"}},
    {CropsType::Eggplant, {"eggplant_drop", "eggplant_drop.png"}},
    {CropsType::Pumpkin, {"pumpkin_drop", "pumpkin_drop.png"}},
    // 酸菜
    {CropsType::Withered, {"",""}}
};
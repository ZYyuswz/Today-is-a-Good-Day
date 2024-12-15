#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
#include "definition.h"

USING_NS_CC;

// 游戏开始需要创建掉落物层并加载掉落.plist
//auto dropLayer = Layer::create();
//dropLayer->setName("DropLayer");
//this->addChild(dropLayer);

// 加载纹理图集
//auto spriteFrameCache = SpriteFrameCache::getInstance();
//spriteFrameCache->addSpriteFramesWithFile("Drop/drop.plist");


// 掉落物类型结构
struct DropItem {
    std::string type;        // 掉落物的类型
    int id;                  // 唯一标识符
    std::string texturePath; // 掉落物的贴图路径
    Vec2 position;           // 掉落物的当前坐标
};

class Drop {
protected:
    Vec2 dropPosition;                       // 掉落物的初始坐标
    std::vector<DropItem> dropItems;         // 掉落物的类型和贴图列表
    float spreadRadius = 5.0f;               // 掉落物散开半径
    Layer* targetLayer;                      // 目标层
    int nextDropId = 0;                      // 用于生成唯一 ID

    // 随机数生成器
    static std::mt19937 gen;

    // 随机生成掉落物数量
    int generateRandomCount(int min, int max);

public:
    // 构造函数
    Drop(const Vec2& position, Layer* targetLayer);

    // 添加掉落物
    void addDropItem(const std::string& itemType, const std::string& texturePath);

    // 生成掉落物
    void generate();

    // 删除掉落物（根据 ID）
    void removeDropItemById(int id);
};

class TreeDrop : public Drop {
public:
    // 构造函数
    TreeDrop(const Vec2& position, Layer* targetLayer);
};

class StoneDrop : public Drop {
private:
    // 石头类型到掉落物类型和贴图路径的映射表
    static const std::unordered_map<StoneType, std::pair<std::string, std::string>> stoneDropMap;

public:
    // 构造函数
    StoneDrop(const Vec2& position, Layer* targetLayer, StoneType type);
};

class CropsDrop : public Drop {
private:
    // 农作物类型到掉落物类型和贴图路径的映射表
    static const std::unordered_map<CropsType, std::pair<std::string, std::string>> cropsDropMap;
public:
    // 构造函数
    CropsDrop(const Vec2& position, Layer* targetLayer, CropsType type);
};
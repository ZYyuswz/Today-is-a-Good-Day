#pragma once
#include "cocos2d.h"
#include <vector>
#include <string>
#include <random>
#include <unordered_map>
#include "definition.h"
#include "map.h"
USING_NS_CC;

// 掉落物组类型结构
struct DropItem {
    std::string type;        // 掉落物的类型
    int id;                  // 唯一标识符
    std::string texturePath; // 掉落物的贴图路径
    Vec2 position;           // 掉落物的当前坐标
};

// 掉落物类型结构
class Dropper : public Sprite{
public:
    std::string type;
    Vec2 tilePosition;
    Dropper(Vec2 tile) :tilePosition(tile){}
    // 获取掉落物的瓦片坐标
    Vec2 getTilePosition() { return tilePosition; }
};

class Drop { 
protected:
    Vec2 dropPosition;                       // 掉落物的初始坐标
    std::vector<DropItem> dropItems;         // 掉落物的类型和贴图列表
    float spreadRadius = 5.0f;               // 掉落物散开半径
    Layer* targetLayer;                      // 目标层
    int nextDropId = 0;                      // 用于生成唯一 ID
    TMXTiledMap* tileMap;                    // 地图指针
    // 随机数生成器
    static std::mt19937 gen;

    // 随机生成掉落物数量
    int generateRandomCount(int min, int max);

public:
    // 构造函数
    Drop(const Vec2& position, Layer* targetLayer, TMXTiledMap* tileMap);

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
    TreeDrop(const Vec2& position, Layer* targetLayer, TMXTiledMap* tileMap);
};

class StoneDrop : public Drop {
private:
    // 石头类型到掉落物类型和贴图路径的映射表
    static const std::unordered_map<StoneType, std::pair<std::string, std::string>> stoneDropMap;

public:
    // 构造函数
    StoneDrop(const Vec2& position, Layer* targetLayer, StoneType type, TMXTiledMap* tileMap);
};

class CropsDrop : public Drop {
private:
    // 农作物类型到掉落物类型和贴图路径的映射表
    static const std::unordered_map<CropsType, std::pair<std::string, std::string>> cropsDropMap;
public:
    // 构造函数
    CropsDrop(const Vec2& position, Layer* targetLayer, CropsType type, TMXTiledMap* tileMap);
};
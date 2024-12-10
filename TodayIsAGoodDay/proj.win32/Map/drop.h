#pragma once
// 游戏开始需要创建掉落物层
// auto dropLayer = Layer::create();
// scene->addChild(dropLayer);
#include "cocos2d.h"
#include <vector>
#include <string>
#include <random>

USING_NS_CC;

// 掉落物类型结构
struct DropItem {
    std::string type;        // 掉落物的类型
    std::string texturePath; // 掉落物的贴图路径
};

class Drop : public Sprite {
protected:
    Vec2 dropPosition;                       // 掉落物的初始坐标
    std::vector<DropItem> dropItems;         // 掉落物的类型和贴图列表
    float spreadRadius = 5.0f;               // 掉落物散开半径
    Layer* targetLayer;                       // 目标层

public:
    // 构造函数
    Drop(const Vec2& position, Layer* targetLayer) : dropPosition(position), targetLayer(targetLayer) {}

    // 添加掉落物
    void addDropItem(const std::string& itemType, const std::string& texturePath) {
        dropItems.push_back({ itemType, texturePath });
    }

    // 生成掉落物
    void generate() {
        if (!targetLayer) {
            CCLOG("Drop object has no target layer!");
            return;
        }
        // 用于生成真正随机的种子
        std::random_device rd;
        // 随机数生成器
        std::mt19937 gen(rd());
        // 创建一个浮点型的均匀分布范围，表示掉落物偏移量
        std::uniform_real_distribution<float> dist(-spreadRadius, spreadRadius);

        for (const auto& item : dropItems) {
            auto dropSprite = Sprite::create(item.texturePath);
            if (!dropSprite) {
                CCLOG("Failed to load drop sprite texture: %s", item.texturePath.c_str());
                continue;
            }
            // 随机偏移生成位置
            Vec2 offset(dist(gen), dist(gen));
            dropSprite->setPosition(dropPosition + offset);
            // 将掉落物添加到目标层
            targetLayer->addChild(dropSprite);
        }
    }
};

class TreeDrop : public Drop {
public:
    // 构造函数
    TreeDrop(const Vec2& position, int generate_num, Layer* targetLayer) : Drop(position, targetLayer) {
        for (int i = 0; i < generate_num; i++) {
            addDropItem("wood", "res/drops/wood.png");
        }
    }
};

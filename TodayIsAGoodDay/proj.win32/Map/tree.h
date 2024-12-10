/* ----- 实现树的相关功能 ----- */
#pragma once
#include <string>
#include "cocos2d.h" 
#include "definition.h"
#include "Time.h"
#include "map.h"
#include "drop.h"

USING_NS_CC;

class Tree : public Sprite {
private:
    TreeType type;            // 树的种类
    Vec2 tilePosition;        // 树的瓦片坐标
    TreeStage stage;          // 树的阶段
    int growthDays;           // 生长天数
    int growthDays_threshold; // 生长天数阈值
    int health;               // 树的当前血量

public:
    // 构造函数
    Tree(TreeType type, Vec2 tilePosition, TreeStage st, Layer* objectLayer);

    // 更新生长天数（增加一天，并可能改变阶段）
    void updateStatus();

    // 树长大，替换贴图sprite
    void growToMature();

    // 播放被砍的动画 同时生成掉落物
    void playChopAnimation();

    // 判断树是否存活
    bool isAlive() const;

    // 减少血量
    void reduceHealth(int damage);

    // 更新树的贴图
    void updateSpriteBySeason();

    // 生成掉落物
    void generateDrops();
};

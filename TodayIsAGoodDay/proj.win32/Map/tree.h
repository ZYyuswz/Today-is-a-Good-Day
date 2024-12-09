/* ----- 实现树的相关功能 ----- */
#pragma once
#include <string>
#include "cocos2d.h" 
#include "definition.h"
USING_NS_CC;

class Tree {
public:
    // 枚举表示树的阶段
    enum class TreeStage {
        Sapling,  // 树苗
        Mature    // 大树
    };

protected: // 派生类需要访问这些成员
    int growthDays;              // 生长天数
    int health;                  // 树的当前血量
    int growthDays_threshold;    // 生长天数
    TreeStage stage;             // 当前阶段
    TreeType type;               // 树的种类
    Sprite* sprite;     // 树的贴图

public:
    // 构造函数
    Tree(TreeType type, TreeStage st = TreeStage::Sapling);

    // 初始化函数
    virtual void init();

    // 更新生长天数（增加一天，并可能改变阶段）
    void updateStatus();

    // 树长大，替换贴图sprite
    void growToMature();

    // 播放被砍的动画
    void playChopAnimation();

    // 减少血量
    void reduceHealth(int damage);

    // 判断树是否存活
    bool isAlive() const;

    // 产生掉落物
    void generateDrops();

    // 析构函数
    virtual ~Tree();
};

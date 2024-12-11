#pragma once
#include "cocos2d.h"
#include "map.h"
#include "definition.h"
#include "Control/Time.h"

USING_NS_CC;

class MyObject : public Sprite {
protected:
    Vec2 tilePosition;  // 物体的瓦片坐标
    int health = 10;         // 物体的血量
public:
    // 构造函数
    MyObject(){}

    // 获取瓦片坐标
    Vec2 getTilePosition() const { return tilePosition; }

    // 获取血量
    int getHealth() const { return health; }

    // 减少血量
    void reduceHealth(int damage) {
        health -= damage;
        if (health <= 0) {
            // 物体被摧毁
            deathAnimation();// 死亡动画
            this->removeFromParent(); // 移除
            generateDrops(); // 产生掉落物
        }
    }

    // 死亡动画
    virtual void deathAnimation() = 0;

    // 产生掉落物
    virtual void generateDrops(){}
};


class GrowObject : public MyObject {
protected:
    int growthDays = 0;              // 生长天数
    int growthDaysThreshold = 3;     // 生长天数阈值
    Stage stage = Stage::Childhood;  // 当前阶段

public:
    // 构造函数
    GrowObject(){}

    // 更新生长天数（增加一天，并可能改变阶段）
    void updateStatus() {
        if (stage == Stage::Mature) 
            return;
        growthDays++;
        if (growthDays >= growthDaysThreshold) {
            health = 100;
            stage = Stage::Mature;
            growToMature();  // 生长完成时的回调
        }
    }

    // 生长完成时的回调
    virtual void growToMature() = 0;
};


class DeadObject : public MyObject {
public:
    // 构造函数
    DeadObject(){}
};
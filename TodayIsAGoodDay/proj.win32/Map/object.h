#pragma once
#include "map.h"
#include "definition.h"

USING_NS_CC;

class Time;  // 前向声明 Time 类

// 抽象类
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
    virtual void reduceHealth(int damage) {
        health -= damage;
        if (health <= 0) {
            // 物体被摧毁
            auto deathAnim = CallFunc::create([this]() {
                deathAnimation();  // 播放死亡动画
                });
            auto generateDropsAction = CallFunc::create([this]() {
                generateDrops();   // 产生掉落物
                });
            auto removeAction = CallFunc::create([this]() {
                this->removeFromParent();  // 移除对象
                });
            auto delay = DelayTime::create(1.0f);  // 延迟1秒
            // 按顺序执行动作
            this->runAction(Sequence::create(
                deathAnim,
                delay,
                generateDropsAction,
                removeAction,
                nullptr
            ));
        }
    }

    // 死亡动画
    virtual void deathAnimation() = 0;

    // 产生掉落物
    virtual void generateDrops(){}
};

// 需要注意每日更新活物的状态时候，需要getRunningScene()
// 所以要依此把所有场景变成RunningScene然后依此更新所有内容
// 抽象类
class GrowObject : public MyObject {
protected:
    int growthDays = 0;              // 生长天数
    Stage stage = Stage::Childhood;  // 当前阶段

public:
    // 构造函数
    GrowObject(){}

    // 更新生长天数（增加一天，并可能改变阶段）
    virtual void update() = 0;

    Stage getStage() { return stage; }
};

// 抽象类
class DeadObject : public MyObject {
public:
    // 构造函数
    DeadObject(){}
};
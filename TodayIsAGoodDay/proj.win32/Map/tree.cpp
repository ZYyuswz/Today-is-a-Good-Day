/* ----- 实现树的相关功能 ----- */

#include "tree.h"


// 构造函数
Tree::Tree(TreeType type, TreeStage st){
    growthDays = 0;
    stage = st;
    this->type = type;  // 初始化树种类
    // 根据树种类和阶段，设置不同的贴图
    if (stage == TreeStage::Sapling) {
        switch (type) {
            case TreeType::Oak:
                sprite = cocos2d::Sprite::create("oak_sapling.png");  // 小橡树贴图
                break;
            case TreeType::Pine:
                sprite = cocos2d::Sprite::create("pine_sapling.png"); // 小松树贴图
                break;
            case TreeType::Maple:
                sprite = cocos2d::Sprite::create("maple_sapling.png"); // 小枫树贴图
                break;
            default:
                sprite = nullptr;
                break;
        }
    }
    else {
        switch (type) {
            case TreeType::Oak:
                sprite = cocos2d::Sprite::create("oak_mature.png");  // 成熟橡树贴图
                break;
            case TreeType::Pine:
                sprite = cocos2d::Sprite::create("pine_mature.png"); // 成熟松树贴图
                break;
            case TreeType::Maple:
                sprite = cocos2d::Sprite::create("maple_mature.png"); // 成熟枫树贴图
                break;
            default:
                sprite = nullptr;
                break;
        }
    }
    if (!sprite) {
        CCLOG("Failed to load tree sprite!");
    }
    init();
}

void Tree::init() {
    // 默认生长天数为五天
    growthDays_threshold = 5;
    // 默认血量
    if (stage == TreeStage::Sapling)
        health = 10;
    else
        health = 100;
}

// 更新生长天数（增加一天，并可能改变阶段）
void Tree::updateStatus() {
    if (growthDays >= growthDays_threshold || stage == TreeStage::Mature)
        return;
    growthDays++;
    if (growthDays >= growthDays_threshold) {
        health = 100;
        stage = TreeStage::Mature;
        growToMature();
    }
    return;
}

// 树长大，替换贴图sprite
void Tree::growToMature() {
    // 根据树的种类，更新成熟阶段的贴图
    if (sprite) {
        switch (type) {
            case TreeType::Oak:
                sprite->setTexture("oak_mature.png");
                break;
            case TreeType::Pine:
                sprite->setTexture("pine_mature.png");
                break;
            case TreeType::Maple:
                sprite->setTexture("maple_mature.png");
                break;
            default:
                break;
        }
    }
}

// 播放被砍的动画
void Tree::playChopAnimation() {
    if (sprite) {
        sprite->runAction(cocos2d::RotateBy::create(0.5f, 90));
        sprite->runAction(cocos2d::FadeOut::create(0.5f));
    }
    generateDrops();
}

// 产生掉落物
void Tree::generateDrops() {

}

// 判断树是否存活
bool Tree::isAlive() const {
    return health > 0;
}

// 减少血量
void Tree::reduceHealth(int damage) {
    health -= damage;
    if (!isAlive()) {
        // 播放动画
        playChopAnimation();
        // 销毁
        if (sprite) {
            sprite->removeFromParent();  // 从父节点移除
            sprite = nullptr;
        }
    }
}

// 析构函数
Tree::~Tree() {
    // 清理资源
    if (sprite) {
        sprite->removeFromParent(); // 从父节点中移除
        sprite = nullptr;
    }
}
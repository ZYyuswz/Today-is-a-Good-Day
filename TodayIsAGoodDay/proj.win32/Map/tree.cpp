/* ----- 实现树的相关功能 ----- */

#include "tree.h"

// 构造函数
Tree::Tree(TreeType type, TreeStage st){
    growthDays = 0;
    stage = st;
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
    // 默认为橡树
    if (stage == TreeStage::Sapling)
        sprite = cocos2d::Sprite::create("oak_sapling.png"); // 小橡树贴图
    else
        sprite = cocos2d::Sprite::create("oak_mature.png"); // 橡树贴图
}

// 更新生长天数（增加一天，并可能改变阶段）
void Tree::incrementGrowth() {
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

void Tree::growToMature() {
    // 替换贴图为大树
}

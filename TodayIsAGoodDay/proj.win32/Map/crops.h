// 庄稼类
#pragma once
#include "object.h"

class Crops : public GrowObject {
private:
    std::string stageImages[3];  // 存储每个阶段的图片路径
    std::vector<int> growthStageThreshold;
public:
    // 构造函数
    Crops(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st);

    // 更新生长天数（增加一天，并可能改变阶段）
    void update() override;

    // 死亡动画
    void deathAnimation() override;

    // 产生掉落物
    void generateDrops() override;

    // 获取当前阶段的图片路径
    std::string getCurrentStageImage() const;

    // 设置当前阶段的图片
    void setCurrentStageImage();
};
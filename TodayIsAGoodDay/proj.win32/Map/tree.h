/* ----- 实现树的相关功能 ----- */
#pragma once
#include "object.h"
#include "drop.h"
#include "Control\Time.h"

USING_NS_CC;

class Tree : public GrowObject {
private:
    TreeType type; // 树的种类
public:
    // 构造函数
    Tree(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, TreeType ty, Stage st = Stage::Childhood);

    // 在瓦片地图上随机生成 num 个树苗
    static void randomGenerate(TMXTiledMap* tileMap, Layer* objectLayer, int num, Stage stage);

    // 静态方法：遍历objectLayer的所有子节点并调用update
    static void updateAll(Layer* objectLayer);

    // 更新树的贴图
    void update() override;

    // 死亡动画
    void deathAnimation() override;

    // 产生掉落物
    void generateDrops() override;

    // 设置树的透明度
    void reduceOpacity();

    // 恢复树的透明度
    void restoreOpacity();
};

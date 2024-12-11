/* ----- 实现树的相关功能 ----- */
#pragma once
#include "object.h"
#include "drop.h"

USING_NS_CC;

class Tree : public GrowObject {
private:
    TreeType type; // 树的种类
public:
    // 构造函数
    Tree(TMXTiledMap* tileMap, Vec2 tile, Layer* objectLayer, TreeType ty,  Stage st);

    // 更新树的贴图
    void updateSpriteBySeason();

    // 在瓦片地图上随机生成 num 个树苗
    static void randomGenerate(int num, TMXTiledMap* tileMap, Layer* objectLayer);

protected:
    // 死亡动画
    void deathAnimation() override;

    // 产生掉落物
    void generateDrops() override;

    // 生长完成时的回调
    void growToMature() override;
};
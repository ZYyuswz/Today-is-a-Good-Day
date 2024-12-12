#pragma once
#include "object.h"
#include "drop.h" // 假设掉落物的定义在这里

class Stone : public DeadObject {
private:
    StoneType type; // 石头的种类
public:
    // 构造函数
    Stone(TMXTiledMap* tileMap, Layer* objectLayer, const Vec2& tile,  StoneType ty);

    // 在瓦片地图上随机生成 num 个石头
    static void randomGenerate(int num, StoneType type, TMXTiledMap* tileMap, Layer* objectLayer);

protected:

    // 死亡动画
    void deathAnimation() override;

    // 产生掉落物
    void generateDrops() override;
};
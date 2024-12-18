// 庄稼类
#pragma once
#include "object.h"
#include "drop.h"
#include "Map/plough.h"

class Crops : public GrowObject {
protected:
    // 作物的生长季节
    Season cropsSeason;
    // 作物类型
    CropsType type;
    // 存储每个阶段的图片路径
    std::string stageImages[3];  
    // 生长阶段阈值
    std::vector<int> growthStageThreshold;
    // 地图指针
    TMXTiledMap* pMap;
    // 构造函数
    Crops(){}
public:
    // 更新生长天数
    void grow();
        
    // 死亡动画
    void deathAnimation() override;

    // 产生掉落物
    void generateDrops() override;

    // 生长
    void update() override;

    // 收获
    void harvest();

    // 扣血
    virtual void reduceHealth(int damage);

    // 静态方法：遍历objectLayer的所有子节点并调用update
    static void updateAll(Layer* objectLayer);
};

// 酸菜类
class Withered : public Crops {
public:
    Withered(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
    void update() override {};
};

// 胡萝卜类
class Carrot : public Crops {
public:
    Carrot(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 大蒜类
class Garlic : public Crops {
public:
    Garlic(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 土豆类
class Potato : public Crops {
public:
    Potato(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 玉米类
class Corn : public Crops {
public:
    Corn(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 甜瓜类
class Melon : public Crops {
public:
    Melon(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 西红柿类
class Tomato : public Crops {
public:
    Tomato(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 小白菜类
class Cabbage : public Crops {
public:
    Cabbage(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 茄子类
class Eggplant : public Crops {
public:
    Eggplant(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};

// 南瓜类
class Pumpkin : public Crops {
public:
    Pumpkin(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st = Stage::Childhood);
};
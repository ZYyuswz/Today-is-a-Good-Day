#pragma once
#include "cocos2d.h"
#include "definition.h"
#include "map.h"
#include "Control/Time.h"
USING_NS_CC;

class Plough : public Sprite{
private:
    LandState state;
    int non_watered_count; 
    Vec2 tilePosition; // 瓦片坐标
    // 静态成员变量，用于记录需要移除的对象
    static std::vector<Node*> nodesToRemove;  // 使用std::list，避免迭代器失效的问题
public:
    // 构造函数
    Plough(TMXTiledMap* tileMap, Layer* ploughLayer,const Vec2 tile, LandState state = LandState::Tilled);
    // 天数更新，遍历当前图层所有耕地更新
    void update();
    // 浇水
    void water();
    // 施肥
    void fertilize();
    // 还原（耕地）
    void restore();
    // 获取瓦片坐标
    Vec2 getTilePosition() const { return tilePosition; } 
    // 获取状态
    LandState getState() const { return state; }
    // 静态方法：遍历ploughLayer的所有子节点并调用update()
    static void updateAll(Layer* ploughLayer);
};


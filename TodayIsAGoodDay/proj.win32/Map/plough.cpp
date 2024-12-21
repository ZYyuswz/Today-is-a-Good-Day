/* ----- 耕地类 实现每一格方块属性和功能 ----- */
#include "plough.h"

// 定义静态成员变量
std::vector<Node*> Plough::nodesToRemove;  // 使用std::list，避免迭代器失效的问题

// 构造函数
Plough::Plough(TMXTiledMap* tileMap, Layer* ploughLayer,const Vec2 tile, LandState state){
    this->state = state;
    this->tilePosition = tile;
    this->non_watered_count = 0;
    // 初始化精灵
    if(state == LandState::Tilled)
        this->setSpriteFrame("tilled.png");
    else if(state == LandState::Watered)
        this->setSpriteFrame("watered.png");
    else if(state == LandState::Fertilized)
        this->setSpriteFrame("fertilized.png");
    else 
        this->setSpriteFrame("fertilized-watered.png");
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.5f)); 
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到ploughLayer层
    ploughLayer->addChild(this);
}

// 浇水
void Plough::water() {
    if (state == LandState::Tilled) {
        state = LandState::Watered;
        this->setSpriteFrame("watered.png");  // 切换到已浇水图片
        non_watered_count = 0;                // 重置未浇水天数计数器
    }
    else if (state == LandState::Fertilized) {
        state = LandState::FertilizedWatered;
        this->setSpriteFrame("fertilized-watered.png");  // 切换到已浇水图片
        non_watered_count = 0;                           // 重置未浇水天数计数器
    }
}

// 施肥
void Plough::fertilize() {
    if (state == LandState::Tilled) {
        state = LandState::Fertilized;
        this->setSpriteFrame("fertilized.png");  // 切换到已浇水图片
    }
    else if (state == LandState::Watered) {
        state = LandState::FertilizedWatered;
        this->setSpriteFrame("fertilized-watered.png");  // 切换到已浇水图片
    }
}

// 还原（耕地）
void Plough::restore() {
    if (state == LandState::Watered) {
        state = LandState::Tilled;
        this->setSpriteFrame("tilled.png");  // 切换到已耕地图片
    }
    else if (state == LandState::FertilizedWatered) {
        state = LandState::Fertilized;
        this->setSpriteFrame("fertilized.png");  // 切换到已耕地图片
    }
}


// 天数更新，遍历当前图层所有耕地更新
void Plough::update(){
    // 天气
    Weather current_weather = GameTime::getInstance()->getWeather();
    if (state == LandState::Tilled) {
        if (current_weather == Weather::Sunny) {  // 晴天
            non_watered_count++;
            if (non_watered_count >= LAND_DESTORY_THRESHOLD) {
                nodesToRemove.push_back(this);  // 记录需要移除的对象
            }
        }
        else {  // 雨天
            water();  // 自动浇水
        }
    }
    else if (state == LandState::Watered) {
        if (current_weather == Weather::Sunny) {  // 晴天
            restore();  // 恢复为已耕地状态
        }
    }
    else if (state == LandState::Fertilized) {
        if (current_weather == Weather::Sunny) {  // 晴天
            non_watered_count++;
            if (non_watered_count >= LAND_DESTORY_THRESHOLD) {
                nodesToRemove.push_back(this);  // 记录需要移除的对象
            }
        }
        else {  // 雨天
            water();  // 自动浇水
        }
    }
    else if (state == LandState::FertilizedWatered) {
        if (current_weather == Weather::Sunny) {  // 晴天
            restore();  // 恢复为已耕地状态
        }
    }
}


// 静态方法：遍历 ploughLayer 的所有子节点并调用 update()
void Plough::updateAll(Layer* ploughLayer) {
    if (!ploughLayer) {
        CCLOG("ploughLayer is null!");
        return;
    }
    // 遍历 ploughLayer 的所有子节点
    for (auto child : ploughLayer->getChildren()) {
        // 检查子节点是否是 Plough 类的实例
        Plough* plough = dynamic_cast<Plough*>(child);
        if (plough) {
            plough->update();  // 调用 update() 方法
        }
    }
    // 遍历结束后统一移除对象
    for (auto it = nodesToRemove.begin(); it != nodesToRemove.end(); ) {
        (*it)->removeFromParent();  // 移除节点
        it = nodesToRemove.erase(it);  // 会删除当前元素，并返回一个指向被删除元素之后元素的迭代器
    }
    // 清空 nodesToRemove
    nodesToRemove.clear();
}
/* ----- 对整个项目均适用的工具集 ----- */

#include "totaltools.h"

#include "global.h"

#include <random>



USING_NS_CC;

//工具：瓦片地图坐标转换成屏幕像素坐标
/* 传入参数：
*  mapsize: size类型， 通过tileMap->getMapSize()方法获得当前地图大小
*  tilesize： size类型 ，通过tileMap->getTileSize()方法获得每个图块的大小
*  scale: float类型， 是最底层地图的缩放比例，可通过scale = tileMap ->getScale()方法获得，缺省为原地图大小为1.0f
* （其中，tilemap是自己的tmx图片名）
* 返回值：
* vec2类型：转换后在屏幕的坐标
*/
Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original,float scale = 1.0f)
{
	float x = original.x * tilesize.width;
	float y = original.y * tilesize.height;
	Vec2 screenpos = Vec2(x, y);
	screenpos = screenpos * scale;
	return screenpos;
}


//工具：将鼠标点击的位置转化成瓦片坐标
/* 传入参数：
*  const Vec2& worldPosition：鼠标点击位置的屏幕像素坐标
*  const Vec2& Tiledposition： 屏幕锚点的像素坐标
* 返回值：
* vec2类型：瓦片坐标
*/
Vec2 convertWorldToTileCoord(const Vec2& worldPosition, const Vec2& Tiledposition) {
    // 计算屏幕坐标与瓦片地图位置的差值
    Vec2 ScreenGap = worldPosition - Tiledposition;

    // 将差值转换为瓦片坐标
    Vec2 TiledGap = ScreenGap / (BEACH_SMALL_SCALE * TILESIZE);

    // 将结果转换为 int
    int tileX = static_cast<int>(TiledGap.x);
    int tileY = static_cast<int>(TiledGap.y);

    return Vec2(tileX, tileY);
}

/*工具：随机生成一组伯努利分布的离散变量
* 传入参数：
* double p 生成1的概率
* 返回值：
* 随机生成的一个bool值
*/
bool random_bernoulli(double p) {
    // 创建一个随机数生成器
    static std::random_device rd;  // 用于获取随机种子
    static std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
    std::bernoulli_distribution dist(p); // 创建一个伯努利分布，概率为p

    // 返回一个服从伯努利分布的随机数
    return dist(gen);

}

//工具：切换场景时移除人物
void people_remove_change()
{

    auto currentScene = Director::getInstance()->getRunningScene();
    // 获取当前场景中的人物层
    Layer* currentCharacterLayer = nullptr;
    for (auto child : currentScene->getChildren()) {
        currentCharacterLayer = dynamic_cast<Layer*>(child);
        if (currentCharacterLayer) {
            break;
        }
    }
    
    if (currentCharacterLayer) {
        // 手动调用 onExit()
        currentCharacterLayer->onExit();
        currentScene->removeChild(currentCharacterLayer);
    }

    leading_charactor._sprite->retain();
}

//工具：切换场景时添加人物
/* 传入参数：
*  const Vec2 change_vec2 切换后人物位置
*/
void people_change_scene(const Vec2 change_Vec2)
{

    auto newCharacterLayer = Layer::create();
    auto nowTiledMap = MapManager::getInstance()->getCurrentMap();
    auto nowScene = Director::getInstance()->getRunningScene();
    nowScene->addChild(newCharacterLayer); // 将人物层添加到当前场景中
//    leading_charactor._sprite = Sprite::create("/person/person_front_1.png");
    

        // 如果精灵不在运行中，可能需要重新初始化或重新添加
        leading_charactor._sprite->release();
        leading_charactor._sprite = Sprite::create("/person/person_front_1.png");
        newCharacterLayer->addChild(leading_charactor._sprite,PERSON_LAYER);
        leading_charactor._sprite->setPosition(change_Vec2);
}

/*工具：返回鼠标点击坐标的精灵的指针，如果没有为nullptr
* 传入参数：
* Vec2 tilePosition：鼠标点击的坐标
* 返回值：
* MyObject*：基类指针
*/
MyObject* getSpriteOnMap(Vec2 tilePosition) {
    //得到当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--getSpriteOnMap");
        return nullptr;
    }
    // 获取 objectLayer
    auto objectLayer = dynamic_cast<Layer*>(map->getChildByName("ObjectLayer"));
    if (!objectLayer) {
        CCLOG("ObjectLayer not found in the map!--getSpriteOnMap");
        return nullptr;
    }
    // 遍历 ObjectLayer 的子节点
    for (auto child : objectLayer->getChildren()) {
        // 检查子节点是否是 MyObject 类的实例
        MyObject* myObject = dynamic_cast<MyObject*>(child);
        if (myObject && myObject->getTilePosition() == tilePosition) {
            return myObject;
        }
    }
    return nullptr;
}

/*工具：返回鼠标点击坐标上有没有耕地，如果没有为false
* 传入参数：
* Vec2 tilePosition：鼠标点击的坐标
* 返回值：
* bool类型：有无耕地
*/
bool is_have_plough(Vec2 tilePosition)
{
    //得到当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--getSpriteOnMap");
        return nullptr;
    }
    // 获取 ploughLayer
    auto ploughLayer = dynamic_cast<Layer*>(map->getChildByName(PLOUGH_LAYER));
    if (!ploughLayer) {
        CCLOG("PloughLayer not found in the map!--getSpriteOnMap");
        return nullptr;
    }
    // 遍历 PloughLayer 的子节点
    for (auto child : ploughLayer->getChildren()) {
        // 检查子节点是否是 MyObject 类的实例
        Plough* myObject = dynamic_cast<Plough*>(child);
        if (myObject && myObject->getTilePosition() == tilePosition) {
            return true;
        }
    }
    return false;
}

std::vector<Dropper*>* getDrops(Vec2 personPosition) {
    auto pickDrops = new std::vector<Dropper*>();  // 创建一个新的 vector
    // 获取当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--getDrops");
        return nullptr;
    }
    // 获取 dropLayer
    auto dropLayer = dynamic_cast<Layer*>(map->getChildByName("DropLayer"));
    if (!dropLayer) {
        CCLOG("DropLayer not found in the map!--getDrops");
        return nullptr;
    }
    // 遍历 dropLayer 的子节点
    for (auto child : dropLayer->getChildren()) {
        // 转换为 Dropper 类
        Dropper* drop = dynamic_cast<Dropper*>(child);
        if (drop) {
            Vec2 dropPosition = drop->getTilePosition();
            double delta_x = dropPosition.x - personPosition.x;
            double delta_y = dropPosition.y - personPosition.y;
            // 在拾取半径内的需要添加
            if (abs(delta_x) <= PICK_RADIUS && abs(delta_y) <= PICK_RADIUS) {
                pickDrops->push_back(drop);
                dropLayer->removeChild(drop, false);  // 移除节点但不销毁
            }
        }
    }
    return pickDrops;
}


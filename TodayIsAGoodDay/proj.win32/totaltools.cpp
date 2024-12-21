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
Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original, float scale = 1.0f)
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
    newCharacterLayer->addChild(leading_charactor._sprite, PERSON_LAYER);
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
        return false;
    }
    // 获取 ploughLayer
    auto ploughLayer = dynamic_cast<Layer*>(map->getChildByName(PLOUGH_LAYER));
    if (!ploughLayer) {
        CCLOG("PloughLayer not found in the map!--getSpriteOnMap");
        return false;
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


/*工具：返回可拾取掉落物的vector容器
* 传入参数：
* Vec2 tilePosition：人物坐标
* 返回值：
* std::vector<Dropper*>*：储存掉落物指针vector指针
*/
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


/*工具：降低人物下方树的透明度并且将这些树储存在一个全局数组里
* 传入参数：
* Vec2 tilePosition：人物坐标
* 返回值：
* std::vector<Dropper*>*：储存掉落物指针vector指针
*/
// 储存目前被遮挡的树，树不遮挡人之后需要调用restoreOpacity()
std::vector<Tree*> tree_block;
// PS:逻辑是你每次移动时候要调用，treeBlock函数，然后再调用updateTreeBlock去还原没有遮挡的树
void treeBlock(Vec2 personPosition) {
    // 获取当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--treeBlock");
        return;
    }
    // 获取 objectLayer
    auto objectLayer = dynamic_cast<Layer*>(map->getChildByName("ObjectLayer"));
    if (!objectLayer) {
        CCLOG("ObjectLayer not found in the map!--getSpriteOnMap");
        return;
    }
    // 遍历 ObjectLayer 的子节点
    for (auto child : objectLayer->getChildren()) {
        // 检查子节点是否是 Tree 类的实例
        Tree* tree = dynamic_cast<Tree*>(child);
        if (tree) {
            Vec2 treePosition = tree->getTilePosition();
            double delta_x = treePosition.x - personPosition.x;
            double delta_y = treePosition.y - personPosition.y;
            // 在3*6的范围
            if (abs(delta_x) <= TREE_BLOCK_X && delta_y < TREE_BLOCK_Y) {
                tree->reduceOpacity();
                tree_block.push_back(tree);
            }
        }
    }
}

void updateTreeBlock(Vec2 personPosition) {
    // 遍历 ObjectLayer 的子节点
    for (auto it = tree_block.begin(); it != tree_block.end(); ) {
        Tree* tree = *it;
        Vec2 treePosition = tree->getTilePosition();
        double delta_x = treePosition.x - personPosition.x;
        double delta_y = treePosition.y - personPosition.y;
        // 在3*6的范围
        if (abs(delta_x) <= TREE_BLOCK_X && delta_y < TREE_BLOCK_Y) {
            // 什么也不干
            ++it;  // 继续遍历下一个元素
        }
        else {
            // 恢复透明度
            tree->restoreOpacity();
            it = tree_block.erase(it);  // 移除元素并更新迭代器
        }
    }
}

/*工具：返回鼠标点击坐标上有没有物体，如果没有为false
* 传入参数：
* Vec2 tilePosition：某个位置
* 返回值：
* bool类型：有无耕地
*/
bool is_have_object(Vec2 tilePosition)
{
    //得到当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--is_have_object");
        return false;
    }
    // 获取 objectLayer
    auto objectLayer = dynamic_cast<Layer*>(map->getChildByName("ObjectLayer"));
    if (!objectLayer) {
        CCLOG("ObjectLayer not found in the map!--is_have_object");
        return false;
    }
    // 遍历 ObjectLayer 的子节点
    for (auto child : objectLayer->getChildren()) {
        // 检查子节点是否是 MyObject 类的实例
        MyObject* myObject = dynamic_cast<MyObject*>(child);
        if (myObject && myObject->getTilePosition() == tilePosition) {
            return true;
        }
    }
    return false;


}


//判断是否为5种工具
bool isFiveTool(const std::string& name)
{
    if (name == "axe" || name == "hammer" || name == "draft" || name == "kettle" || name == "fishing_pole")
        return true;
    else
        return false;


}

/*工具：收获当前坐标的作物，如果作物没成熟或者没有就什么都不干
* 传入参数：
* Vec2 tilePosition：某个位置
*/
void harvest(Vec2 tilePosition) {
    // 获取当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--harvest");
        return;
    }
    // 获取 cropsLayer
    auto cropsLayer = dynamic_cast<Layer*>(map->getChildByName("CropsLayer"));
    if (!cropsLayer) {
        CCLOG("CropsLayer not found in the map!--harvest");
        return;
    }
    // 遍历 CropsLayer 的子节点
    for (auto child : cropsLayer->getChildren()) {
        // 检查子节点是否是 Crops 类的实例
        Crops* crop = dynamic_cast<Crops*>(child);
        if (crop && crop->getTilePosition() == tilePosition) { 
            // 检查是否成熟
            if (crop->getStage() == Stage::Mature) {
                crop->harvest();
            }
        }
    }

}
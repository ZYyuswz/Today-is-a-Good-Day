/* ----- 该文件夹主cpp ----- */
/* 详细内容参阅开发者手册 */

#include "person.h"
#include "global.h"
#include "totaltools.h"
#include <vector>
#include "Map/drop.h"

Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, const Vec2& Tiledposition);


/*关于图片，这里只给出了一张，如果要有选择角色功能的话，那么图片要不一样*/
Person::Person()

{

}
void Person::person_construction(const std::string& name, const int& sex, const std::string& farmName,
    Scene* currentScene, int level, int HP, int energy, int money)
{

    //初始化赋值
    _name = name;
    _sex = sex;
    _farmName = farmName;
    _level = level;
    _HP = HP;
    _money = money;
    _energy = energy;
     
    auto newCharacterLayer = Layer::create();
    currentScene->addChild(newCharacterLayer); // 将人物层添加到当前场景中
    // 创建一个精灵并添加到Person节点中
    _sprite = cocos2d::Sprite::create("/person/person_front_1.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 screenCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    _sprite->setPosition(screenCenter);

    if (_sprite)
    {
        newCharacterLayer->addChild(_sprite);
    }
    init();
    
    createAnimate();
    
}
bool Person::init()
{
    /*
    if (!Node::init())
    {
        return false;
    }
    */
    return true;
    
}

void Person::decreaseHP(const int attack)
{
    _HP -= attack;//扣血
    if (isDead()) {
        dead();
    }
}

void Person::dead()
{
    _HP /= 10;
    _money /= 10;
    _energy /= 10;
    //   setPosition(HOSPITAL_X, HOSPITAL_Y);
     //  Director::getInstance()->replaceScene(town); //切换场景为小镇
}

void Person::moneyUP(int deltaMoney)
{
    _money += deltaMoney;
    //预留函数接口
}

Vec2 Person::getTiledPosition()
{
    Vec2 PersonWP = _sprite->getPosition();
    Vec2 MapTP = MapManager::getInstance()->getCurrentMap()->getPosition();
    return convertWorldToTileCoord(PersonWP, MapTP);
}

Vec2 Person::getWorldPosition()
{
    return _sprite->getPosition();
}

void Person::levelUP()
{
    if (experience_all > 1000) {
        experience_all -= 1000;
        _level++;
    }
}

void Person::collectItems()
{
    Vec2 currentPosition = _sprite->getPosition();
    auto currentTiledMap = MapManager::getInstance()->getCurrentMap();
    Vec2 currentTiledPosition = convertWorldToTileCoord(currentPosition, currentTiledMap->getPosition());
    std::vector <DropItem>* dropVector;//= getDrops(currentTiledPosition);
    for (int i = 0; i < dropVector->size(); i++) {
        MyBag.addItem((*dropVector)[i].type);
    }
    delete dropVector;
}

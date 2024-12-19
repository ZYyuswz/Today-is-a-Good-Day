/* ----- ���ļ�����cpp ----- */
/* ��ϸ���ݲ��Ŀ������ֲ� */

#include "person.h"
#include "global.h"

Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, const Vec2& Tiledposition);
/*����ͼƬ������ֻ������һ�ţ����Ҫ��ѡ���ɫ���ܵĻ�����ôͼƬҪ��һ��*/
Person::Person()

{

}
void Person::person_construction(const std::string& name, const int& sex, const std::string& farmName,
    Scene* currentScene, int level, int HP, int energy, int money)
{

    //��ʼ����ֵ
    _name = name;
    _sex = sex;
    _farmName = farmName;
    _level = level;
    _HP = HP;
    _money = money;
    _energy = energy;

    auto characterLayer = Layer::create();
    currentScene->addChild(characterLayer); // ���������ӵ���ǰ������
    // ����һ�����鲢��ӵ�Person�ڵ���
    _sprite = cocos2d::Sprite::create("/person/person_front_1.png");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 screenCenter = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    _sprite->setPosition(screenCenter);

    if (_sprite)
    {
        characterLayer->addChild(_sprite, 3);
    }
    init();
    createAnimate();
    //    _sprite->runAction(_leftWalkAnimate);
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
    _HP -= attack;//��Ѫ
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
     //  Director::getInstance()->replaceScene(town); //�л�����ΪС��
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

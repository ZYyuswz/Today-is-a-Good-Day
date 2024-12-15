/* ----- 该文件夹主cpp ----- */
/* 详细内容参阅开发者手册 */

#include "person.h"

/*关于图片，这里只给出了一张，如果要有选择角色功能的话，那么图片要不一样*/
Person::Person(const std::string& name, const int& sex, const std::string& farmName,
    Scene* currentScene,int level, int HP, int energy, int money)
    : _name(name), _sex(sex), _level(level), _HP(HP),_money(money),_energy(energy),_farmName(farmName)
{
    auto characterLayer = Layer::create();
    currentScene->addChild(characterLayer); // 将人物层添加到当前场景中
    // 创建一个精灵并添加到Person节点中
    _sprite = cocos2d::Sprite::create("/person/person_front_1.png");
    _sprite->setPosition(500, 500);
    if (_sprite)
    {
        characterLayer->addChild(_sprite,3);
    }  
    init();
}

bool Person::init()
{
    if (!Node::init())
    {
        return false;
    }
    //初始化键盘监听器
    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Person::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(Person::onKeyReleased, this);

    // 确保事件分发器正确获取
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
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



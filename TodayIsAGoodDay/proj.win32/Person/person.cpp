/* ----- ���ļ�����cpp ----- */
/* ��ϸ���ݲ��Ŀ������ֲ� */

#include "person.h"

/*����ͼƬ������ֻ������һ�ţ����Ҫ��ѡ���ɫ���ܵĻ�����ôͼƬҪ��һ��*/
Person::Person(const std::string& name, const int& sex, const std::string& farmName,
    Scene* currentScene,int level, int HP, int energy, int money)
    : _name(name), _sex(sex), _level(level), _HP(HP),_money(money),_energy(energy),_farmName(farmName)
{
    auto characterLayer = Layer::create();
    currentScene->addChild(characterLayer); // ���������ӵ���ǰ������
    // ����һ�����鲢��ӵ�Person�ڵ���
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
    //��ʼ�����̼�����
    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Person::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(Person::onKeyReleased, this);

    // ȷ���¼��ַ�����ȷ��ȡ
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
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



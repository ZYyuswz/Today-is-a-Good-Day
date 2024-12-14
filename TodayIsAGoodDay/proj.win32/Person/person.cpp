/* ----- ���ļ�����cpp ----- */
/* ��ϸ���ݲ��Ŀ������ֲ� */

#include "person.h"

/*����ͼƬ������ֻ������һ�ţ����Ҫ��ѡ���ɫ���ܵĻ�����ôͼƬҪ��һ��*/
Person::Person(const std::string& name, const int& sex, const std::string& farmName,
    int level, int HP, int energy, int money)
    : _name(name), _sex(sex), _level(level), _HP(HP),_money(money),_energy(energy),_farmName(farmName)
{
    // ����һ�����鲢��ӵ�Person�ڵ���
    _sprite = cocos2d::Sprite::create("person_front_stand.png");
    if (_sprite)
    {
        this->addChild(_sprite);
    }

    // ��ʼ�����̼�����
    _keyboardListener = cocos2d::EventListenerKeyboard::create();
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

}

bool Person::init()
{
    if (!Node::init())
    {
        return false;
    }

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
    setPosition(HOSPITAL_X, HOSPITAL_Y);
    Director::getInstance()->replaceScene(town); //�л�����ΪС��
}



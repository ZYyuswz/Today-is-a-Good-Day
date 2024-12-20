#pragma once

#include "cocos2d.h"
#include "person.h"
USING_NS_CC;

//tool�ǿ����ֳֵ�
class Tool : public cocos2d::Node {
protected:
    std::string _name;
    int _level;
    int _attackPower;
    

public:
    cocos2d::Sprite* _toolsprite;
    Tool(){}
    Tool(const std::string& name, int level = 1, int attackPower = 0):_name(name),_level(level),_attackPower(attackPower){}
//    virtual ~Tool();

    bool init(const std::string& name, int level = 1, int attackPower = 0);
 //   CREATE_FUNC(Tool);

    
    // ��ȡ����������
    const std::string& getName() const { return _name; }
    void setName(const std::string& name) { _name = name; }

    int getLevel() const { return _level; }
    void setLevel(int level) { _level = level; }

    int getAttackPower() const { return _attackPower; }
    void setAttackPower(int attackPower) { _attackPower = attackPower; }

    // ʹ�ù���
//    virtual void use();

    // ��������
//    virtual void upgrade();
};
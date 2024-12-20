#pragma once

#include "cocos2d.h"

USING_NS_CC;

//tool是可以手持的
class Tool : public cocos2d::Node {
protected:
    std::string _name;
    int _level;
    int _attackPower;
    

public:
    cocos2d::Sprite* _toolsprite;

    Tool(const std::string& name, int level, int attackPower):_name(name),_level(level),_attackPower(attackPower){}
//    virtual ~Tool();

 //   virtual bool init();
 //   CREATE_FUNC(Tool);

    // 获取和设置属性
    const std::string& getName() const { return _name; }
    void setName(const std::string& name) { _name = name; }

    int getLevel() const { return _level; }
    void setLevel(int level) { _level = level; }

    int getAttackPower() const { return _attackPower; }
    void setAttackPower(int attackPower) { _attackPower = attackPower; }

    // 使用工具
//    virtual void use();

    // 升级工具
//    virtual void upgrade();
};
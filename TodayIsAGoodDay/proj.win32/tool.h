#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Tool : public cocos2d::Node {
protected:
    std::string _name;
    int _level;
    int _attackPower;
    cocos2d::Sprite* _sprite;

public:
    Tool(const std::string& name, int level, int attackPower);
    virtual ~Tool();

    virtual bool init();
    CREATE_FUNC(Tool);

    // 获取和设置属性
    std::string getName() const { return _name; }
    void setName(const std::string& name) { _name = name; }

    int getLevel() const { return _level; }
    void setLevel(int level) { _level = level; }

    int getAttackPower() const { return _attackPower; }
    void setAttackPower(int attackPower) { _attackPower = attackPower; }

    // 使用工具
    virtual void use();

    // 升级工具
    virtual void upgrade();
};
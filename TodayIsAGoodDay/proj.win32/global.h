#pragma once

#include "./Person/person.h"

//创建唯一主人公

extern Person* leading_charactor;

//控制主角层

// 专门负责主角移动和键盘输入的层
class PlayerControlLayer : public Layer
{
public:
    CREATE_FUNC(PlayerControlLayer);
    bool init() override;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void update(float dt) override;
    void setPlayer(Person* player);

    void onExit() override; // 添加 override 关键字

private:
    EventListenerKeyboard* _keyboardListener;
    Person* _player; // 指向要控制的主角
    bool _moveLeft;
    bool _moveRight;
    bool _moveUp;
    bool _moveDown;
    float _playerSpeed;

};
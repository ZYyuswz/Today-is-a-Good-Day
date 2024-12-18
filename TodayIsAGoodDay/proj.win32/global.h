#pragma once

#include "./Person/person.h"

//创建唯一主人公

extern Person leading_charactor;


//控制主角层

// 专门负责主角移动和键盘输入的层
class PlayerControlLayer : public Layer
{
public:
    CREATE_FUNC(PlayerControlLayer);
    bool init() override;
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void onMouseDown(Event* event); // 新增鼠标点击回调函数
    void update(float dt) override;
    void setPlayer(Person* player);

    void onExit() override; // 添加 override 关键字

private:
    EventListenerKeyboard* _keyboardListener;
    EventListenerMouse* _mouseListener; // 新增鼠标事件监听器
    Person* _player; // 指向要控制的主角
    bool _moveLeft;
    bool _moveRight;
    bool _moveUp;
    bool _moveDown;
    float _playerSpeed;

};



//场景管理
//获取当前场景和地图
#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

/**
 * MapManager 类：管理场景和地图的映射关系
 */
class MapManager
{
public:
    // 获取单例实例
    static MapManager* getInstance();

    // 注册场景和地图的映射关系
    void registerSceneMap(Scene* scene, TMXTiledMap* map);

    // 获取当前场景的地图
    TMXTiledMap* getCurrentMap();

private:
    // 构造函数和析构函数
    MapManager();
    ~MapManager();

    // 场景切换事件回调
    void onSceneChange(EventCustom* event);

private:
    // 单例实例
    static MapManager* _instance;

    // 当前场景
    Scene* _currentScene;

    // 场景和地图的映射关系
    std::unordered_map<Scene*, TMXTiledMap*> _sceneMap;
};

#endif // __MAP_MANAGER_H__
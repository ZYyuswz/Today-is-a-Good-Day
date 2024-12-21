
﻿#include "ui/CocosGUI.h"
#include"cocos2d.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"
#include"Person/person.h"
#include"global.h"
#include "controler.h"
#include "Map/tree.h"
#include"Person/tool.h"

USING_NS_CC;

//创建主人公

Person leading_charactor ;


/*联网socket初始化*/
// 初始化全局变量
SOCKET global_socket = INVALID_SOCKET;

bool PlayerControlLayer::init() {
    if (!Layer::init())
    {
        return false;
    }
    _moveLeft = false;
    _moveRight = false;
    _moveUp = false;
    _moveDown = false;
    _playerSpeed = 100.0f;
    // 1. 创建键盘事件监听器
    _keyboardListener = EventListenerKeyboard::create();

    // 2. 设置事件回调函数
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(PlayerControlLayer::onKeyPressed, this);
    _keyboardListener->onKeyReleased = CC_CALLBACK_2(PlayerControlLayer::onKeyReleased, this);

    // 3. 添加监听器到事件分发器
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);

    // 创建鼠标事件监听器
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(PlayerControlLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    //this->scheduleUpdate();
    return true;
}

void PlayerControlLayer::setPlayer(Person* player) {
    this->_player = player;
}


void PlayerControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            _moveLeft = true;

            _isRunning = true;
            _currentDirection = "moveLeft"; // 设置当前方向
            Director::getInstance()->getScheduler()->schedule(
                CC_CALLBACK_1(PlayerControlLayer::movePlayer, this),
                this,
                0.0f,
                kRepeatForever,
                0.0f,
                false,
                "moveLeft"
            );



            break;
        case EventKeyboard::KeyCode::KEY_D:
            _moveRight = true;
            _isRunning = true;
            _currentDirection = "moveRight"; // 设置当前方向
            Director::getInstance()->getScheduler()->schedule(
                CC_CALLBACK_1(PlayerControlLayer::movePlayer, this),
                this,
                0.0f,
                kRepeatForever,
                0.0f,
                false,
                "moveRight"
            );

            break;
        case EventKeyboard::KeyCode::KEY_W:
            _moveUp = true;
            _isRunning = true;
            _currentDirection = "moveUp"; // 设置当前方向
            Director::getInstance()->getScheduler()->schedule(
                CC_CALLBACK_1(PlayerControlLayer::movePlayer, this),
                this,
                0.0f,
                kRepeatForever,
                0.0f,
                false,
                "moveUp"
            );

            break;
        case EventKeyboard::KeyCode::KEY_S:
            _moveDown = true;
            _isRunning = true;
            _currentDirection = "moveDown"; // 设置当前方向
            Director::getInstance()->getScheduler()->schedule(
                CC_CALLBACK_1(PlayerControlLayer::movePlayer, this),
                this,
                0.0f,
                kRepeatForever,
                0.0f,
                false,
                "moveDown"
            );

            break;
        case EventKeyboard::KeyCode::KEY_E:
            leading_charactor.MyBag.changeBag();
            break;
        case EventKeyboard::KeyCode::KEY_0:
            leading_charactor.useTools();
            break;
        case EventKeyboard::KeyCode::KEY_1://限制变量的生命周期
        {
            if (leading_charactor.getTool() != nullptr) {
                delete leading_charactor.getTool();
            }
            std::string toolName = leading_charactor.MyBag.getItems()[0].name;
            Tool* changeTool;
            if (isFiveTool(toolName))
                changeTool = new Tool(toolName, leading_charactor.toolLevel());
            else
                changeTool = new Tool(toolName);
            leading_charactor.setTool(changeTool);
        }
        break;
        case EventKeyboard::KeyCode::KEY_2:
        {
            if (leading_charactor.getTool() != nullptr) {
                delete leading_charactor.getTool();
            }
            std::string toolName = leading_charactor.MyBag.getItems()[1].name;
            Tool* changeTool;
            if (isFiveTool(toolName))
                changeTool = new Tool(toolName, leading_charactor.toolLevel());
            else
                changeTool = new Tool(toolName);
            leading_charactor.setTool(changeTool);
        }
        break;
        case EventKeyboard::KeyCode::KEY_3:
        {
            if (leading_charactor.getTool() != nullptr) {
                delete leading_charactor.getTool();
            }
            std::string toolName = leading_charactor.MyBag.getItems()[2].name;
            Tool* changeTool;
            if (isFiveTool(toolName))
                changeTool = new Tool(toolName, leading_charactor.toolLevel());
            else
                changeTool = new Tool(toolName);
            leading_charactor.setTool(changeTool);
        }
        break;
        case EventKeyboard::KeyCode::KEY_4:
        {
            if (leading_charactor.getTool() != nullptr) {
                delete leading_charactor.getTool();
            }
            std::string toolName = leading_charactor.MyBag.getItems()[3].name;
            Tool* changeTool;
            if (isFiveTool(toolName))
                changeTool = new Tool(toolName, leading_charactor.toolLevel());
            else
                changeTool = new Tool(toolName);
            leading_charactor.setTool(changeTool);
        }
        break;
        case EventKeyboard::KeyCode::KEY_5:
        {
            if (leading_charactor.getTool() != nullptr) {
                delete leading_charactor.getTool();
            }
            std::string toolName = leading_charactor.MyBag.getItems()[4].name;
            Tool* changeTool;
            if (isFiveTool(toolName))
                changeTool = new Tool(toolName, leading_charactor.toolLevel());
            else
                changeTool = new Tool(toolName);
            leading_charactor.setTool(changeTool);
        }
        break;
        case EventKeyboard::KeyCode::KEY_6:
        {
            if (leading_charactor.getTool() != nullptr) {
                delete leading_charactor.getTool();
            }
            std::string toolName = leading_charactor.MyBag.getItems()[5].name;
            Tool* changeTool;
            if (isFiveTool(toolName))
                changeTool = new Tool(toolName, leading_charactor.toolLevel());
            else
                changeTool = new Tool(toolName);
            leading_charactor.setTool(changeTool);
        }
        break;
        case EventKeyboard::KeyCode::KEY_7:

        break;
    case EventKeyboard::KeyCode::KEY_8:

        break;
    case EventKeyboard::KeyCode::KEY_9:

        break;
    case EventKeyboard::KeyCode::KEY_EQUAL:

        break;
    case EventKeyboard::KeyCode::KEY_MINUS:

        break;
    default:
        break;
    }

    event->stopPropagation();
}


void PlayerControlLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            _moveLeft = false;
            _isRunning = false;
            // 取消调度任务
            Director::getInstance()->getScheduler()->unschedule("moveLeft", this);
            leading_charactor.PersonStop(-10, 0);
            control_changescene();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            _moveRight = false;
            _isRunning = false;
            // 取消调度任务
            Director::getInstance()->getScheduler()->unschedule("moveRight", this);
            leading_charactor.PersonStop(10, 0);
            control_changescene();
            break;
        case EventKeyboard::KeyCode::KEY_W:
            _moveUp = false;
            _isRunning = false;
            // 取消调度任务
            Director::getInstance()->getScheduler()->unschedule("moveUp", this);
            leading_charactor.PersonStop(0, 10);
            control_changescene();
            break;
        case EventKeyboard::KeyCode::KEY_S:
            _moveDown = false;
            _isRunning = false;
            // 取消调度任务
            Director::getInstance()->getScheduler()->unschedule("moveDown", this);
            leading_charactor.PersonStop(0, -10);
            control_changescene();
            break;
        case EventKeyboard::KeyCode::KEY_E:

            break;
        case EventKeyboard::KeyCode::KEY_0:

            break;
        case EventKeyboard::KeyCode::KEY_1:

            break;
        case EventKeyboard::KeyCode::KEY_2:

            break;
        case EventKeyboard::KeyCode::KEY_3:

            break;
        case EventKeyboard::KeyCode::KEY_4:

            break;
        case EventKeyboard::KeyCode::KEY_5:

            break;
        case EventKeyboard::KeyCode::KEY_6:

            break;
        case EventKeyboard::KeyCode::KEY_7:

            break;
        case EventKeyboard::KeyCode::KEY_8:

            break;
        case EventKeyboard::KeyCode::KEY_9:

            break;
        case EventKeyboard::KeyCode::KEY_EQUAL:

            break;
        case EventKeyboard::KeyCode::KEY_MINUS:

            break;
        default:
            break;

    }

    event->stopPropagation();
}


//鼠标监听器
void PlayerControlLayer::onMouseDown(Event* event)
{
    if (_player == nullptr) return;

    // 获取鼠标点击的位置
    EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
    if (mouseEvent)
    {
        Vec2 mousePos = Vec2(mouseEvent->getCursorX(), mouseEvent->getCursorY());

        // 获取主角当前位置
        Vec2 playerPos = _player->getWorldPosition();

        /*
        * 鼠标如果也想移动人物
        // 计算移动方向
        Vec2 moveDir = mousePos - playerPos;
        moveDir.normalize(); // 单位化方向向量

        // 更新主角的移动状态
        _moveLeft = moveDir.x < 0;
        _moveRight = moveDir.x > 0;
        _moveUp = moveDir.y > 0;
        _moveDown = moveDir.y < 0;
        */

        //鼠标点击之后调用函数
        control_mouseclick(mousePos);

        //manor_change_map();
    }
}

//帧更新，暂时未启用
void PlayerControlLayer::update(float dt) {
    float moveDistance = 1; // 每次移动的距离
    if (_player == nullptr) return;
    Vec2 playerPos = _player->getWorldPosition();
    Vec2 moveDir = Vec2::ZERO;
    if (_moveLeft) {
        moveDir.x -= 1.0f;
        _player->PersonMove(-moveDistance, 0);
    }
    if (_moveRight) {
        moveDir.x += 1.0f;
        _player->PersonMove(-moveDistance, 0);
    }
    if (_moveUp) {
        moveDir.y += 1.0f;
        _player->PersonMove(-moveDistance, 0);
    }
    if (_moveDown) {
        moveDir.y -= 1.0f;
        _player->PersonMove(-moveDistance, 0);
    }

    if (moveDir != Vec2::ZERO) {
        moveDir.normalize(); // 单位化方向向量
        playerPos += moveDir * _playerSpeed * dt;
        _player->_sprite->setPosition(playerPos);
    }
}

//人物移动
void PlayerControlLayer::movePlayer(float dt)
{
    if (_player == nullptr || !_isRunning) return;



    // 根据方向信息设置移动方向
    if (_currentDirection == "moveLeft")
    {
        _player->PersonMove(-MOVE_DISTANCE, 0);

    }
    else if (_currentDirection == "moveRight")
    {
        _player->PersonMove(MOVE_DISTANCE, 0);
    }
    else if (_currentDirection == "moveUp")
    {
        _player->PersonMove(0, MOVE_DISTANCE);
    }
    else if (_currentDirection == "moveDown")
    {
        _player->PersonMove(0, -MOVE_DISTANCE);
    }

}

void PlayerControlLayer::onExit()
{
    if (_keyboardListener != nullptr)
    {
        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr;
    }
    if (_mouseListener != nullptr)
    {
        _eventDispatcher->removeEventListener(_mouseListener);
        _mouseListener = nullptr;
    }
    Layer::onExit();
}


/* ---------- 地图管理层得到当前场景和地图 ----------*/
MapManager* MapManager::_instance = nullptr;

MapManager::MapManager() : _currentScene(nullptr)
{
    // 监听场景切换完成事件
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(Director::EVENT_AFTER_SET_NEXT_SCENE, CC_CALLBACK_1(MapManager::onSceneChange, this));
}

MapManager::~MapManager()
{
    // 移除事件监听
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(Director::EVENT_AFTER_SET_NEXT_SCENE);
}

MapManager* MapManager::getInstance()
{
    if (!_instance)
    {
        _instance = new MapManager();
    }
    return _instance;
}

void MapManager::registerSceneMap(Scene* scene, TMXTiledMap* map)
{
    _sceneMap[scene] = map;
}
//得到当前地图
TMXTiledMap* MapManager::getCurrentMap()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    auto children = currentScene->getChildren();
    TMXTiledMap* currentTiledMap;

    for (auto child : children) {
        currentTiledMap = dynamic_cast<TMXTiledMap*>(child);
        if (currentTiledMap) {
            CCLOG("Tile map found!");
            break;
        }
    }
    return currentTiledMap;
}

//得到当前场景
Scene* MapManager::getCurrentScene()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    return currentScene;
}

void MapManager::onSceneChange(EventCustom* event)
{
    // 更新当前场景
    _currentScene = Director::getInstance()->getRunningScene();
}

Size MapManager::getCurrentMapSize()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    auto children = currentScene->getChildren();
    TMXTiledMap* currentTiledMap;

    for (auto child : children) {
        currentTiledMap = dynamic_cast<TMXTiledMap*>(child);
        if (currentTiledMap) {
            CCLOG("Tile map found!");
            break;
        }
    }
    Size mapSize = currentTiledMap->getMapSize();
    return mapSize;
}

Size MapManager::getCurrentTileSize()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    auto children = currentScene->getChildren();
    TMXTiledMap* currentTiledMap;

    for (auto child : children) {
        currentTiledMap = dynamic_cast<TMXTiledMap*>(child);
        if (currentTiledMap) {
            CCLOG("Tile map found!");
            break;
        }
    }
    Size mapSize = currentTiledMap->getTileSize();
    return mapSize;
}

/*
   使用以下方法在别的cpp中找到当前场景下的地图
   TMXTiledMap* currentMap = MapManager::getInstance()->getCurrentMap();
    if (currentMap)
    {
        CCLOG("Current map name: %s", currentMap->getMapSize().width);
    }
    else
    {
        CCLOG("No map found for the current scene.");
    }

*/

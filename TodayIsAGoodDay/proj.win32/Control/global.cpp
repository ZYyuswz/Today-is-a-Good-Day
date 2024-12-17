#include "ui/CocosGUI.h"
#include"cocos2d.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"
#include "./Person/person.h"
#include"global.h"

USING_NS_CC;
//创建主人公
Person* leading_charactor = new Person();


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

    //this->scheduleUpdate();
    return true;
}

void PlayerControlLayer::setPlayer(Person* player) {
    _player = player;
}

void PlayerControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            _moveLeft = true;
            _player->PersonMove(-1, 0);
            break;
        case EventKeyboard::KeyCode::KEY_D:
            _moveRight = true;
            _player->PersonMove(-1, 0);
            break;
        case EventKeyboard::KeyCode::KEY_W:
            _moveUp = true;
            _player->PersonMove(-1, 0);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            _moveDown = true;
            _player->PersonMove(-1, 0);
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
            break;
        case EventKeyboard::KeyCode::KEY_D:
            _moveRight = false;
            break;
        case EventKeyboard::KeyCode::KEY_W:
            _moveUp = false;
            break;
        case EventKeyboard::KeyCode::KEY_S:
            _moveDown = false;
            break;
        default:
            break;
    }

    event->stopPropagation();
}

void PlayerControlLayer::update(float dt) {
    float moveDistance = 1; // 每次移动的距离
    if (_player == nullptr) return;
    Vec2 playerPos = _player->getPosition();
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
        _player->setPosition(playerPos);
    }
}


void PlayerControlLayer::onExit()
{
    if (_keyboardListener != nullptr)
    {
        _eventDispatcher->removeEventListener(_keyboardListener);
        _keyboardListener = nullptr;
    }
    Layer::onExit();
}



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

TMXTiledMap* MapManager::getCurrentMap()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    if (currentScene)
    {
        auto it = _sceneMap.find(currentScene);
        if (it != _sceneMap.end())
        {
            return it->second;
        }
    }
    return nullptr;
}

void MapManager::onSceneChange(EventCustom* event)
{
    // 更新当前场景
    _currentScene = Director::getInstance()->getRunningScene();
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
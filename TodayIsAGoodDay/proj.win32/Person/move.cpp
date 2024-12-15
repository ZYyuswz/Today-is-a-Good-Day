/* ----- 实现主人公移动功能 ----- */
/*详见开发者手册*/
#include "person.h"

const int ONE_CELL = 1.0f;

Vec2 Person::convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, TMXTiledMap* tileMap) {
    // 获取瓦片的大小
    cocos2d::Size tileSize = tileMap->getTileSize();

    // 获取瓦片地图的大小
    cocos2d::Size mapSize = tileMap->getMapSize();

    // 计算瓦片坐标
    int tileX = worldPosition.x / tileSize.width;
    int tileY = (mapSize.height - 1) - (worldPosition.y / tileSize.height);

    return cocos2d::Vec2(tileX, tileY);
}


bool Person::canMove(float deltaX, float deltaY, TMXTiledMap* currentMap)
{
    // 计算目标位置
    cocos2d::Vec2 currentPosition = this->getPosition();
    cocos2d::Vec2 targetPosition = currentPosition + cocos2d::Vec2(deltaX, deltaY);

    auto _wallLayer = currentMap->getLayer("Wall");
    auto _itemLayer = currentMap->getLayer("Item");

    // 将目标位置转换为瓦片坐标
    cocos2d::Vec2 tileCoord = convertWorldToTileCoord(targetPosition, currentMap);

    // 获取目标位置的瓦片 GID
    int wallGID = _wallLayer->getTileGIDAt(tileCoord);
    int itemGID = _itemLayer->getTileGIDAt(tileCoord);

    // 如果目标位置是 wall 或 item，则不能移动
    if (wallGID != 0 || itemGID != 0)
    {
        return false;
    }

    return true;
}

void Person::moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap)
{
   

    // 获取屏幕中心的世界坐标
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 screenCenter = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // 计算瓦片地图需要移动的距离
    cocos2d::Vec2 offset = screenCenter - playerPosition;

    // 移动瓦片地图
    tileMap->setPosition(tileMap->getPosition() + offset);
}

void Person::createAnimations()
{

    // 创建前走动画
    _frontWalkAnimation = cocos2d::Animation::create();
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_1.png");
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_2.png");
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_3.png");
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_4.png");
    _frontWalkAnimation->setDelayPerUnit(0.2f);
    _frontWalkAnimation->setLoops(-1);

    // 创建后走动画
    _backWalkAnimation = cocos2d::Animation::create();
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_1.png");
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_2.png");
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_3.png");
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_4.png");
    _backWalkAnimation->setDelayPerUnit(0.2f);
    _backWalkAnimation->setLoops(-1);

    // 创建左走动画
    _leftWalkAnimation = cocos2d::Animation::create();
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_1.png");
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_2.png");
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_3.png");
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_4.png");
    _leftWalkAnimation->setDelayPerUnit(0.2f);
    _leftWalkAnimation->setLoops(-1);

    // 创建右走动画
    _rightWalkAnimation = cocos2d::Animation::create();
    _rightWalkAnimation->addSpriteFrameWithFile("/person/person_right_1.png");
    _rightWalkAnimation->addSpriteFrameWithFile("/person/person_right_2.png");
    _rightWalkAnimation->addSpriteFrameWithFile("/person/person_right_3.png");
    _rightWalkAnimation->addSpriteFrameWithFile("/person/person_right_4.png");
    _rightWalkAnimation->setDelayPerUnit(0.2f);
    _rightWalkAnimation->setLoops(-1);
}

void Person::PersonMove(float deltaX, float deltaY)
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
    Size mapSize = currentTiledMap->getContentSize(); // 瓦片地图的大小
    Size visibleSize = Director::getInstance()->getVisibleSize(); // 屏幕的大小

    float minX = 0;
    float maxX = mapSize.width - visibleSize.width;
    float minY = 0;
    float maxY = mapSize.height - visibleSize.height;

    // 计算新的位置
    cocos2d::Vec2 newPosition = this->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    //判断是否可以移动
    if (!canMove(deltaX, deltaY,currentTiledMap))
        return;

    // 使用动作来平滑移动精灵
//    auto moveAction = cocos2d::MoveTo::create(0.1f, newPosition); // 0.1秒内移动到新位置

    // 根据移动方向切换动画
    if (deltaX > 0)
    {
        _sprite->runAction(cocos2d::Animate::create(_rightWalkAnimation));
    }
    else if (deltaX < 0)
    {
        _sprite->runAction(cocos2d::Animate::create(_leftWalkAnimation));
    }
    else if (deltaY > 0)
    {
        _sprite->runAction(cocos2d::Animate::create(_backWalkAnimation));
    }
    else if (deltaY < 0)
    {
        _sprite->runAction(cocos2d::Animate::create(_frontWalkAnimation));
    }
    moveTileMap(newPosition, currentTiledMap);

}

void Person::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    float moveDistance = ONE_CELL; // 每次移动的距离

    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        PersonMove(0, moveDistance); // 向上移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        PersonMove(-moveDistance, 0); // 向左移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        PersonMove(0, -moveDistance); // 向下移动
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        PersonMove(moveDistance, 0); // 向右移动
        break;
    default:
        break;
    }
}
void Person::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    
}
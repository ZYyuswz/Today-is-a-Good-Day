/* ----- 实现主人公移动功能 ----- */
/*详见开发者手册*/
#include "person.h"

extern Person leading_charactor;
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

Animation* Person::createAnimations(const std::string& direction)
{

    auto animation = Animation::create();
    // 创建一个数组，存储动画的每一帧
    Vector<SpriteFrame*> frames;

    // 加载4张图片并添加到帧数组中
    for (int i = 1; i <= 4; i++) {
        std::string frameName = "/person/person_" + direction + "_" + std::to_string(i) + ".png";
        animation->addSpriteFrameWithFile(frameName);

        /*
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame == nullptr) {
            // 如果缓存中没有，则从文件加载
            frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 96)); // 假设图片大小为64x64
        }
        frames.pushBack(frame);
        */
    }
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);

    // 创建动画对象
//    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f); // 每帧间隔0.1秒
    animation->setLoops(-1); // 设置为播放一次

    return animation;
   
}

void Person::createAnimations()
{
    _frontWalkAnimation = createAnimations("front");
    _backWalkAnimation = createAnimations("back");
    _leftWalkAnimation = createAnimations("left");
    _rightWalkAnimation = createAnimations("right");

    _frontWalkAnimate=Animate::create(_frontWalkAnimation);
    _backWalkAnimate= Animate::create(_backWalkAnimation);
    _leftWalkAnimate= Animate::create(_leftWalkAnimation);
    _rightWalkAnimate= Animate::create(_rightWalkAnimation);
}

void Person::PersonMove(float deltaX, float deltaY)
{
    static int i = 0;
    // 根据移动方向切换动画
    if (i++) {
        if (deltaX > 0)
        {
            _sprite->runAction(Sequence::create(_rightWalkAnimate->clone(), NULL));
        }
        else if (deltaX < 0)
        {
            _sprite->runAction(Sequence::create(_leftWalkAnimate->clone(), NULL));
        }
        else if (deltaY > 0)
        {
            _sprite->runAction(Sequence::create(_backWalkAnimate->clone(), NULL));
        }
        else if (deltaY < 0)
        {
            _sprite->runAction(Sequence::create(_frontWalkAnimate->clone(), NULL));
        }
    }
    else {
        if (deltaX > 0)
        {

            _sprite->runAction(Sequence::create(_rightWalkAnimate, NULL));
        }
        else if (deltaX < 0)
        {
            _sprite->runAction(Sequence::create(_leftWalkAnimate, _leftWalkAnimate,nullptr));
        }
        else if (deltaY > 0)
        {
            _sprite->runAction(Sequence::create(_backWalkAnimate, NULL));
        }
        else if (deltaY < 0)
        {
            _sprite->runAction(Sequence::create(_frontWalkAnimate, NULL));
        }
    }
   
    /*
    auto currentScene = Director::getInstance()->getRunningScene();
//    auto children = currentScene->getChildren();
    TMXTiledMap* currentTiledMap= currentScene->getChildByName< TMXTiledMap* >("spring");
    /*
    for (auto child : children) {
        currentTiledMap = dynamic_cast<TMXTiledMap*>(child);
        if (currentTiledMap) {
            CCLOG("Tile map found!");
            break;
        }
    }
    */
    /*
    Size mapSize = currentTiledMap->getContentSize(); // 瓦片地图的大小
    Size visibleSize = Director::getInstance()->getVisibleSize(); // 屏幕的大小

    float minX = 0;
    float maxX = mapSize.width - visibleSize.width;
    float minY = 0;
    float maxY = mapSize.height - visibleSize.height;
    */

    // 计算新的位置
    cocos2d::Vec2 newPosition = this->getPosition()+ cocos2d::Vec2(deltaX, deltaY);


    //判断是否可以移动
//    if (!canMove(deltaX, deltaY,currentTiledMap))
//        return;

    // 使用动作来平滑移动精灵
    auto moveAction = cocos2d::MoveBy::create(0.4f, newPosition); // 0.1秒内移动到新位置
    _sprite->runAction(moveAction);

   
    
    
//    moveTileMap(newPosition, currentTiledMap);

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
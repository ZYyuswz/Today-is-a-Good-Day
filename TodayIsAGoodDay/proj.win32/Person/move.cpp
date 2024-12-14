/* ----- 实现主人公移动功能 ----- */
/*详见开发者手册*/
#include "person.h"

const int ONE_CELL = 1.0f;
Size mapSize = getMap()->getContentSize(); // 瓦片地图的大小
Size visibleSize = Director::getInstance()->getVisibleSize(); // 屏幕的大小

class Move : public Person
{
private:
    cocos2d::Animation* _frontWalkAnimation;
    cocos2d::Animation* _backWalkAnimation;
    cocos2d::Animation* _leftWalkAnimation;
    cocos2d::Animation* _rightWalkAnimation;

    // 摄像头
    cocos2d::Camera* _camera;
public:
    //构造函数
    Move(const std::string& name, const int& sex, const std::string& farmName,
        int level, int HP, int energy, int money);

    // 创建动画
    void createAnimations();

    // 辅助方法：将世界坐标转换为瓦片坐标
    cocos2d::Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, TMXTiledMap* tileMap);

    // 辅助方法：将瓦片坐标转换为世界坐标
    cocos2d::Vec2 convertTileCoordToWorld(const cocos2d::Vec2& tileCoord, TMXTiledMap* tileMap);

    // 辅助方法：移动瓦片地图
    void moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // 辅助方法：移动人物
    void movePlayer(const cocos2d::Vec2& playerPosition);

    // 辅助方法：判断是否在边界之内
    bool isWithinBoundary(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // 移动函数
    void PersonMove(float deltaX, float deltaY);

    //判断是否可以移动
    bool canMove(float deltaX, float deltaY);

    // 键盘事件处理函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

Move::Move(const std::string& name, const int& sex, const std::string& farmName,
    int level, int HP, int energy, int money) : Person(name, sex, farmName)
{
    //初始化键盘监听器
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Move::onKeyPressed, this);

    // 获取默认摄像头
    _camera = cocos2d::Camera::getDefaultCamera();
}

bool Move::canMove(float deltaX, float deltaY)
{
    // 计算目标位置
    cocos2d::Vec2 currentPosition = this->getPosition();
    cocos2d::Vec2 targetPosition = currentPosition + cocos2d::Vec2(deltaX, deltaY);

    TMXTiledMap* currentMap = getMap();
    auto _wallLayer = currentMap->getLayer("Wall");
    auto _itemLayer = currentMap->getLayer("Item");

    // 将目标位置转换为瓦片坐标
    cocos2d::Vec2 tileCoord = _wallLayer ->getTileCoordinateAt(targetPosition);

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

void Move::moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap)
{

}

void Move::createAnimations()
{
    // 创建前走动画
    _frontWalkAnimation = cocos2d::Animation::create();
    _frontWalkAnimation->addSpriteFrameWithFile("person_front_walk.png");
    _frontWalkAnimation->addSpriteFrameWithFile("person_front_stand.png");
    _frontWalkAnimation->setDelayPerUnit(0.2f);
    _frontWalkAnimation->setLoops(-1);

    // 创建后走动画
    _backWalkAnimation = cocos2d::Animation::create();
    _backWalkAnimation->addSpriteFrameWithFile("person_back_walk.png");
    _backWalkAnimation->addSpriteFrameWithFile("person_back_stand.png");
    _backWalkAnimation->setDelayPerUnit(0.2f);
    _backWalkAnimation->setLoops(-1);

    // 创建左走动画
    _leftWalkAnimation = cocos2d::Animation::create();
    _leftWalkAnimation->addSpriteFrameWithFile("person_left_walk.png");
    _leftWalkAnimation->addSpriteFrameWithFile("person_left_stand.png");
    _leftWalkAnimation->setDelayPerUnit(0.2f);
    _leftWalkAnimation->setLoops(-1);

    // 创建右走动画
    _rightWalkAnimation = cocos2d::Animation::create();
    _rightWalkAnimation->addSpriteFrameWithFile("person_right_walk.png");
    _rightWalkAnimation->addSpriteFrameWithFile("person_right_stand.png");
    _rightWalkAnimation->setDelayPerUnit(0.2f);
    _rightWalkAnimation->setLoops(-1);
}

void Move::PersonMove(float deltaX, float deltaY)
{
    // 计算新的位置
    cocos2d::Vec2 newPosition = this->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    //判断是否可以移动
    if (!canMove(deltaX, deltaY))
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
    moveTileMap(newPosition, getMap());

}

void Move::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

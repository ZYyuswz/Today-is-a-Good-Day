/* ----- ʵ�����˹��ƶ����� ----- */
/*����������ֲ�*/
#include "person.h"

const int ONE_CELL = 1.0f;

Vec2 Person::convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, TMXTiledMap* tileMap) {
    // ��ȡ��Ƭ�Ĵ�С
    cocos2d::Size tileSize = tileMap->getTileSize();

    // ��ȡ��Ƭ��ͼ�Ĵ�С
    cocos2d::Size mapSize = tileMap->getMapSize();

    // ������Ƭ����
    int tileX = worldPosition.x / tileSize.width;
    int tileY = (mapSize.height - 1) - (worldPosition.y / tileSize.height);

    return cocos2d::Vec2(tileX, tileY);
}


bool Person::canMove(float deltaX, float deltaY, TMXTiledMap* currentMap)
{
    // ����Ŀ��λ��
    cocos2d::Vec2 currentPosition = this->getPosition();
    cocos2d::Vec2 targetPosition = currentPosition + cocos2d::Vec2(deltaX, deltaY);

    auto _wallLayer = currentMap->getLayer("Wall");
    auto _itemLayer = currentMap->getLayer("Item");

    // ��Ŀ��λ��ת��Ϊ��Ƭ����
    cocos2d::Vec2 tileCoord = convertWorldToTileCoord(targetPosition, currentMap);

    // ��ȡĿ��λ�õ���Ƭ GID
    int wallGID = _wallLayer->getTileGIDAt(tileCoord);
    int itemGID = _itemLayer->getTileGIDAt(tileCoord);

    // ���Ŀ��λ���� wall �� item�������ƶ�
    if (wallGID != 0 || itemGID != 0)
    {
        return false;
    }

    return true;
}

void Person::moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap)
{
   

    // ��ȡ��Ļ���ĵ���������
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 screenCenter = cocos2d::Vec2(visibleSize.width / 2, visibleSize.height / 2);

    // ������Ƭ��ͼ��Ҫ�ƶ��ľ���
    cocos2d::Vec2 offset = screenCenter - playerPosition;

    // �ƶ���Ƭ��ͼ
    tileMap->setPosition(tileMap->getPosition() + offset);
}

void Person::createAnimations()
{

    // ����ǰ�߶���
    _frontWalkAnimation = cocos2d::Animation::create();
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_1.png");
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_2.png");
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_3.png");
    _frontWalkAnimation->addSpriteFrameWithFile("/person/person_front_4.png");
    _frontWalkAnimation->setDelayPerUnit(0.2f);
    _frontWalkAnimation->setLoops(-1);

    // �������߶���
    _backWalkAnimation = cocos2d::Animation::create();
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_1.png");
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_2.png");
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_3.png");
    _backWalkAnimation->addSpriteFrameWithFile("/person/person_back_4.png");
    _backWalkAnimation->setDelayPerUnit(0.2f);
    _backWalkAnimation->setLoops(-1);

    // �������߶���
    _leftWalkAnimation = cocos2d::Animation::create();
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_1.png");
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_2.png");
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_3.png");
    _leftWalkAnimation->addSpriteFrameWithFile("/person/person_left_4.png");
    _leftWalkAnimation->setDelayPerUnit(0.2f);
    _leftWalkAnimation->setLoops(-1);

    // �������߶���
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
    Size mapSize = currentTiledMap->getContentSize(); // ��Ƭ��ͼ�Ĵ�С
    Size visibleSize = Director::getInstance()->getVisibleSize(); // ��Ļ�Ĵ�С

    float minX = 0;
    float maxX = mapSize.width - visibleSize.width;
    float minY = 0;
    float maxY = mapSize.height - visibleSize.height;

    // �����µ�λ��
    cocos2d::Vec2 newPosition = this->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    //�ж��Ƿ�����ƶ�
    if (!canMove(deltaX, deltaY,currentTiledMap))
        return;

    // ʹ�ö�����ƽ���ƶ�����
//    auto moveAction = cocos2d::MoveTo::create(0.1f, newPosition); // 0.1�����ƶ�����λ��

    // �����ƶ������л�����
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
    float moveDistance = ONE_CELL; // ÿ���ƶ��ľ���

    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        PersonMove(0, moveDistance); // �����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        PersonMove(-moveDistance, 0); // �����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        PersonMove(0, -moveDistance); // �����ƶ�
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        PersonMove(moveDistance, 0); // �����ƶ�
        break;
    default:
        break;
    }
}
void Person::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    
}
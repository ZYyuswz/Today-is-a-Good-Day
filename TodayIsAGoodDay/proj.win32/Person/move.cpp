/* ----- ʵ�����˹��ƶ����� ----- */
/*����������ֲ�*/
#include "person.h"

extern Person leading_charactor;
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

Animation* Person::createAnimations(const std::string& direction)
{

    auto animation = Animation::create();
    // ����һ�����飬�洢������ÿһ֡
    Vector<SpriteFrame*> frames;

    // ����4��ͼƬ����ӵ�֡������
    for (int i = 1; i <= 4; i++) {
        std::string frameName = "/person/person_" + direction + "_" + std::to_string(i) + ".png";
        animation->addSpriteFrameWithFile(frameName);

        /*
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame == nullptr) {
            // ���������û�У�����ļ�����
            frame = SpriteFrame::create(frameName, Rect(0, 0, 64, 96)); // ����ͼƬ��СΪ64x64
        }
        frames.pushBack(frame);
        */
    }
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);

    // ������������
//    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f); // ÿ֡���0.1��
    animation->setLoops(-1); // ����Ϊ����һ��

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
    // �����ƶ������л�����
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
    Size mapSize = currentTiledMap->getContentSize(); // ��Ƭ��ͼ�Ĵ�С
    Size visibleSize = Director::getInstance()->getVisibleSize(); // ��Ļ�Ĵ�С

    float minX = 0;
    float maxX = mapSize.width - visibleSize.width;
    float minY = 0;
    float maxY = mapSize.height - visibleSize.height;
    */

    // �����µ�λ��
    cocos2d::Vec2 newPosition = this->getPosition()+ cocos2d::Vec2(deltaX, deltaY);


    //�ж��Ƿ�����ƶ�
//    if (!canMove(deltaX, deltaY,currentTiledMap))
//        return;

    // ʹ�ö�����ƽ���ƶ�����
    auto moveAction = cocos2d::MoveBy::create(0.4f, newPosition); // 0.1�����ƶ�����λ��
    _sprite->runAction(moveAction);

   
    
    
//    moveTileMap(newPosition, currentTiledMap);

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
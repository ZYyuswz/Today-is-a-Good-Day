/* ----- ʵ�����˹��ƶ����� ----- */
/*����������ֲ�*/
#include "person.h"
#include "global.h"
#include "totaltools.h"
extern Person leading_charactor;

//������Ӧ���Ǻ궨��

const int ONE_CELL = 1.0f;
const float SCALE_WORLD_TO_TILE = 16 * 3.5;

//Ӧʹ�ú궨���滻���֣�����Ļ�ߴ��޷��ڱ���ʱ��ã����Ϊ0��
const float HALF_TILED_WIDTH = 1024.0f / SCALE_WORLD_TO_TILE;
const float HALF_TILED_HEIGHT = 576.0f / SCALE_WORLD_TO_TILE;

/*
Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition,const Vec2& Tiledposition) {
    Vec2 ScreenGap = worldPosition - Tiledposition;
    Vec2 TiledGap = ScreenGap / SCALE_WORLD_TO_TILE;
//    Vec2 TiledMiddle(32.0f, 32.0f);   
    return TiledGap;
}
*/

bool Person::canMove(float deltaX, float deltaY, TMXTiledMap* currentMap)
{
    // ����Ŀ��λ��
    cocos2d::Vec2 currentPosition = _sprite->getPosition();
    cocos2d::Vec2 targetPosition = currentPosition + cocos2d::Vec2(deltaX, deltaY);

    auto _floorLayer = currentMap->getLayer("floor");
    
    
    // ��Ŀ��λ��ת��Ϊ������Ƭ����
    cocos2d::Vec2 tileCoord = convertWorldToTileCoord(targetPosition, currentMap->getPosition());
    tileCoord.y = currentMap->getMapSize().height - tileCoord.y;
    int floorGID = _floorLayer->getTileGIDAt(tileCoord);  

    
    if (floorGID != 0)
    {
        return true;
    }
    return false;
}



void Person::moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap)
{
    // �ƶ���Ƭ��ͼ
    tileMap->setPosition(playerPosition);
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
        
    }
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);

    animation->setLoops(-1); // ����Ϊ����һ��

    return animation;
   
}

void Person::createAnimate()
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
    createAnimate();
    // �����ƶ������л�����
    
    if (deltaX > 0)
    {
        //            _sprite->stopAllActions();
        if (_sprite->getNumberOfRunningActions() == 0)
            _sprite->runAction(_rightWalkAnimate);
    }
    else if (deltaX < 0)
    {
        //            _sprite->stopAllActions();
        if (_sprite->getNumberOfRunningActions() == 0)
            _sprite->runAction(_leftWalkAnimate);
    }
    else if (deltaY > 0)
    {
        //            _sprite->stopAllActions();
        if (_sprite->getNumberOfRunningActions() == 0)
            _sprite->runAction(_backWalkAnimate);
    }
    else if (deltaY < 0)
    {
        //            _sprite->stopAllActions();
        if (_sprite->getNumberOfRunningActions() == 0)
            _sprite->runAction(_frontWalkAnimate);
    }
           
    auto currentScene = Director::getInstance()->getRunningScene();
    auto children = currentScene->getChildren();
    TMXTiledMap* currentMap;
    for (auto child : children) {
        currentMap = dynamic_cast<TMXTiledMap*>(child);
        if (currentMap) {
            CCLOG("Tile map found!");
            break;
        }
    }
 
    //û�ã�ֻ�ǵ���һ��
    Vec2 hello = convertWorldToTileCoord(_sprite->getPosition(), currentMap->getPosition());

    //�ж��Ƿ�����ƶ�
    if (!canMove(deltaX, deltaY,currentMap))
        return;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 screenRightUp = Vec2(visibleSize.width, visibleSize.height);
  
    Vec2 newPlayerPosition = _sprite->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    //������λ�õ���Ƭ����
    Vec2 PositionMiddle = convertWorldToTileCoord(newPlayerPosition, currentMap->getPosition());

    // �����µ���Ƭ��ͼ��λ��
    cocos2d::Vec2 newTiledPosition = currentMap->getPosition()- cocos2d::Vec2(deltaX, deltaY);
    
    Vec2 PositionLeftDown = PositionMiddle - Vec2(HALF_TILED_WIDTH, HALF_TILED_HEIGHT);//���½ǵ�����
    Vec2 PositionRightUp = PositionMiddle + Vec2(HALF_TILED_WIDTH, HALF_TILED_HEIGHT);//���Ͻǵ�����

    //���ˮƽ����ﵽ���ޣ���ֱ�����ƶ������ƶ�����ͷ
    if ((PositionLeftDown.x<0 && deltaY==0) || (PositionLeftDown.y<0 && deltaX==0) ||
        (PositionRightUp.x>64 && deltaY== 0 )||( PositionRightUp.y>64 && deltaX==0)) {
        // ʹ�ö�����ƽ���ƶ�����
        auto moveAction = cocos2d::MoveTo::create(0.2f, newPlayerPosition); // 0.1�����ƶ�����λ��
        _sprite->runAction(moveAction);
//        _sprite->setPosition(newPlayerPosition);
    }
    else {
        moveTileMap(newTiledPosition, currentMap);
    }

}


void Person::PersonStop(float deltaX, float deltaY)
{
    _sprite->stopAllActions();

    if (deltaX > 0)
    {
        _sprite->setTexture("/person/person_right_1.png");
    }
    else if (deltaX < 0)
    {
        _sprite->setTexture("/person/person_left_1.png");
    }
    else if (deltaY > 0)
    {
        _sprite->setTexture("/person/person_back_1.png");
    }
    else if (deltaY < 0)
    {
        _sprite->setTexture("/person/person_front_1.png");
    }
}



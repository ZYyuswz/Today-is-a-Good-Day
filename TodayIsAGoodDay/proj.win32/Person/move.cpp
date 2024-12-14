/* ----- ʵ�����˹��ƶ����� ----- */
/*����������ֲ�*/
#include "person.h"

const int ONE_CELL = 1.0f;
Size mapSize = getMap()->getContentSize(); // ��Ƭ��ͼ�Ĵ�С
Size visibleSize = Director::getInstance()->getVisibleSize(); // ��Ļ�Ĵ�С

class Move : public Person
{
private:
    cocos2d::Animation* _frontWalkAnimation;
    cocos2d::Animation* _backWalkAnimation;
    cocos2d::Animation* _leftWalkAnimation;
    cocos2d::Animation* _rightWalkAnimation;

    // ����ͷ
    cocos2d::Camera* _camera;
public:
    //���캯��
    Move(const std::string& name, const int& sex, const std::string& farmName,
        int level, int HP, int energy, int money);

    // ��������
    void createAnimations();

    // ��������������������ת��Ϊ��Ƭ����
    cocos2d::Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, TMXTiledMap* tileMap);

    // ��������������Ƭ����ת��Ϊ��������
    cocos2d::Vec2 convertTileCoordToWorld(const cocos2d::Vec2& tileCoord, TMXTiledMap* tileMap);

    // �����������ƶ���Ƭ��ͼ
    void moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // �����������ƶ�����
    void movePlayer(const cocos2d::Vec2& playerPosition);

    // �����������ж��Ƿ��ڱ߽�֮��
    bool isWithinBoundary(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // �ƶ�����
    void PersonMove(float deltaX, float deltaY);

    //�ж��Ƿ�����ƶ�
    bool canMove(float deltaX, float deltaY);

    // �����¼�������
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
};

Move::Move(const std::string& name, const int& sex, const std::string& farmName,
    int level, int HP, int energy, int money) : Person(name, sex, farmName)
{
    //��ʼ�����̼�����
    _keyboardListener->onKeyPressed = CC_CALLBACK_2(Move::onKeyPressed, this);

    // ��ȡĬ������ͷ
    _camera = cocos2d::Camera::getDefaultCamera();
}

bool Move::canMove(float deltaX, float deltaY)
{
    // ����Ŀ��λ��
    cocos2d::Vec2 currentPosition = this->getPosition();
    cocos2d::Vec2 targetPosition = currentPosition + cocos2d::Vec2(deltaX, deltaY);

    TMXTiledMap* currentMap = getMap();
    auto _wallLayer = currentMap->getLayer("Wall");
    auto _itemLayer = currentMap->getLayer("Item");

    // ��Ŀ��λ��ת��Ϊ��Ƭ����
    cocos2d::Vec2 tileCoord = _wallLayer ->getTileCoordinateAt(targetPosition);

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

void Move::moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap)
{

}

void Move::createAnimations()
{
    // ����ǰ�߶���
    _frontWalkAnimation = cocos2d::Animation::create();
    _frontWalkAnimation->addSpriteFrameWithFile("person_front_walk.png");
    _frontWalkAnimation->addSpriteFrameWithFile("person_front_stand.png");
    _frontWalkAnimation->setDelayPerUnit(0.2f);
    _frontWalkAnimation->setLoops(-1);

    // �������߶���
    _backWalkAnimation = cocos2d::Animation::create();
    _backWalkAnimation->addSpriteFrameWithFile("person_back_walk.png");
    _backWalkAnimation->addSpriteFrameWithFile("person_back_stand.png");
    _backWalkAnimation->setDelayPerUnit(0.2f);
    _backWalkAnimation->setLoops(-1);

    // �������߶���
    _leftWalkAnimation = cocos2d::Animation::create();
    _leftWalkAnimation->addSpriteFrameWithFile("person_left_walk.png");
    _leftWalkAnimation->addSpriteFrameWithFile("person_left_stand.png");
    _leftWalkAnimation->setDelayPerUnit(0.2f);
    _leftWalkAnimation->setLoops(-1);

    // �������߶���
    _rightWalkAnimation = cocos2d::Animation::create();
    _rightWalkAnimation->addSpriteFrameWithFile("person_right_walk.png");
    _rightWalkAnimation->addSpriteFrameWithFile("person_right_stand.png");
    _rightWalkAnimation->setDelayPerUnit(0.2f);
    _rightWalkAnimation->setLoops(-1);
}

void Move::PersonMove(float deltaX, float deltaY)
{
    // �����µ�λ��
    cocos2d::Vec2 newPosition = this->getPosition() + cocos2d::Vec2(deltaX, deltaY);

    //�ж��Ƿ�����ƶ�
    if (!canMove(deltaX, deltaY))
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
    moveTileMap(newPosition, getMap());

}

void Move::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
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

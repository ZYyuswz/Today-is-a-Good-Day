#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*��һ�����Ǻ궨�壬Ϊ����궨���ͻ������Ӧ�û�Ҫ�ϲ���һ��ͳһ��ͷ�ļ�*/
const int MAN = 1;
const int WOMAN = 0;

const int MIN_OF_ENERGY = 0;
const int INIT_MONEY = 100;
const int INIT_PX = 0;
const int INIT_PY = 0;


class Person : public cocos2d::Node
{
protected:
    std::string _name;
    std::string _farmName;
    int _sex;                                                    //����Ա�
    int _level;
    int _energy;
    int _HP;                                                // �������ֵ
    int _money;
    int experience_all;

    cocos2d::Sprite* _sprite;   //���ﾫ��

    //�ƶ�����
    cocos2d::Animation* _frontWalkAnimation;
    cocos2d::Animation* _backWalkAnimation;
    cocos2d::Animation* _leftWalkAnimation;
    cocos2d::Animation* _rightWalkAnimation;

    cocos2d::Animate* _frontWalkAnimate;
    cocos2d::Animate* _backWalkAnimate;
    cocos2d::Animate* _leftWalkAnimate;
    cocos2d::Animate* _rightWalkAnimate;

    cocos2d::EventListenerKeyboard* _keyboardListener;  //���̼�����

public:
    // ���캯��
    Person();
    //   ~Person() { _sprite->setPosition(200, 200); }
       // ��ʼ������
    virtual bool init();

    // ��ȡ����������
    std::string getname() const { return _name; }
    void setName(const std::string& name) { _name = name; }

    std::string getFarmName() const { return _farmName; }
    void setFarmName(const std::string& farmName) { _farmName = farmName; }

    int getSex() const { return _sex; }
    void setSex(const int& sex) { _sex = sex; }

    int getLevel() const { return _level; }
    void setLevel(int level) { _level = level; }

    int getEnergy() const { return _energy; }
    void setEnergy(const int& energy) { _energy = energy; }

    int getHP() const { return _HP; }
    void setHP(int HP) { _HP = HP; }

    Sprite* getSprite()const { return _sprite; }

    //��Ѫ
    void Person::decreaseHP(const int attack);

    //�ж���û��
    bool isDead() { return _HP <= 0; }

    //���ˣ���ʬ����д���
    void dead();

    void levelUP();

    /*����Ϊmove������غ���*/
    // ��������
    Animation* createAnimations(const std::string& direction);
    void createAnimate();

    // ��������������������ת��Ϊ��Ƭ����
//    cocos2d::Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, TMXTiledMap* tileMap);

    // ��������������Ƭ����ת��Ϊ��������
 //   cocos2d::Vec2 convertTileCoordToWorld(const cocos2d::Vec2& tileCoord, TMXTiledMap* tileMap);

    // �����������ƶ���Ƭ��ͼ
    void moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // �����������ƶ�����
    void movePlayer(const cocos2d::Vec2& playerPosition);

    // �����������ж��Ƿ��ڱ߽�֮��
    bool isWithinBoundary(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // �ƶ�����
    void PersonMove(float deltaX, float deltaY);
    void PersonStop(float deltaX, float deltaY);

    //�ж��Ƿ�����ƶ�
    bool canMove(float deltaX, float deltaY, TMXTiledMap* currentMap);

    //��ʼ��
    void person_construction(const std::string& name, const int& sex, const std::string& farmName, Scene* currentScene,
        int level = 0, int HP = 0, int energy = 0, int money = 0);

    Vec2 getTiledPosition();

};

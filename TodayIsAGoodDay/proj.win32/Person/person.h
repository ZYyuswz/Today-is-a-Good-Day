#pragma once
#include "cocos2d.h"
#include "Map/drop.h"
#include <map>
#include <string>
#include "person/tool.h"

USING_NS_CC;

/*��һ�����Ǻ궨�壬Ϊ����궨���ͻ������Ӧ�û�Ҫ�ϲ���һ��ͳһ��ͷ�ļ�*/
const int MAN = 1;
const int WOMAN = 0;

const int MIN_OF_ENERGY = 0;
const int INIT_MONEY = 100;
const int INIT_PX = 0;
const int INIT_PY = 0;

const int AXE = 100;//��ͷ��������
const int HAMMER = 101;//��ͷ����ʯͷ
const int DRAFT = 102; //��ͷ��������
const int KETTLE = 103;//ˮ��������
const int FISHING_POLE = 104;//�����



struct item
{
    std::string name;
    int num;
    int value; //tools��valueΪ0
    bool isTool;
    item(const std::string itemName,const int itemNum = 1) 
        :name(itemName),value(itemPrices.find(itemName)->second),num(itemNum) {}
};


class Bag : public Node
{
public:
    // ���캯��
    Bag();

    //����������E�򿪱���
    void changeBag();

    // ��ӹ��߻����
    void addItem(const item& MyItem); 

    // �Ƴ����߻����
    void removeItem(const item& MyItem);

    // ��ʾ��������
    void displayBag();

    //�رձ���
    void closeBag();

    // ������Ʒ��Ϣ
    void updateItemInfo(cocos2d::Vec2 position);

    std::vector<item> getItems() { return _items; };
private:
    //��Ʒ�б�
    std::vector<item> _items;

    //��Ʒ�����б�
    std::vector<cocos2d::Sprite*> _itemSprites;

    //��Ʒ��ǩ��ֻ��һ������������ƶ���ʾ
    cocos2d::Label* _itemInfoLabel;
    int _selectedItemIndex;

    bool isOpen;

    cocos2d::EventListenerKeyboard* _keyboardListener;  //���̼�����
};


class Person// : public cocos2d::Node
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
    

    //�ƶ�����
    cocos2d::Animation* _frontWalkAnimation;
    cocos2d::Animation* _backWalkAnimation;
    cocos2d::Animation* _leftWalkAnimation;
    cocos2d::Animation* _rightWalkAnimation;

    cocos2d::Animate* _frontWalkAnimate;
    cocos2d::Animate* _backWalkAnimate;
    cocos2d::Animate* _leftWalkAnimate;
    cocos2d::Animate* _rightWalkAnimate;

    Tool* currentTool;

public: 
    friend Tool;
    friend Bag;
    Sprite* _sprite;   //���ﾫ��
    Bag MyBag;

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

    void setTool(Tool* newTool) { currentTool = newTool; }
    Tool* getTool() { return currentTool; }
    Sprite* getSprite()const { return _sprite; }

    int toolLevel() { return _level > 50 ? 2 : 1; }
    //��Ѫ
    void Person::decreaseHP(const int attack);

    //�ж���û��
    bool isDead() { return _HP <= 0; }

    //���ˣ���ʬ����д���
    void dead();

    void levelUP();

    void moneyUP(int deltaMoney);

    /*����Ϊmove������غ���*/
    // ��������
    Animation* createAnimations(const std::string& direction);
    void createAnimate();

    void collectItems();

    void Person::useTools();
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
    Vec2 getWorldPosition();
};


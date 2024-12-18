#pragma once
#include "cocos2d.h"

USING_NS_CC;

/*这一部分是宏定义，为避免宏定义冲突，后期应该还要合并到一个统一的头文件*/
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
    int _sex;                                                    //玩家性别
    int _level;
    int _energy;
    int _HP;                                                // 玩家生命值
    int _money;
    int experience_all;

    cocos2d::Sprite* _sprite;   //人物精灵

    //移动动画
    cocos2d::Animation* _frontWalkAnimation;
    cocos2d::Animation* _backWalkAnimation;
    cocos2d::Animation* _leftWalkAnimation;
    cocos2d::Animation* _rightWalkAnimation;

    cocos2d::Animate* _frontWalkAnimate;
    cocos2d::Animate* _backWalkAnimate;
    cocos2d::Animate* _leftWalkAnimate;
    cocos2d::Animate* _rightWalkAnimate;

    cocos2d::EventListenerKeyboard* _keyboardListener;  //键盘监听器

public:
    // 构造函数
    Person();
    //   ~Person() { _sprite->setPosition(200, 200); }
       // 初始化函数
    virtual bool init();

    // 获取和设置属性
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

    //扣血
    void Person::decreaseHP(const int attack);

    //判断死没死
    bool isDead() { return _HP <= 0; }

    //死了，对尸体进行处理
    void dead();

    void levelUP();

    /*以下为move功能相关函数*/
    // 创建动画
    Animation* createAnimations(const std::string& direction);
    void createAnimate();

    // 辅助方法：将世界坐标转换为瓦片坐标
//    cocos2d::Vec2 convertWorldToTileCoord(const cocos2d::Vec2& worldPosition, TMXTiledMap* tileMap);

    // 辅助方法：将瓦片坐标转换为世界坐标
 //   cocos2d::Vec2 convertTileCoordToWorld(const cocos2d::Vec2& tileCoord, TMXTiledMap* tileMap);

    // 辅助方法：移动瓦片地图
    void moveTileMap(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // 辅助方法：移动人物
    void movePlayer(const cocos2d::Vec2& playerPosition);

    // 辅助方法：判断是否在边界之内
    bool isWithinBoundary(const cocos2d::Vec2& playerPosition, TMXTiledMap* tileMap);

    // 移动函数
    void PersonMove(float deltaX, float deltaY);
    void PersonStop(float deltaX, float deltaY);

    //判断是否可以移动
    bool canMove(float deltaX, float deltaY, TMXTiledMap* currentMap);

    //初始化
    void person_construction(const std::string& name, const int& sex, const std::string& farmName, Scene* currentScene,
        int level = 0, int HP = 0, int energy = 0, int money = 0);

    Vec2 getTiledPosition();

};

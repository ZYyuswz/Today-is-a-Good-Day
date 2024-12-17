#pragma once


#include "cocos2d.h"


bool first_to_manor();    //初始进入主场景
bool manor_to_towm();     //从庄园去小镇


/*--------------------沙滩场景--------------------*/

// 沙滩场景调用
class beach : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
   

    // implement the "static create()" method manually
    CREATE_FUNC(beach);
};


/*--------------------庄园场景--------------------*/

//庄园春天场景调用
class spring_manor :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(spring_manor);
};

/*--------------------小镇场景--------------------*/

//小镇春天场景
class  spring_town:public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(spring_town);
};
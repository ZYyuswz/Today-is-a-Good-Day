﻿
﻿#pragma once


#include "cocos2d.h"


bool first_to_manor();    //初始进入主场景
bool manor_to_towm();     //从庄园去小镇
bool change_to_mine();    //进入矿洞
//切换到沙滩场景
bool change_to_beach();

//切换到家的场景
bool change_to_home();

/* 返回场景调用 */
// 小镇返回庄园
bool back_to_manor_from_town();

//强制返回庄园
void force_back_to_manor();

void test();


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

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
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

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
};

/*--------------------小镇场景--------------------*/

//小镇春天场景
class  spring_town :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(spring_town);

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;


};


//小镇秋天场景
class autumn_town :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(autumn_town);

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
};

//小镇冬天场景
class winter_town :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(winter_town);

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
};


/* ---------- 矿洞场景 ---------- */
class scene_mine :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(scene_mine);

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
};


/* ---------- 家庭场景 ---------- */
class scene_home :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(scene_home);

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
};

/* ---------- 商店场景 ---------- */
class scene_store :public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(scene_store);

    // 重写 onEnter 方法
    virtual void onEnter() override;

    // 重写 onExit 方法
    virtual void onExit() override;
};

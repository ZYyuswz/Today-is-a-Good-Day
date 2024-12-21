#pragma once


#include "cocos2d.h"

class menu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void onCreate(cocos2d::Ref* sender);   //创建选项回调
    void onLoad(cocos2d::Ref* sender);   //存档选项回调
    void onCoop(cocos2d::Ref* sender);    //合作选项回调
    void onEixt(cocos2d::Ref* sender);    //退出选项回调


     

    // implement the "static create()" method manually
    CREATE_FUNC(menu);
};




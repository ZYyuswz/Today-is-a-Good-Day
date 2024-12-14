#pragma once


#include "cocos2d.h"


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

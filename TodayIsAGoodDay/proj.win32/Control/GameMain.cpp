/*  -----作为游戏实现总调度函数----- */

#include<iostream>

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"menu.h"


//本游戏总控函数
using namespace cocos2d;
int gamemain()
{
    // create a scene. it's an autorelease object
    auto scene = menu::createScene();
    auto director = Director::getInstance();
    //运行第一幕场景，即欢迎页面
    // run
    director->runWithScene(scene);


	return 0;
}
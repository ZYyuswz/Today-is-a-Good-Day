/*  -----作为游戏实现总调度函数----- */

#include<iostream>

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"menu.h"
using namespace cocos2d;
int gamemain()
{
    // create a scene. it's an autorelease object
    auto scene = menu::createScene();
    auto director = Director::getInstance();

    // run
    director->runWithScene(scene);
	return 0;
}
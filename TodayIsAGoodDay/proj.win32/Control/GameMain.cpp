/*  -----作为游戏实现总调度函数----- */

#include<iostream>

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include"menu.h"
#include "Time.h"
#include "Setting/setting.h"
using namespace cocos2d;

//本游戏启动函数
//加载纹理图集
//启动BGM
//进入初始场景

int gamemain()
{
    // create a scene. it's an autorelease object
    auto scene = menu::createScene();
    auto director = Director::getInstance();
    // 加载纹理图集（只需要加载一次）
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile("Tree/tree.plist");
    spriteFrameCache->addSpriteFramesWithFile("Stone/stone.plist");
    spriteFrameCache->addSpriteFramesWithFile("Plough/plough.plist");
    spriteFrameCache->addSpriteFramesWithFile("Crops/crops.plist");
    spriteFrameCache->addSpriteFramesWithFile("Drops/drops_1.plist"); 

  
    
    play_BGM();
    //运行第一幕场景，即欢迎页面
    // run
    director->runWithScene(scene);


	return 0;
}
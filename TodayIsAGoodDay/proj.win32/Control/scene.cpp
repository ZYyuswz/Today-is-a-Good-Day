﻿// 本cpp用于切换场景调用


#include "SimpleAudioEngine.h"

#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"

//切换场景调用函数
bool change_to_beach()
{
    

    return false;
}




//沙滩场景初始化
Scene* beach::createScene()
{
    //创建场景
    auto beachscene = Scene::create();
    //添加层
    auto layer = beach::create();
    beachscene->addChild(layer);

    return beachscene;
}

bool beach::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_beach = TMXTiledMap::create("map/beach.tmx"); // 替换为你的 .tmx 文件名

    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
       //设置图缩放比例
        scene_beach->setScale(BEACH_SMALL_SCALE);
        
        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(BEACH_ENTER_X, BEACH_ENTER_Y);
        // 获取地图的尺寸  
        Size mapSize = scene_beach->getMapSize();
        Size tileSize = scene_beach->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_beach->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = (screensize.width / 2) - screen_enterence.x;
        point_row.y = (screensize.height) - screen_enterence.y;

        scene_beach->setAnchorPoint(Vec2(0, 0));
        scene_beach->setPosition(point_row);


    }
    

    this->addChild(scene_beach);
    return true;
}
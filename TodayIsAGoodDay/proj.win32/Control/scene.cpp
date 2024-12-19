﻿// 本cpp用于切换场景调用


#include "SimpleAudioEngine.h"

#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"
#include "global.h"
#include "time.h"

#include "Map/stone.h"

//切换场景调用函数
bool first_to_manor() {
    auto spring_scene = spring_manor::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, spring_scene));
    leading_charactor.person_construction("zy", 1, "zyh", spring_scene);
    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    spring_scene->addChild(playerControlLayer);
    // GameTime* gametime = GameTime::getInstance();
    //if(gametime->getWeather()==Weather::Rainy)spring_scene->addChild(RainLayer(),RAINLAYER); //下雨场景实现示例
    return true;
}

bool manor_to_towm()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    /* 移除人物 */
    //people_remove_change();
    /*end*/

    Season season = GameTime::getInstance()->getSeason();
    if (season == Season::Spring || season == Season::Summer)
    {
        auto town_scene = spring_town::createScene();

        CCLOG("before");
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        //Director::getInstance()->replaceScene(town_scene);
        Director::getInstance()->pushScene(town_scene);
        
        CCLOG("after");
       
        auto now= Director::getInstance()->getRunningScene();
        /*
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        auto playerControlLayer = PlayerControlLayer::create();
        playerControlLayer->setPlayer(&leading_charactor);

        town_scene->addChild(playerControlLayer);
        Size mapsize = MapManager::getInstance()->getCurrentMapSize();
        Size tilesize = MapManager::getInstance()->getCurrentTileSize();

        Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);
        //加入人物在场景里
        people_change_scene(pos_player);
        auto playerControlLayer = PlayerControlLayer::create();
        playerControlLayer->setPlayer(&leading_charactor);
        town_scene->addChild(playerControlLayer);
        */
      
        

        return true;
    }
    else if (season == Season::Winter)
    {
        auto town_scene = winter_town::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        auto playerControlLayer = PlayerControlLayer::create();
        playerControlLayer->setPlayer(&leading_charactor);
        town_scene->addChild(playerControlLayer);
        Size mapsize = MapManager::getInstance()->getCurrentMapSize();
        Size tilesize = MapManager::getInstance()->getCurrentTileSize();

        Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

        //加入人物在场景里
        //leading_charactor.person_scene_construction();
        //leading_charactor._sprite->setPosition(pos_player);
        return true;
    }
    else if (season == Season::Autumn)
    {
        auto town_scene = autumn_town::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        auto playerControlLayer = PlayerControlLayer::create();
        playerControlLayer->setPlayer(&leading_charactor);

        town_scene->addChild(playerControlLayer);
        Size mapsize = MapManager::getInstance()->getCurrentMapSize();
        Size tilesize = MapManager::getInstance()->getCurrentTileSize();

        Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

        //加入人物在场景里
        //leading_charactor.person_scene_construction();
        //leading_charactor._sprite->setPosition(pos_player);
        return true;
    }
    return false;
}
/*test*/
void test()
{
    auto now = Director::getInstance()->getRunningScene();
}
bool change_to_beach()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    Director::getInstance()->pushScene(currentScene);
    auto beach_scene = beach::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, beach_scene));
    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    beach_scene->addChild(playerControlLayer);
    Size mapsize = MapManager::getInstance()->getCurrentMapSize();
    Size tilesize = MapManager::getInstance()->getCurrentTileSize();

    Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

    //加入人物在场景里
    //leading_charactor.person_scene_construction();
    //leading_charactor._sprite->setPosition(pos_player);
    return true;

}

bool change_to_mine()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    Director::getInstance()->pushScene(currentScene);
    auto mine_scene = scene_mine::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mine_scene));
    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    mine_scene->addChild(playerControlLayer);
    Size mapsize = MapManager::getInstance()->getCurrentMapSize();
    Size tilesize = MapManager::getInstance()->getCurrentTileSize();

    Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

    //加入人物在场景里
    //leading_charactor.person_scene_construction();
    //leading_charactor._sprite->setPosition(pos_player);

    return true;
}

//切换到家的场景
bool change_to_home()
{

    return true;
}

//切换到商店场景
bool change_to_store()
{

    return true;
}



/*--------------------沙滩场景--------------------*/
//沙滩场景初始化
Scene* beach::createScene()
{
    /*
    //创建场景
    auto beachscene = Scene::create();
    //添加层
    auto layer = beach::create();
    beachscene->addChild(layer);

    return beachscene;
    */
    return beach::create();
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
    
    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    scene_beach->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    scene_beach->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    scene_beach->addChild(dropLayer);


    this->addChild(scene_beach);
    return true;
}

/*--------------------庄园场景--------------------*/

//庄园春天场景
//庄园春天初始化

Scene* spring_manor::createScene()
{
    return spring_manor::create();

    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_manor::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */

}

bool spring_manor::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_spring = TMXTiledMap::create("manor/spring.tmx"); // 替换为你的 .tmx 文件名

    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        scene_spring->setScale(SRING_MANOR_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y);
        // 获取地图的尺寸  
        Size mapSize = scene_spring->getMapSize();
        Size tileSize = scene_spring->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_spring->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = (screensize.width / 2) - screen_enterence.x;
        point_row.y = (screensize.height / 2) - screen_enterence.y;

        scene_spring->setAnchorPoint(Vec2(0, 0));
        scene_spring->setPosition(point_row);


    }

    //将地图和场景关联
    //MapManager::getInstance()->registerSceneMap(this, scene_spring);

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    scene_spring->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    scene_spring->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    scene_spring->addChild(dropLayer);

    this->addChild(scene_spring);


    return true;
}

/*--------------------小镇场景--------------------*/

//春天场景
Scene* spring_town::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */
    return spring_town::create();
}

bool spring_town::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_spring = TMXTiledMap::create("map/town_spring.tmx"); // 替换为你的 .tmx 文件名



    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        scene_spring->setScale(TOWN_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y);
        // 获取地图的尺寸  
        Size mapSize = scene_spring->getMapSize();
        Size tileSize = scene_spring->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_spring->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = screen_enterence.x;
        point_row.y = (screensize.height / 2) - screen_enterence.y;

        scene_spring->setAnchorPoint(Vec2(0, 0));
        scene_spring->setPosition(point_row);


    }

    //将地图和场景关联
    //MapManager::getInstance()->registerSceneMap(this, scene_spring);

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    scene_spring->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    scene_spring->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    scene_spring->addChild(dropLayer);


    this->addChild(scene_spring);


    return true;
}

//秋天场景
Scene* autumn_town::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */
    return autumn_town::create();
}

bool autumn_town::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_spring = TMXTiledMap::create("map/town_autumn.tmx"); // 替换为你的 .tmx 文件名



    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        scene_spring->setScale(TOWN_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y);
        // 获取地图的尺寸  
        Size mapSize = scene_spring->getMapSize();
        Size tileSize = scene_spring->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_spring->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = screen_enterence.x;
        point_row.y = (screensize.height / 2) - screen_enterence.y;

        scene_spring->setAnchorPoint(Vec2(0, 0));
        scene_spring->setPosition(point_row);


    }

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    scene_spring->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    scene_spring->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    scene_spring->addChild(dropLayer);


    this->addChild(scene_spring);


    return true;
}

//冬天场景
Scene* winter_town::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */
    return winter_town::create();
}

bool winter_town::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_winter = TMXTiledMap::create("map/town_winter.tmx"); // 替换为你的 .tmx 文件名



    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        scene_winter->setScale(TOWN_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y);
        // 获取地图的尺寸  
        Size mapSize = scene_winter->getMapSize();
        Size tileSize = scene_winter->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_winter->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = screen_enterence.x;
        point_row.y = (screensize.height / 2) - screen_enterence.y;

        scene_winter->setAnchorPoint(Vec2(0, 0));
        scene_winter->setPosition(point_row);


    }

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    scene_winter->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    scene_winter->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    scene_winter->addChild(dropLayer);


    this->addChild(scene_winter);


    return true;
}

/* ---------- 矿洞场景 ---------- */
Scene* scene_mine::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */
    return scene_mine::create();
}

bool scene_mine::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto mine = TMXTiledMap::create("map/mine.tmx"); // 替换为你的 .tmx 文件名



    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        mine->setScale(MINE_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(MANOR_TO_MINE_X, MANOR_TO_MINE_Y);
        // 获取地图的尺寸  
        Size mapSize = mine->getMapSize();
        Size tileSize = mine->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, mine->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = screen_enterence.x;
        point_row.y = screen_enterence.y;

        mine->setAnchorPoint(Vec2(0, 0));
        mine->setPosition(point_row);


    }

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    mine->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    mine->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    mine->addChild(dropLayer);


    this->addChild(mine);

    Stone::randomGenerateInMine(mine, objectLayer);

    return true;
}

//家的场景
Scene* scene_home::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */
    return scene_home::create();
}

bool scene_home::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto home = TMXTiledMap::create("map/house.tmx"); // 替换为你的 .tmx 文件名



    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        home->setScale(HOME_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(MANOR_TO_HOME_X, MANOR_TO_HOME_Y);
        // 获取地图的尺寸  
        Size mapSize = home->getMapSize();
        Size tileSize = home->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, home->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = screen_enterence.x;
        point_row.y = screen_enterence.y;

        home->setAnchorPoint(Vec2(0, 0));
        home->setPosition(point_row);


    }

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    home->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    home->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    home->addChild(dropLayer);



    this->addChild(home);

    return true;
}
//商店场景
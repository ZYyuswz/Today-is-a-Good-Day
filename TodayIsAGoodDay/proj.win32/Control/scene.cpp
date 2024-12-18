// 本cpp用于切换场景调用


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

//切换场景调用函数
//初始进入主场景
bool first_to_manor()
{
    auto spring_scene = spring_manor::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, spring_scene));
    leading_charactor.person_construction("zy", 1, "zyh", spring_scene);
    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    spring_scene->addChild(playerControlLayer);

    return true;
}

bool manor_to_towm()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    Director::getInstance()->pushScene(currentScene);
    Season season = GameTime::getInstance()->getSeason();
    if (season == Season::Spring)
    {
        auto town_scene = spring_town::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        auto playerControlLayer = PlayerControlLayer::create();
        playerControlLayer->setPlayer(&leading_charactor);
        town_scene->addChild(playerControlLayer);

        return true;
    }
    return false;
}

bool change_to_beach()
{
    

    return false;
}



/*--------------------沙滩场景--------------------*/
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

/*--------------------庄园场景--------------------*/

//庄园春天场景
//庄园春天初始化
Scene* spring_manor::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_manor::create();
    scene_spring->addChild(layer);
    */
    return spring_manor::create();
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
    MapManager::getInstance()->registerSceneMap(this, scene_spring);

    this->addChild(scene_spring);


    return true;
}

/*--------------------小镇场景--------------------*/

//春天场景
Scene* spring_town::createScene()
{
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
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
    MapManager::getInstance()->registerSceneMap(this, scene_spring);

    this->addChild(scene_spring);


    return true;
}
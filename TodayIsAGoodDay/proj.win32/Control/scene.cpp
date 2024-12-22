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

#include "Map/stone.h"

//切换场景调用函数
bool first_to_manor() {
    auto spring_scene = spring_manor::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, spring_scene));
    //leading_charactor.person_construction("zy", 1, "zyh", spring_scene);

    // GameTime* gametime = GameTime::getInstance();
    //if(gametime->getWeather()==Weather::Rainy)spring_scene->addChild(RainLayer(),RAINLAYER); //下雨场景实现示例
      // 启动自动更新
    GameTime::getInstance()->startAutoUpdate();

    return true;
}

/* ---------- 进入调用 ---------- */

bool manor_to_towm()
{
    auto currentScene = Director::getInstance()->getRunningScene();
    /* 移除人物 */
    //people_remove_change();
    /*end*/

    Season season = GameTime::getInstance()->getSeason();
    if (season == Season::Spring || season == Season::Summer)
    {
        if (season == Season::Spring)
        {
            int current_day = GameTime::getInstance()->getDay();
            if (current_day >= 1 && current_day <= 2) {
                auto festival_spring = festival_spring_town::createScene();
                CCLOG("before");

                Director::getInstance()->pushScene(festival_spring);

                CCLOG("after");
            }
            else {
                auto town_scene = spring_town::createScene();

                CCLOG("before");
                //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
                //Director::getInstance()->replaceScene(town_scene);
                Director::getInstance()->pushScene(town_scene);

                CCLOG("after");
            }
        }
        else {
            auto town_scene = spring_town::createScene();

            CCLOG("before");
            //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
            //Director::getInstance()->replaceScene(town_scene);
            Director::getInstance()->pushScene(town_scene);

            CCLOG("after");
        }



        return true;
    }
    else if (season == Season::Winter)
    {
        auto town_scene = winter_town::createScene();
        CCLOG("before");
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        //Director::getInstance()->replaceScene(town_scene);
        Director::getInstance()->pushScene(town_scene);

        CCLOG("after");


        //加入人物在场景里
        //leading_charactor.person_scene_construction();
        //leading_charactor._sprite->setPosition(pos_player);
        return true;
    }
    else if (season == Season::Autumn)
    {
        auto town_scene = autumn_town::createScene();
        CCLOG("before");
        //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
        //Director::getInstance()->replaceScene(town_scene);
        Director::getInstance()->pushScene(town_scene);

        CCLOG("after");

        return true;
    }
    return false;
}


/*test*/
void test()
{
    auto now = Director::getInstance()->getRunningScene();
}

//切换到沙滩场景
bool change_to_beach()
{

    auto beach_scene = beach::createScene();
    people_remove_change();
    CCLOG("before");
    //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
    //Director::getInstance()->replaceScene(town_scene);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, beach_scene));

    CCLOG("after");

    return true;

}

//切换到矿洞场景
bool change_to_mine()
{
    auto mine_scene = scene_mine::createScene();
    people_remove_change();
    CCLOG("before");
    //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
    //Director::getInstance()->replaceScene(town_scene);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, mine_scene));

    CCLOG("after");


    return true;
}

//切换到家的场景
bool change_to_home()
{
    auto home_scene = scene_home::createScene();
    people_remove_change();
    CCLOG("before");
    //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
    //Director::getInstance()->replaceScene(town_scene);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, home_scene));

    CCLOG("after");

    return true;
}

//切换到商店场景
bool change_to_store()
{
    auto store_scene = scene_store::createScene();
    people_remove_change();
    CCLOG("before");
    //Director::getInstance()->replaceScene(TransitionFade::create(1.0f, town_scene));
    //Director::getInstance()->replaceScene(town_scene);
    Director::getInstance()->pushScene(TransitionFade::create(1.0f, store_scene));

    CCLOG("after");

    return true;
}

/* ---------- 退出调用 ---------- */

//小镇返回庄园
bool back_to_manor_from_town()
{
    people_remove_change();
    Director::getInstance()->popScene();
    return true;
}
//矿洞返回庄园
bool back_to_manor_from_mine()
{
    people_remove_change();
    Director::getInstance()->popScene();
    return true;
}
//家返回庄园
bool back_to_manor_from_home()
{
    people_remove_change();
    Director::getInstance()->popScene();
    return true;
}

//强制返回庄园
void force_back_to_manor() {
    Director::getInstance()->popToRootScene();
}

/* ---------- 场景初始化 ---------- */

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

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_BEACH);


    return true;
}


void beach::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);

}

void beach::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

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
    auto cropsLayer = Layer::create();
    cropsLayer->setName(CROPS_LAYER);
    cropsLayer->setLocalZOrder(CROPS);
    scene_spring->addChild(cropsLayer);
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    scene_spring->addChild(dropLayer);

    this->addChild(scene_spring);

    //随机生成树
    Tree::randomGenerate(scene_spring, objectLayer, 20, Stage::Mature);

    //随机生成石头
    Stone::randomGenerate(scene_spring, objectLayer, 20, StoneType::Stone);

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //auto playerControlLayer = PlayerControlLayer::create();
    //playerControlLayer->setPlayer(&leading_charactor);
    //this->addChild(playerControlLayer);

    //设置名字
    this->setName(SCENE_MANOR);

    return true;
}

void spring_manor::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);

}

void spring_manor::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

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

    Size mapsize = MapManager::getInstance()->getCurrentMapSize();
    Size tilesize = MapManager::getInstance()->getCurrentTileSize();

    Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

    this->addChild(scene_spring);



    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_SPRING_TOWN);

    return true;
}


void spring_town::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);
    npc1 = NPC::create();
    npc1->setPosition(650, 500);
    npc1->setScale(1.0f);
    MapManager::getInstance()->getCurrentMap()->addChild(npc1, PERSON_LAYER);
}

void spring_town::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

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

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_AUTUMN_TOWN);

    return true;
}


void autumn_town::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);
    npc1 = NPC::create();
    npc1->setPosition(650, 500);
    npc1->setScale(1.0f);
    MapManager::getInstance()->getCurrentMap()->addChild(npc1, PERSON_LAYER);
}

void autumn_town::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

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

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_WINTER_TOWN);


    return true;
}


void winter_town::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);
    npc1 = NPC::create();
    npc1->setPosition(650, 500);
    npc1->setScale(1.0f);
    MapManager::getInstance()->getCurrentMap()->addChild(npc1, PERSON_LAYER);
}

void winter_town::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

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

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_MINE);


    return true;
}

void scene_mine::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);

}

void scene_mine::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

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

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_HOME);

    return true;
}

void scene_home::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);

}

void scene_home::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

}


/* ---------- 节日场景 ---------- */
Scene* festival_spring_town::createScene()
{
    /*
    //创建场景
    auto scene_spring = Scene::create();
    //添加层
    auto layer = spring_town::create();
    scene_spring->addChild(layer);

    return scene_spring;
    */
    return festival_spring_town::create();
}

bool festival_spring_town::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_spring = TMXTiledMap::create("map/town_spring_festival.tmx"); // 替换为你的 .tmx 文件名



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

    Size mapsize = MapManager::getInstance()->getCurrentMapSize();
    Size tilesize = MapManager::getInstance()->getCurrentTileSize();

    Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

    this->addChild(scene_spring);



    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_SPRING_TOWN);

    return true;
}


void festival_spring_town::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);
    npc1 = NPC::create();
    npc1->setPosition(650, 500);
    npc1->setScale(1.0f);
    MapManager::getInstance()->getCurrentMap()->addChild(npc1, PERSON_LAYER);
}

void festival_spring_town::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

}


Scene* festival_winter_town::createScene()
{
    /*
    //创建场景
    auto scene_winter = Scene::create();
    //添加层
    auto layer = winter_town::create();
    scene_winter->addChild(layer);

    return scene_winter;
    */
    return festival_winter_town::create();
}

bool festival_winter_town::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto scene_winter = TMXTiledMap::create("map/town_winter_festival.tmx"); // 替换为你的 .tmx 文件名



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

    //将地图和场景关联
    //MapManager::getInstance()->registerSceneMap(this, scene_winter);

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

    Size mapsize = MapManager::getInstance()->getCurrentMapSize();
    Size tilesize = MapManager::getInstance()->getCurrentTileSize();

    Vec2 pos_player = tile_change_screen(mapsize, tilesize, Vec2(MANOR_TO_TOWN_X, MANOR_TO_TOWN_Y), TOWN_SMALL_SCALE);

    this->addChild(scene_winter);



    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    //设置名字
    this->setName(SCENE_WINTER_TOWN);

    return true;
}


void festival_winter_town::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);

    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);

}

void festival_winter_town::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

}

//商店场景
//
Scene* scene_store::createScene()
{
    
    return scene_store::create();
}

bool scene_store::init() {
    if (!Scene::init()) {
        return false;
    }
    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto store = TMXTiledMap::create("map/store.tmx"); // 替换为你的 .tmx 文件名



    //测试
    int visiablemood = get_window_size();
    if (visiablemood == SMALL_WINDOW)
    {
        //设置图缩放比例
        store->setScale(HOME_SMALL_SCALE);

        //获取当前屏幕大小
        Size screensize = Director::getInstance()->getVisibleSize();
        //设置进入的瓦片地图坐标
        Vec2 entrence = Vec2(MANOR_TO_HOME_X, MANOR_TO_HOME_Y);
        // 获取地图的尺寸  
        Size mapSize = store->getMapSize();
        Size tileSize = store->getTileSize();
        //设置进入的屏幕坐标
        Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, store->getScale());

        //屏幕左下角
        Vec2 point_row;

        point_row.x = screen_enterence.x;
        point_row.y = screen_enterence.y;

        store->setAnchorPoint(Vec2(0, 0));
        store->setPosition(point_row);


    }


    this->addChild(store);

    auto objectLayer = Layer::create();
    objectLayer->setName(OBJECT_LAYER);  // 设置名字
    objectLayer->setLocalZOrder(OBJECT);   // 设置层级
    store->addChild(objectLayer);
    auto ploughLayer = Layer::create();
    ploughLayer->setName(PLOUGH_LAYER);  // 设置名字
    ploughLayer->setLocalZOrder(PLOUGH);   // 设置层级
    store->addChild(ploughLayer);
    auto dropLayer = Layer::create();
    dropLayer->setName(DROP_LAYER);  // 设置名字
    dropLayer->setLocalZOrder(DROP);   // 设置层级
    store->addChild(dropLayer);

    // 添加全局层
    auto globalLayer = GlobalLayer::create();
    this->addChild(globalLayer, SETTING_LAYER); // 设置较高的 z-order，确保全局层在顶部

    auto buy_thinglayer = store_thing::create();
    this->addChild(buy_thinglayer);

    //设置名字
    this->setName(SCENE_STORE);

    return true;
}

void scene_store::onEnter()
{
    Scene::onEnter(); // 调用父类的 onEnter

    CCLOG("MyScene onEnter");
    std::string player_name = leading_charactor.getname();
    std::string farm_name = leading_charactor.getFarmName();
    int sex = leading_charactor.getSex();
    leading_charactor.person_construction(player_name, sex, farm_name, this);
    Vec2 original = Vec2(8, 5);
    float x = original.x * 16;
    float y = original.y * 16;
    Vec2 screenpos = Vec2(x, y);
    screenpos = screenpos * 3.5f;
    leading_charactor._sprite->setPosition(screenpos);



    auto playerControlLayer = PlayerControlLayer::create();
    playerControlLayer->setPlayer(&leading_charactor);
    playerControlLayer->setName(PLAYER_CONTROLER);
    this->addChild(playerControlLayer);

}

void scene_store::onExit()
{
    Scene::onExit(); // 调用父类的 onExit

    CCLOG("MyScene onExit");
    // 在这里添加自定义逻辑
    this->removeChildByName(PLAYER_CONTROLER);

    /* 移除人物 */
    people_remove_change();

}

bool store_thing::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 添加售货员图标
    auto shopper = Sprite::create("setting/shopper.png");
    shopper->setAnchorPoint(Vec2(0.5f, 0.5f));
    shopper->setPosition(Vec2(600, 500)); // 左上角 

    shopper->setScale(4.0f);
    this->addChild(shopper, 100);




    // 添加鼠标事件监听器
    auto listener = EventListenerMouse::create();

    listener->onMouseDown = [this, shopper](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) // 检测左键点击
        {
            Vec2 mousePos = mouseEvent->getLocationInView();
            Vec2 iconPos = shopper->getPosition();
            Size iconSize = shopper->getContentSize();

            // 检查点击是否在设置图标范围内
            if (mousePos.x >= iconPos.x - iconSize.width / 2 &&
                mousePos.x <= iconPos.x + iconSize.width / 2 &&
                mousePos.y >= iconPos.y - iconSize.height / 2 &&
                mousePos.y <= iconPos.y + iconSize.height / 2)
            {

                this->onShopperClicked(event);
                event->stopPropagation(); // 阻止事件继续传递
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, shopper);


}

void store_thing::onShopperClicked(cocos2d::Event* event)
{
    buy_sth();

}

void store_thing::buy_sth()
{
    if (STORE_MOOD == true) {
        STORE_MOOD = false;
    }
    else {
        auto backgroung = Sprite::create("menu/settingbackground.png"); // 替换为你的 .tmx 文件名

        auto currentscene = MapManager::getInstance()->getCurrentScene();

        //测试
        int visiablemood = get_window_size();
        if (visiablemood == SMALL_WINDOW)
        {
            //设置图缩放比例
            backgroung->setScale(2.0);
            // 获取当前窗口的尺寸
            auto director = Director::getInstance();
            auto glview = director->getOpenGLView();
            float screenWidth = glview->getFrameSize().width;
            float screenHeight = glview->getFrameSize().height;
            backgroung->setAnchorPoint(Vec2(0.5f, 0.5f));
            backgroung->setPosition(screenWidth / 2, screenHeight / 2);
            backgroung->setName("store_background");
        }
        currentscene->addChild(backgroung);


        auto backitem = MenuItemImage::create("menu/back_no.png",
            "bag/back_yes.png",
            CC_CALLBACK_1(store_thing::back, this));
        backitem->setPosition(Vec2(800, 470));
        backitem->setScale(0.5);




        auto carrotitem = MenuItemImage::create("bag/Carrot_Seeds.png",
            "bag/Carrot_Seeds.png",
            CC_CALLBACK_1(store_thing::carrotseed, this));
        carrotitem->setPosition(Vec2(100, 400));
        carrotitem->setScale(0.5);

        auto cornitem = MenuItemImage::create("bag/Corn_Seeds.png",
            "bag/Corn_Seeds.png",
            CC_CALLBACK_1(store_thing::cornseed, this));
        cornitem->setPosition(Vec2(160, 400));
        cornitem->setScale(0.5);
        auto eggplantitem = MenuItemImage::create("bag/Eggplant_Seeds.png",
            "bag/Eggplant_Seeds.png",
            CC_CALLBACK_1(store_thing::eggplantseed, this));
        eggplantitem->setPosition(Vec2(220, 400));
        eggplantitem->setScale(0.5);
        auto garlicitem = MenuItemImage::create("bag/Garlic_Seeds.png",
            "bag/Garlic_Seeds.png",
            CC_CALLBACK_1(store_thing::garlicseed, this));
        garlicitem->setPosition(Vec2(280, 400));
        garlicitem->setScale(0.5);
        auto melonitem = MenuItemImage::create("bag/Melon_Seeds.png",
            "bag/Melon_Seeds.png",
            CC_CALLBACK_1(store_thing::melonseed, this));
        melonitem->setPosition(Vec2(100, 300));
        melonitem->setScale(0.5);
        auto potatoitem = MenuItemImage::create("bag/Potato_Seeds.png",
            "bag/Potato_Seeds.png",
            CC_CALLBACK_1(store_thing::potatoseed, this));
        potatoitem->setPosition(Vec2(160, 300));
        potatoitem->setScale(0.5);
        auto pumpkinitem = MenuItemImage::create("bag/Pumpkin_Seeds.png",
            "bag/Pumpkin_Seeds.png",
            CC_CALLBACK_1(store_thing::pumpkinseed, this));
        pumpkinitem->setPosition(Vec2(220, 300));
        pumpkinitem->setScale(0.5);
        auto tomatoitem = MenuItemImage::create("bag/Tomato_Seeds.png",
            "bag/Tomato_Seeds.png",
            CC_CALLBACK_1(store_thing::tomatoseed, this));
        tomatoitem->setPosition(Vec2(280, 300));
        tomatoitem->setScale(0.5);



        auto menu = Menu::create(backitem, carrotitem,cornitem,eggplantitem,garlicitem,melonitem,potatoitem,pumpkinitem,tomatoitem, nullptr);
        menu->setPosition(Vec2::ZERO);
        backgroung->addChild(menu);
       


        STORE_MOOD = true;
    }
}

void store_thing::back(cocos2d::Ref* sender)
{
    Scene* currentscene = MapManager::getInstance()->getCurrentScene();
    auto shezhi = currentscene->getChildByName("store_background");
    if (shezhi) {
        shezhi->removeFromParent();
    }

}

void store_thing::carrotseed(Ref* sender)
{
    leading_charactor.moneyUP(-1);
    auto carrot = item(SEED_CARROT);
    leading_charactor.MyBag.addItem(carrot);

}

void store_thing::eggplantseed(Ref* sender) {
    leading_charactor.moneyUP(-2); // 减少角色的金钱
    auto eggplant = item(SEED_EGGPLANT); // 创建茄子种子
    leading_charactor.MyBag.addItem(eggplant); // 将种子添加到角色的背包
}

void store_thing::cabbageseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto cabbage = item(SEED_CABBAGE); // 创建卷心菜种子
    leading_charactor.MyBag.addItem(cabbage); // 将种子添加到角色的背包
}

void store_thing::cornseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto cgrs = item(SEED_CORN); // 创建CGRS种子
    leading_charactor.MyBag.addItem(cgrs); // 将种子添加到角色的背包
}

void store_thing::potatoseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto potato = item(SEED_POTATO); // 创建土豆种子
    leading_charactor.MyBag.addItem(potato); // 将种子添加到角色的背包
}

void store_thing::pumpkinseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto pumpkin = item(SEED_PUMPIN); // 创建南瓜种子
    leading_charactor.MyBag.addItem(pumpkin); // 将种子添加到角色的背包
}

void store_thing::melonseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto melon = item(SEED_MELON); // 创建西瓜种子
    leading_charactor.MyBag.addItem(melon); // 将种子添加到角色的背包
}

void store_thing::garlicseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto garlic = item(SEED_GARLIC); // 创建大蒜种子
    leading_charactor.MyBag.addItem(garlic); // 将种子添加到角色的背包
}

void store_thing::tomatoseed(Ref* sender) {
    leading_charactor.moneyUP(-1); // 减少角色的金钱
    auto tomato = item(SEED_TOMATO); // 创建番茄种子
    leading_charactor.MyBag.addItem(tomato); // 将种子添加到角色的背包
}


/*  ----- 本cpp实现进入游戏初始界面 ----- */


#include "SimpleAudioEngine.h"

#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"

using namespace cocos2d;


Scene* menu::createScene()
{
    //创建场景
    auto menuscene = Scene::create();
    //添加层
    auto layer = menu::create();
    menuscene->addChild(layer);

    return menuscene;
}

bool menu::init()
{
    if (!Scene::init())
    {
        return false;
    }

    // 加载 TMX 文件
    //FileUtils::getInstance()->addSearchPath("Resources/menu");


    auto welcome = TMXTiledMap::create("menu/welcome_small.tmx"); // 替换为你的 .tmx 文件名
    //auto welcome = TMXTiledMap::create("map/beach.tmx"); // 替换为你的 .tmx 文件名
    
   
    if (welcome)
    {
        this->addChild(welcome); // 将地图添加到场景中
        // 获取地图的尺寸  
        Size mapSize = welcome->getMapSize();
        Size tileSize = welcome->getTileSize();

        // 计算地图的总尺寸（宽 x 高）
        float mapWidth = mapSize.width * tileSize.width;
        float mapHeight = mapSize.height * tileSize.height;

        // 获取当前窗口的尺寸
        auto director = Director::getInstance();
        auto glview = director->getOpenGLView();
        float screenWidth = glview->getFrameSize().width;
        float screenHeight = glview->getFrameSize().height;

        // 计算缩放比例，使得地图完全适应屏幕
        float scaleX = screenWidth / mapWidth;
        float scaleY = screenHeight / mapHeight;

        // 选择较小的缩放比例，使地图能够完全显示
        float scale = std::min(scaleX, scaleY);
        welcome->setScale(scale);

        // 将地图的左下角对齐到屏幕左下角
        welcome->setPosition(0, 0); // 将地图的左下角定位到屏幕左下角
    }
    else
    {
        CCLOG("Failed to load TMX map!");
    }

    //加载地图完毕
    

    //加载菜单项
    //加载创建选项
    auto createItem = MenuItemImage::create(
        "menu/new_no.png",  // 正常状态图片
        "menu/new_yes.png", // 点击状态图片
        CC_CALLBACK_1(menu::onCreate, this));

    //加载读档选项
    auto loadItem = MenuItemImage::create(
        "menu/load_no.png",
        "menu/load_yes.png",
        CC_CALLBACK_1(menu::onLoad, this)
    );


    //加载合作选项
    auto coopItem = MenuItemImage::create(
        "menu/coop_no.png",
        "menu/coop_yes.png",
        CC_CALLBACK_1(menu::onCoop, this)
    );

    //加载退出选项
    auto exitItem = MenuItemImage::create(
        "menu/exit_no.png",
        "menu/exit_yes.png",
        CC_CALLBACK_1(menu::onEixt, this)
    );



    //设置图片大小
    createItem->setScale(ROW_PICTURE);
    loadItem->setScale(ROW_PICTURE);
    coopItem->setScale(ROW_PICTURE);
    exitItem->setScale(ROW_PICTURE);


    Size mapsize = welcome->getMapSize();
    Size tilesize = welcome->getTileSize();
    //new选项放置位置
    Vec2 new_pos = Vec2(POS_NEW_X, POS_NEW_Y);
    //NEW选项转换屏幕位置
    
    Vec2 screenpos_new = tile_change_screen(mapsize, tilesize, new_pos,welcome->getScale());

    //load选项放置位置
    Vec2 load_pos = Vec2(POS_LOAD_X, POS_LOAD_Y);
    Vec2 screenpos_load = tile_change_screen(mapsize, tilesize, load_pos, welcome->getScale());

    //coop选项放置位置
    Vec2 coop_pos = Vec2(POS_COOP_X, POS_COOP_Y);
    Vec2 screenpos_coop = tile_change_screen(mapsize, tilesize, coop_pos, welcome->getScale());

    //exit选项放置位置
    Vec2 exit_pos = Vec2(POS_EXIT_X, POS_EXIT_Y);
    Vec2 screenpos_exit = tile_change_screen(mapsize, tilesize, exit_pos, welcome->getScale());


    //设置位置
    createItem->setPosition(screenpos_new);
    loadItem->setPosition(screenpos_load);
    coopItem->setPosition(screenpos_coop);
    exitItem->setPosition(screenpos_exit);

    //创建菜单项
    auto my_menu = Menu::create(createItem, loadItem,coopItem,exitItem,nullptr);
    my_menu->setPosition(Vec2::ZERO);
    this->addChild(my_menu,1);





    //加载设置选项


    return true;
}


//创建菜单回调函数
void menu::onCreate(cocos2d::Ref* sender)
{
    //仅用于测试场景
    Director::getInstance()->pushScene(this);

    //测试，应创建主场景，先用沙滩测试
    auto beach_scene = beach::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, beach_scene));


}

//读档菜单回调函数
void menu::onLoad(cocos2d::Ref* sender)
{

}



//合作函数回调函数
void menu::onCoop(cocos2d::Ref* sender)
{

}


//退出选项回调函数
void menu::onEixt(cocos2d::Ref* sender)
{
    //可能需要加存档选项
    
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
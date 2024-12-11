/*  ----- 本cpp实现进入游戏初始界面 ----- */


#include "SimpleAudioEngine.h"

#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "menu.h"

using namespace cocos2d;


Scene* menu::createScene()
{
    auto menuscene = Scene::create();
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


    auto welcome = TMXTiledMap::create("menu/untitled.tmx"); // 替换为你的 .tmx 文件名
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

    return true;
}
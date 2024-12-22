/* ----- 该文件夹主cpp ----- */
/* 用于设置界面的实现 */
#include "cocos2d.h"

#include "definition.h"
#include"setting.h"
#include "Control/time.h"

USING_NS_CC;
//设置窗口大小
int get_window_size()
{

    return SMALL_WINDOW;

}

USING_NS_CC;

/* ---------- 全局层 创建全局显示：设置和血量 ---------- */
bool GlobalLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 创建设置图标
    auto settingsIcon = Sprite::create("setting/setting_.png");
    settingsIcon->setPosition(Vec2(50, Director::getInstance()->getWinSize().height - 50)); // 左上角 
    this->addChild(settingsIcon);

    // 创建时间显示
    auto dis_time = Sprite::create("setting/display_time.png");
    dis_time->setScale(1.4f);
    Vec2 pos_time = Vec2(Director::getInstance()->getWinSize().width - 120, Director::getInstance()->getWinSize().height - 90);
    dis_time->setPosition(pos_time);
    this->addChild(dis_time);

    // 创建时间文本框
    _timeLabel = Label::createWithSystemFont("Year 1 Spring Day 1", "fonts/Marker Felt.ttf", 22);
    _timeLabell = Label::createWithSystemFont("6 : 00", "fonts/Marker Felt.ttf", 22);

    // 设置文本颜色为黑色
    _timeLabel->setTextColor(Color4B::BLACK);
    _timeLabell->setTextColor(Color4B::BLACK);

    _timeLabel->setPosition(Vec2(Director::getInstance()->getWinSize().width - 125, Director::getInstance()->getWinSize().height - 45)); // 右上角
    this->addChild(_timeLabel);

    _timeLabell->setPosition(Vec2(Director::getInstance()->getWinSize().width - 120, Director::getInstance()->getWinSize().height - 170)); // 右上角
    this->addChild(_timeLabell);

    // 添加鼠标事件监听器
    auto listener = EventListenerMouse::create();

    listener->onMouseDown = [this, settingsIcon](Event* event) {
        EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event);
        if (mouseEvent->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) // 检测左键点击
        {
            Vec2 mousePos = mouseEvent->getLocationInView();
            Vec2 iconPos = settingsIcon->getPosition();
            Size iconSize = settingsIcon->getContentSize();

            // 检查点击是否在设置图标范围内
            if (mousePos.x >= iconPos.x - iconSize.width / 2 &&
                mousePos.x <= iconPos.x + iconSize.width / 2 &&
                mousePos.y >= iconPos.y - iconSize.height / 2 &&
                mousePos.y <= iconPos.y + iconSize.height / 2)
            {
                this->onSettingsClicked(event);
                event->stopPropagation(); // 阻止事件继续传递
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, settingsIcon);

    // 定时更新时间
    this->schedule([this](float dt) {
        this->updateTimeDisplay(dt);
        }, 1.0f, "update_time_display"); // 每秒更新一次



    return true;
}
void GlobalLayer::onSettingsClicked(cocos2d::Event* event)
{
    CCLOG("Settings icon clicked!");
    // 在这里处理设置图标的点击事件
    scene_setting();

}

void GlobalLayer::updateTimeDisplay(float dt)
{
    // 获取当前游戏时间（假设你有一个 GameTime 类来管理时间）
    std::vector<int> currentTime = GameTime::getInstance()->getTime();
    int hour, minute;
    hour = currentTime[0];
    minute = currentTime[1];
    std::string st_hour = std::to_string(hour);
    std::string st_minute = std::to_string(minute);

    int year = GameTime::getInstance()->getYear();
    int day = GameTime::getInstance()->getDay();

    std::string st_year = std::to_string(year);
    std::string st_day = std::to_string(day);


    Season season = GameTime::getInstance()->getSeason();
    std::string st_season;
    if (season == Season::Spring) {
        st_season = "Spring";
    }
    else if (season == Season::Summer) {
        st_season = "Summer";
    }
    else if (season == Season::Autumn) {
        st_season = "Autumn";
    }
    else if (season == Season::Winter) {
        st_season = "Winter";
    }

    // 更新文本框的内容

    _timeLabel->setString("Year" + st_year + " " + st_season + " Day " + st_day);
    _timeLabell->setString(st_hour + " : " + st_minute);
}


void GlobalLayer::scene_setting()
{
    Scene* currentscene = MapManager::getInstance()->getCurrentScene();
    if (SETTING_MODE == true) {
        SETTING_MODE = false;
    }
    else {
        auto backgroung = Sprite::create("menu/settingbackground.png"); // 替换为你的 .tmx 文件名

        // 测试
        int visiablemood = get_window_size();
        if (visiablemood == SMALL_WINDOW)
        {
            // 设置图缩放比例
            backgroung->setScale(2.0);
            // 获取当前窗口的尺寸
            auto director = Director::getInstance();
            auto glview = director->getOpenGLView();
            float screenWidth = glview->getFrameSize().width;
            float screenHeight = glview->getFrameSize().height;
            backgroung->setAnchorPoint(Vec2(0.5f, 0.5f));
            backgroung->setPosition(screenWidth / 2, screenHeight / 2);
            backgroung->setName("setting_background");
        }
        currentscene->addChild(backgroung);

        // 创建音量按钮
        auto volumeButton = createVolumeButton();
        volumeButton->setPosition(Vec2(100, 400));
        volumeButton->setName("volume_button"); // 设置音量按钮的名称
        // 创建返回按钮
        auto backitem = MenuItemImage::create("menu/back_no.png",
            "menu/back_yes.png",
            CC_CALLBACK_1(GlobalLayer::back, this));
        backitem->setPosition(Vec2(700, 400));
        backitem->setScale(1);
        backitem->setName("back_button"); // 设置返回按钮的名称
        // 创建菜单，包含音量按钮和返回按钮
        auto menu = Menu::create(volumeButton, backitem, nullptr);
        menu->setPosition(Vec2::ZERO);
        backgroung->addChild(menu);
        menu->setName("setting_menu"); // 为菜单设置名称
        SETTING_MODE = true;
    }
}
void GlobalLayer::back(cocos2d::Ref* sender)
{
    Scene* currentscene = MapManager::getInstance()->getCurrentScene();
    auto shezhi = currentscene->getChildByName("setting_background");
    if (shezhi) {
        shezhi->removeFromParent();
    }
}
// 创建音量按钮
cocos2d::MenuItemToggle* GlobalLayer::createVolumeButton() {
    // 创建“播放”和“暂停”按钮的图像
    auto playItem = MenuItemImage::create("setting/play_button.png", "setting/play_button.png");
    auto pauseItem = MenuItemImage::create("setting/mute_button.png", "setting/mute_button.png");

    // 调整按钮大小（缩放到 0.1 倍）
    playItem->setScale(0.1);
    pauseItem->setScale(0.1);

    // 创建一个 Toggle 按钮
    auto volumeButton = MenuItemToggle::createWithCallback(CC_CALLBACK_1(GlobalLayer::toggleBGM, this), playItem, pauseItem, nullptr);

    // 根据背景音乐的播放状态设置初始状态
    if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        // 如果背景音乐正在播放，初始状态为“暂停”
        volumeButton->setSelectedIndex(1); // 1 表示暂停按钮
    }
    else {
        // 如果背景音乐未播放，初始状态为“播放”
        volumeButton->setSelectedIndex(0); // 0 表示播放按钮
    }

    // 设置按钮的锚点为左上角
    volumeButton->setAnchorPoint(Vec2(0.5f, 0.5f));
    volumeButton->setLocalZOrder(10); // 设置一个较高的 zOrder 值

    return volumeButton;
}

// 音量按钮的回调函数
void GlobalLayer::toggleBGM(cocos2d::Ref* pSender) {
    if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying()) {
        // 如果背景音乐正在播放，则暂停
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();

        // 暂停音效（如果有音效正在播放）
        SimpleAudioEngine::getInstance()->pauseAllEffects();

        // 更新按钮状态为“播放”
        static_cast<MenuItemToggle*>(pSender)->setSelectedIndex(0);
    }
    else {
        // 如果背景音乐没有播放，则播放
        SimpleAudioEngine::getInstance()->playBackgroundMusic("setting/BGM.mp3", true);


        // 更新按钮状态为“暂停”
        static_cast<MenuItemToggle*>(pSender)->setSelectedIndex(1);
    }
}
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
    //创建时间显示
    auto dis_time = Sprite::create("setting/display_time.png");
    dis_time->setScale(1.4f);
    Vec2 pos_time = Vec2(Director::getInstance()->getWinSize().width - 120, Director::getInstance()->getWinSize().height - 90);
    dis_time->setPosition(pos_time);
    this->addChild(dis_time);

    // 创建时间文本框
    _timeLabel = Label::createWithSystemFont("Year 1 Spring Day 1", "fonts/Marker Felt.ttf", 22);
    _timeLabell= Label::createWithSystemFont("6 : 00", "fonts/Marker Felt.ttf", 22);
    
    // 设置文本颜色为红色
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
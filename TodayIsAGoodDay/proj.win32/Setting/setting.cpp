/* ----- 该文件夹主cpp ----- */
/* 用于设置界面的实现 */
#include "cocos2d.h"

#include "definition.h"
#include"setting.h"

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
            }
        }
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, settingsIcon);

    return true;
}

void GlobalLayer::onSettingsClicked(cocos2d::Event* event)
{
    CCLOG("Settings icon clicked!");
    // 在这里处理设置图标的点击事件
}
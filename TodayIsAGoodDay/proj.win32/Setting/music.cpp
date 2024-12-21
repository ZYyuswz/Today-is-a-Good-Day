/* ----- 实现背景音乐调用及大小设置 ----- */
#include <iostream>
#include "SimpleAudioEngine.h"
#include "definition.h"
#include "cocos2d.h"
#include <functional>
#include "ui/CocosGUI.h"
#include "setting.h"
#include "Time.h"
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d;

// 预加载背景音乐
int preload_BGM() {
    // 检查文件是否存在
    if (!SimpleAudioEngine::getInstance()->willPlayBackgroundMusic()) {
        cerr << "Error: Background music file not found or invalid." << endl;
        return -1;
    }

    // 尝试预加载背景音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("setting/BGM.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("setting/Rain_BGM.mp3"); // 使用 preloadEffect 预加载音效

    return 0;
}
void play_BGM(Weather current_weather)
{ 
    SimpleAudioEngine::getInstance()->playBackgroundMusic("setting/BGM.mp3", true);
    if (current_weather == Weather::Rainy)SimpleAudioEngine::getInstance()->playEffect("setting/Rain_BGM.mp3", true); // 使用 playEffect 播放音效
}

// 播放或暂停背景音乐和音效
void toggleBGM(Ref* pSender) {
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

        // 播放音效（如果是雨天）
        if (1)//这里需要调用天气情况
            SimpleAudioEngine::getInstance()->playEffect("setting/Rain_BGM.mp3", true);

        // 更新按钮状态为“暂停”
        static_cast<MenuItemToggle*>(pSender)->setSelectedIndex(1);
    }
}

// 调整背景音乐音量,num的范围为0~1。
void volume_adjustment(float num)
{
    // 检查音量范围，确保在 0.0f 到 1.0f 之间
    if (num < 0.0f)
    {
        num = 0.0f;
    }
    else if (num > 1.0f)
    {
        num = 1.0f;
    }
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5);
    // 调试输出，方便调试
    CCLOG("Background music volume adjusted to: %f", num);
}

// 创建音量按钮
MenuItemToggle* createVolumeButton() {
    // 创建“播放”和“暂停”按钮的图像
    auto playItem = MenuItemImage::create("setting/play_button.png", "setting/play_button.png");
    auto pauseItem = MenuItemImage::create("setting/mute_button.png", "setting/mute_button.png");
    // 调整按钮大小（缩放到 0.1 倍）
    playItem->setScale(0.1);
    pauseItem->setScale(0.1);
    // 使用 std::bind 绑定回调函数
    auto callback = bind(toggleBGM, std::placeholders::_1);

    // 创建一个 Toggle 按钮，初始状态为“播放”
    auto volumeButton = MenuItemToggle::createWithCallback(callback, playItem, pauseItem, nullptr);
    // 设置按钮的锚点为左上角
    volumeButton->setAnchorPoint(Vec2(0, 1));

    // 设置按钮的位置为游戏界面的左上角
    volumeButton->setPosition(Vec2(0, 0));
    return volumeButton;
}


// 创建音量调整进度条
ui::Slider* createVolumeSlider() {
    // 创建音量调整进度条
    auto slider = ui::Slider::create();
    slider->loadBarTexture("setting/slider_bar.png"); // 加载进度条背景图片
    slider->loadSlidBallTextures("setting/slider_ball.png", "setting/slider_ball.png", ""); // 加载滑块图片
    slider->loadProgressBarTexture("setting/slider_progress.png"); // 加载进度条图片

    // 设置滑块的初始值为当前音量
    slider->setPercent(SimpleAudioEngine::getInstance()->getBackgroundMusicVolume() * 100);
    slider->setContentSize(Size(150, 25)); // 设置进度条的宽度和高度

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 计算进度条的位置
    Vec2 topLeftPosition = Vec2(origin.x + 1000, origin.y + visibleSize.height - 200);

    // 设置滑块的位置
    slider->setPosition(topLeftPosition);

    // 绑定滑块的回调函数
    slider->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
        if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
            ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
            float volume = slider->getPercent() / 100.0f;
            volume_adjustment(volume);
        }
        });

    return slider;
}
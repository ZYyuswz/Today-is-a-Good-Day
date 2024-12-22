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
void play_BGM()
{
    SimpleAudioEngine::getInstance()->playBackgroundMusic("setting/BGM.mp3", true);
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
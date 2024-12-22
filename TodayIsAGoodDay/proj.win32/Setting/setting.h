#pragma once

#include"cocos2d.h"
#include "ui/UISlider.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

int get_window_size();
int preload_BGM();
void play_BGM();
void volume_adjustment(float num);

ui::Slider* createVolumeSlider();

/* --------- 全局设置与显示层 ---------- */
class GlobalLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    // 设置图标的点击回调
    void onSettingsClicked(cocos2d::Event* event);

    // 更新时间的函数
    void updateTimeDisplay(float dt);


    // 使用 CREATE_FUNC 宏
    CREATE_FUNC(GlobalLayer);

    void scene_setting();

    void back(cocos2d::Ref* sender);
    // 创建音量按钮
    cocos2d::MenuItemToggle* createVolumeButton();

    // 音量按钮的回调函数
    void toggleBGM(cocos2d::Ref* pSender);
private:
    cocos2d::Label* _timeLabel; // 用于显示时间的文本框
    cocos2d::Label* _timeLabell; // 用于显示时间的文本框

    bool SETTING_MODE = false;
};


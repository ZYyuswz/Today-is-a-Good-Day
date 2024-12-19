#pragma once

#include"cocos2d.h"
#include "ui/UISlider.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
using namespace cocos2d;

int get_window_size();
int preload_BGM();
void play_BGM(bool flag);
void volume_adjustment(float num);
MenuItemToggle* createVolumeButton();
ui::Slider* createVolumeSlider();

/* --------- ȫ�ֲ� ---------- */
class GlobalLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    // ����ͼ��ĵ���ص�
    void onSettingsClicked(cocos2d::Event* event);

    // ʹ�� CREATE_FUNC ��
    CREATE_FUNC(GlobalLayer);
};
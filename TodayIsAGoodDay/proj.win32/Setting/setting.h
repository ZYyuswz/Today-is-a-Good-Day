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

/* --------- ȫ����������ʾ�� ---------- */
class GlobalLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    // ����ͼ��ĵ���ص�
    void onSettingsClicked(cocos2d::Event* event);

    // ����ʱ��ĺ���
    void updateTimeDisplay(float dt);


    // ʹ�� CREATE_FUNC ��
    CREATE_FUNC(GlobalLayer);

    void scene_setting();

    void back(cocos2d::Ref* sender);
    // ����������ť
    cocos2d::MenuItemToggle* createVolumeButton();

    // ������ť�Ļص�����
    void toggleBGM(cocos2d::Ref* pSender);
private:
    cocos2d::Label* _timeLabel; // ������ʾʱ����ı���
    cocos2d::Label* _timeLabell; // ������ʾʱ����ı���

    bool SETTING_MODE = false;
};


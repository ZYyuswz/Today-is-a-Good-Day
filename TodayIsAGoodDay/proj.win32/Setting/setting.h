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

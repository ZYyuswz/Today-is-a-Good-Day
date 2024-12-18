#pragma once
int get_window_size();
int preload_BGM();
void play_BGM(bool flag);
void volume_adjustment(float num);
MenuItemToggle* createVolumeButton();
ui::Slider* createVolumeSlider();

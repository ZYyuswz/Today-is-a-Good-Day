#include "Time.h"
#include <iostream>
#include "totaltools.h"

// 单例模式：静态成员变量初始化
GameTime* GameTime::instance = nullptr;

// 单例模式：获取单例实例
GameTime* GameTime::getInstance() {
    if (!instance) {
        instance = new GameTime();
    }
    return instance;
}

// 构造函数，初始化时间
GameTime::GameTime() {
    year = 1;
    day = 1;
    totalDays = 1;
    season = Season::Spring;
    weather = Weather::Sunny;
}

// 更新一天的时间 
void GameTime::updateTime() {
    day++;
    totalDays++;
    // 切换季节
    if (day > SEASON_LENGTH) {
        day = 1;
        if (season == Season::Winter)
            year++;
        season = static_cast<Season>((static_cast<int>(season) + 1) % 4);  // 切换季节
    }
    // 随机天气
    bool weather_condition = random_bernoulli(0.4);
    if (weather_condition)weather = Weather::Rainy;
    else weather = Weather::Sunny;
}

// 获取当前年份
int GameTime::getYear() const {
    return year;
}

// 获取当前天数
int GameTime::getDay() const {
    return day;
}

// 获取当前季节
Season GameTime::getSeason() const {
    return season;
}

// 获取当前天气
Weather GameTime::getWeather() const {
    return weather;
}

// 获取总天数
int GameTime::getTotalDays() const {
    return totalDays;
}


/*  -----实现右上角时间的显示并可以反馈给任何想知道时间的地方 ----- */
#include "Time.h"
#include <iostream>

// 构造函数，初始化时间
Time::Time() {
    year = 1;
    day = 1;
    totalDays = 1;
    season = Season::Spring;
}

// 更新一天的时间
void Time::updateTime() {
    day++;
    totalDays++;
    // 切换季节
    if (day > SEASON_LENGTH) {
        day = 1;
        if (season == Season::Winter)
            year++;
        season = static_cast<Season>((static_cast<int>(season) + 1) % 4);  // 切换季节
    }
}

// 获取当前年份
int Time::getYear() const {
    return year;
}

// 获取当前天数
int Time::getDay() const {
    return day;
}

// 获取当前季节
Season Time::getSeason() const {
    return season;
}

// 获取总天数
int Time::getTotalDays() const {
    return totalDays;
}


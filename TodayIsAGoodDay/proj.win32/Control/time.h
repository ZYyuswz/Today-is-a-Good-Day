/*  -----实现右上角时间的显示并可以反馈给任何想知道时间的地方 ----- */
#pragma once
#include "definition.h"
#include <string>

class Time {
private:
    int year;        // 当前年份
    int day;         // 当前天数
    Season season;   // 当前季节
    int totalDays;   // 总天数

public:
    // 构造函数
    Time();

    // 更新一天的时间
    void updateTime();

    // 获取当前年份
    int getYear() const;

    // 获取当前天数
    int getDay() const;

    // 获取当前季节
    Season getSeason() const;

    // 获取总天数
    int getTotalDays() const;
};
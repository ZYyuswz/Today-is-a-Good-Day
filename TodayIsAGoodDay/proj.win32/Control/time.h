#pragma once
#include "definition.h"
#include <string>

class GameTime {
private:
    int year;        // 当前年份
    int day;         // 当前天数
    Season season;   // 当前季节
    int totalDays;   // 总天数

    // 单例模式：私有构造函数
    GameTime();

    // 单例模式：静态成员变量
    static GameTime* instance;

public:
    // 单例模式：获取单例实例
    static GameTime* getInstance();

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
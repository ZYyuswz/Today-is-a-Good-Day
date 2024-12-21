#pragma once
#include <iostream>
#include "definition.h"
#include "totalTools.h"
#include <string>
#include "cocos2d.h"
#include "Map/tree.h"
#include "Map/crops.h"
#include "Map/plough.h"
#include "Map/stone.h"
#include "scene.h"

USING_NS_CC;


class GameTime {
private:

    int year;               // 当前年份
    int day;                // 当前天数
    Season season;          // 当前季节 
    Weather weather;        // 当前天气 随机天气还没实现
    int totalDays;          // 总天数
    int time[2];            // 当前时间：time[0] 表示小时，time[1] 表示分钟 


    // 单例模式：私有构造函数
    GameTime();

    // 单例模式：静态成员变量
    static GameTime* instance;

public:
    // 单例模式：获取单例实例
    static GameTime* getInstance();

    // 更新一天
    void updateDay();

    // 更新一天的时间
    void updateTime();

    // 启动自动更新
    void startAutoUpdate();

    // 停止自动更新
    void stopAutoUpdate();

    // 获取当前年份
    int getYear() const;

    // 获取当前天数
    int getDay() const;

    // 获取当前季节
    Season getSeason() const;

    // 获取当前天气
    Weather getWeather() const;

    // 获取总天数
    int getTotalDays() const;

    // 打印时间，调试用
    void printTime() const;

    // 返回时间：小时+分钟
    std::vector<int> getTime() const;
};
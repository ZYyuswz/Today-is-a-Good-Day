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
    // 使用系统时间初始化游戏时间
    time[0] = 6;  // 初始时间为早上 6 点
    time[1] = 0;  // 初始分钟为 0
}

// 更新一天的时间 
void GameTime::updateDay() {
    // 更新时间
    day++;
    totalDays++;
    time[0] = 6;  // 早上 6 点
    time[1] = 0;  //  0
    // 切换季节
    if (day > SEASON_LENGTH) {
        day = 1;
        if (season == Season::Winter)
            year++;
        season = static_cast<Season>((static_cast<int>(season) + 1) % 4);  // 切换季节
    }
    // 随机生成天气
    bool weather_condition = random_bernoulli(0.8);
    if (weather_condition)
        weather = Weather::Rainy;
    else
        weather = Weather::Sunny;
    CCLOG("Weather changed to: %d", static_cast<int>(weather));  // 输出天气切换日志

    // 获取当前地图
    auto map = MapManager::getInstance()->getCurrentMap();
    if (!map) {
        CCLOG("Map not found in the scene!--Time");
        return;
    }
    // 获取 dropLayer
    auto dropLayer = dynamic_cast<Layer*>(map->getChildByName("DropLayer"));
    if (!dropLayer) {
        CCLOG("ObjectLayer not found in the map!--Time");
        return;
    }
    // 获取 PloughLayer
    auto ploughLayer = dynamic_cast<Layer*>(map->getChildByName("PloughLayer"));
    if (!ploughLayer) {
        CCLOG("PloughLayer not found in the map!--Time");
        return;
    }
    // 获取 objectLaye
    auto objectLayer = dynamic_cast<Layer*>(map->getChildByName("ObjectLayer"));
    if (!objectLayer) {
        CCLOG("ObjectLayer not found in the map!--Time");
        return;
    }
    // 1.tree
    Tree::updateAll(objectLayer);
    // 2.crops
    Crops::updateAll(objectLayer);
    // 3. plough
    Plough::updateAll(ploughLayer);
    
    //// test
    //auto tree2 = new Tree(map, objectLayer, Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y-6), TreeType::Maple, Stage::Mature);
    //tree2->reduceHealth(100);
    //auto Pumpkin1 = new Pumpkin(map, objectLayer, Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y - 7), Stage::Mature);
    //Pumpkin1->harvest();
    //auto stone1 = new Stone(map, objectLayer, Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y-8), StoneType::Gold);
    //stone1->reduceHealth(100);

}

// 每隔 1 秒（UPDATE_INTERVAL 定义为 1.0f）调用一次updateTime()方法游戏时间增加10分钟
void GameTime::updateTime(){
    // 增加十分钟
    time[1] += 10;

    // 如果分钟达到 60，则增加小时
    if (time[1] >= 60) {
        time[0] += time[1] / 60;  // 增加小时
        time[1] %= 60;            // 分钟归零

        // 如果小时达到 24，取模
        if (time[0] >= 24) {
            time[0] %= 24;        // 小时归零
        }
    }

    // 特殊逻辑：如果时间达到 2:00，则送回家并更新天数
    if (time[0] == 2) {
        // 送回家
        updateDay();
    }
    printTime();
}

void GameTime::startAutoUpdate() {
    // 使用 Cocos2d-x 的定时器，每隔 UPDATE_INTERVAL 秒调用一次 updateTime 方法
    cocos2d::Director::getInstance()->getScheduler()->schedule(
        [this](float delta) {
            this->updateTime();
        },
        this, // 定时器的目标对象
        UPDATE_INTERVAL, // 定时器的时间间隔
        false,// false 表示定时器立即启动
        "GameTimeUpdate"  // 使用标签 "GameTimeUpdate" 标识定时器
    );
    CCLOG("Auto update started.");  // 输出启动日志
}

void GameTime::stopAutoUpdate() {
    // 停止定时器
    cocos2d::Director::getInstance()->getScheduler()->unschedule(
        "GameTimeUpdate",  // 使用相同的标签 "GameTimeUpdate" 停止定时器
        this // 表示定时器的目标对象
    );
    CCLOG("Auto update stopped.");  // 输出停止日志

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

// 打印时间，调试用
void GameTime::printTime() const {
    CCLOG("Day:%d, TotalDays:%d, Hour:%d, Minute:%d",day,totalDays,time[0], time[1]);
} 
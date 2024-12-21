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

        //force_back_to_manor();
        //manor_change_map();

    }
    // 随机生成天气
    bool weather_condition = random_bernoulli(0.8);
    if (weather_condition)
    {
        weather = Weather::Rainy;
        GameTime* gametime = GameTime::getInstance();
        Scene* currentscene = MapManager::getInstance()->getCurrentScene();
        if (gametime->getWeather() == Weather::Rainy)currentscene->addChild(gametime->RainLayers(), RAINLAYER); //下雨场景实现示例
    }
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
    // 获取 cropsLayer
    auto cropsLayer = dynamic_cast<Layer*>(map->getChildByName("CropsLayer"));
    if (!cropsLayer) {
        CCLOG("CropsLayer not found in the map!--Time");
        return;
    }
    // 1.tree
    Tree::updateAll(objectLayer);
    // 2.crops
    Crops::updateAll(cropsLayer);
    // 3. plough
    Plough::updateAll(ploughLayer);

}

// 每隔 1 秒（UPDATE_INTERVAL 定义为 1.0f）调用一次updateTime()方法游戏时间增加10分钟
void GameTime::updateTime() {
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
    // 特殊逻辑：如果时间达到 18:00，则天黑
    if (time[0] >= 18 || time[0] <= 2) {
        // 获取当前场景
        auto currentScene = MapManager::getInstance()->getCurrentScene();
        if (!currentScene) {
            CCLOG("Current scene not found!");
            return;
        }

        // 查找之前创建的 Overlay 节点
        auto overlay = currentScene->getChildByName("Overlay");

        // 如果 overlay 不存在，创建一个新的
        if (!overlay) {
            overlay = LayerColor::create(Color4B(0, 0, 0, 0)); // 初始透明度为 0
            overlay->setName("Overlay");
            overlay->setPosition(0, 0);
            currentScene->addChild(overlay);
        }

        // 使用 Action 实现透明度的渐变（逐渐变暗）
        auto fadeAction = FadeTo::create(1.0f, 128); // 1.0f 是渐变时间（1 秒），128 是目标透明度
        overlay->runAction(fadeAction);
    }
    else {
        // 获取当前场景
        auto currentScene = MapManager::getInstance()->getCurrentScene();
        if (currentScene) {
            // 查找之前创建的 Overlay 节点
            auto overlay = currentScene->getChildByName("Overlay");
            if (overlay) {
                // 使用 Action 实现透明度的渐变（逐渐变亮）
                auto fadeAction = FadeTo::create(1.0f, 0); // 1.0f 是渐变时间（1 秒），0 是目标透明度
                overlay->runAction(fadeAction);

                // 渐变完成后移除 Overlay 节点
                auto removeAction = CallFunc::create([overlay, currentScene]() {
                    currentScene->removeChild(overlay);
                    });
                overlay->runAction(Sequence::create(fadeAction, removeAction, nullptr));
            }
        }
    }
    // 特殊逻辑：如果时间达到 2:00，则送回家并更新天数
    if (time[0] == 2) {
        // 送回家
        updateDay();
    }
    //printTime();
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

std::vector<int> GameTime::getTime() const {
    return { time[0], time[1] };  // 返回一个 std::vector
}

//下雨场景添加
ParticleRain* GameTime::RainLayers() {
    // 添加雨水粒子效果
    auto rainParticle = ParticleRain::create();
    Size screensize = Director::getInstance()->getVisibleSize();
    rainParticle->setPosition(Vec2(screensize.width / 2, screensize.height)); // 设置粒子系统的位置
    rainParticle->setLife(10.0f); // 设置雨滴的生命周期
    rainParticle->setSpeed(400.0f); // 设置雨滴的速度
    rainParticle->setAngle(-90.0f); // 设置雨滴的角度
    rainParticle->setStartColor(Color4F(0.5f, 0.5f, 1.0f, 1.0f)); // 设置雨滴的颜色
    rainParticle->setEndColor(Color4F(0.5f, 0.5f, 1.0f, 0.8f)); // 设置雨滴的透明度
    rainParticle->setTotalParticles(2000); // 设置雨滴的数量

    // 设置雨滴的大小
    rainParticle->setStartSize(18.0f); // 设置雨滴的初始大小为 18 像素
    rainParticle->setStartSizeVar(5.0f); // 设置雨滴大小的变化范围为 5 像素
    rainParticle->setEndSize(10.0f); // 设置雨滴的结束大小为 10 像素
    rainParticle->setEndSizeVar(2.0f); // 设置雨滴结束大小的变化范围为 2 像素

    // 检查纹理是否正确加载
    if (rainParticle->getTexture() == nullptr) {
        CCLOG("Error: Particle texture is missing!");
    }
    else {
        CCLOG("Particle texture loaded successfully!");
    }
    return rainParticle;
}
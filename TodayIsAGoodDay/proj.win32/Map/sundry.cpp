/* ----- 杂项文件 以备不时之需 ----- */ 
#include "sundry.h"

// 根据季节获取鱼的种类
std::vector<FishType> getFishForSeason(Season season) {
    switch (season) {
    case Season::Spring:
        return { FishType::Carp, FishType::Chub, FishType::Crab, FishType::Eel };
    case Season::Summer:
        return { FishType::Lobster, FishType::Salmon, FishType::Sardine, FishType::Sea_Cucumber };
    case Season::Autumn:
        return { FishType::Shrimp, FishType::Squid, FishType::Sturgeon, FishType::Tuna };
    case Season::Winter:
    default:
        return {};  // 冬季没有鱼
    }
}

// 随机选择一种鱼
FishType getRandomFish(const std::vector<FishType>& fishList) {
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> dist(0, fishList.size() - 1);
    return fishList[dist(rng)];
}

// 钓鱼函数
FishType getFish() {
    // 获取当前季节
    Season currentSeason = GameTime::getInstance()->getSeason();

    // 获取当前季节的鱼种类
    std::vector<FishType> fishList = getFishForSeason(currentSeason);

    // 如果当前季节没有鱼，返回空
    if (fishList.empty()) {
        return FishType::NullFish;
    }
    return getRandomFish(fishList);
}

// 钓鱼逻辑
void fishing() {
    // PS：这里写人物甩杆动画

    // 生成一个随机数，判断是否钓鱼成功
    static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    while (1) {
        double successRate = dist(rng);
        if (successRate <= FISHING_SUCCESS_RATE) {
            // 钓鱼成功，调用 getFish() 获取钓上的鱼
            FishType caughtFish = getFish();
            // PS：这里再写人物旁边出现感叹号的逻辑

            // PS：这里可以接受一个监听器，收杆

            // PS：这里写把鱼添加到背包的逻辑

            break;
        }
        // 这里写如果再次点击左键收杆动画并且退出循环
        //if () {  
        //    break;
        //}
        // 休眠一段时间（例如 1 秒），假设使用秒为单位
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return;
}
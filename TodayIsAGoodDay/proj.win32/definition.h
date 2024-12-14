#pragma once

// 定义每个季节的持续天数
#define SEASON_LENGTH 28  // 每个季节持续28天

// 定义一个瓦片的尺寸
#define TILESIZE 16

// 定义一个常规瓦片地图的大小
#define GENERALMAPSIZE 64

// 枚举类表示季节
enum class Season {
    Spring,  // 春天
    Summer,  // 夏天
    Autumn,  // 秋天
    Winter   // 冬天
};

// 定义树的种类枚举
enum class TreeType {
    Oak,    // 橡树
    Pine,   // 松树
    Maple   // 枫树
};

// 枚举表示GrowObject的阶段
enum class Stage {
    Childhood, // 幼年阶段
    Mature     // 成熟阶段
};

// 定义石头的种类枚举
enum class StoneType {
    Stone,      // 石头
    Copper,     // 铜矿
    Silver,      // 银矿
    Gold,       // 金矿
    Coal        // 煤炭
};

// 定义角点枚举类型 -- 瓦片的四个角定义
enum TileCorner {
    TOP_LEFT,    // 左上角
    BOTTOM_LEFT, // 左下角
    TOP_RIGHT,   // 右上角
    BOTTOM_RIGHT, // 右下角
    CENTER, // 中心
    BOTTOM_CENTER // 下方中心
};

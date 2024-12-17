
#pragma once

//屏幕显示比例
#define SMALL_WINDOW 1

//图层显示关系宏定义
#define FIRST 1

//图片显示比例宏定义
#define ROW_PICTURE 1.0f   //原图片大小

//menu相关宏定义
#define POS_NEW_X 4
#define POS_NEW_Y 3
#define POS_LOAD_X 12
#define POS_LOAD_Y 3
#define POS_COOP_X 20
#define POS_COOP_Y 3
#define POS_EXIT_X 28
#define POS_EXIT_Y 3


//beach场景相关宏定义
// beach缩放比例
// 小窗口下
#define BEACH_SMALL_SCALE 3.5f
//beach入口位置
#define BEACH_ENTER_X 25
#define BEACH_ENTER_Y 48

//庄园场景相关宏定义
//缩放比例
//小窗口下
#define SRING_MANOR_SMALL_SCALE 3.5f
#define SPRING_MANOR_ENTER_X 44
#define SPRING_MANOR_ENTER_Y 40


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
    Growth,    // 成长阶段
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
    TOP_LEFT,           // 左上角
    BOTTOM_LEFT,        // 左下角
    TOP_RIGHT,          // 右上角
    BOTTOM_RIGHT,       // 右下角
    CENTER,             // 中心
    BOTTOM_CENTER       // 下方中心
};


// 耕地状态
enum class LandState {
    Tilled,             // 已耕地
    Watered,            // 已浇水
    Fertilized,         // 已施肥
    FertilizedWatered,  // 施肥浇水
};

// 天气状态
enum class Weather {
    Sunny,   // 晴天
    Rainy    // 雨天
};

// 耕地销毁的时间阈值
#define LAND_DESTORY_THRESHOLD 3

// 树生长天数阈值
#define TREE_GROWTH_THRESHOLD 5


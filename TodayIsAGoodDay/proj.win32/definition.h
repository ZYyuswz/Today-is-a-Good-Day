#pragma once
#include <map>
//屏幕显示比例
#define SMALL_WINDOW 1

//图层显示关系宏定义
#define FIRST 1

#define OBJECT 2
#define PLOUGH 3
#define CROPS 4 
#define DROP 5
#define PERSON_LAYER 10

#define RAINLAYER 100
#define BAGLAYER  101 
#define SETTING_LAYER 102

//图片显示比例宏定义
#define ROW_PICTURE 1.0f   //原图片大小

// 人物
// 人物移动像素点
#define MOVE_DISTANCE 2.0f
enum class DIRECTION {
    LEFT,  //左
    RIGHT,  //右
    UP,    //上
    DOWN   //下
};
//人物最远鼠标点击距离
#define MAX_PERSON_LENTH 4

//工具宏定义
#define TOOL_HAMMER "hammer" //锤子
#define TOOL_AXE "axe"   //斧子 
#define TOOL_DRAFT "draft"  //锄头
#define TOOL_KETTLE "kettle"  //水壶
#define TOOL_FISHING_POLE "fishing_pole"   //钓鱼竿

#define SEED_CARROT "seed_carrot"   //胡萝卜
#define SEED_GARLIC "seed_garlic"   //大蒜
#define SEED_POTATO "seed_potato"   //土豆
#define SEED_CORN  "seed_corn"      //玉米类
#define SEED_MELON "seed_melon"  //瓜
#define SEED_CABBAGE "seed_cabbage"   //白菜
#define SEED_TOMATO "seed_tomato"    //西红柿
#define SEED_PUMPIN "seed_pumpkin"   //南瓜
#define SEED_EGGPLANT "seed_eggplant"  //茄子

#define SEED_TREE "seed_tree"  //树苗


#define SEED_TREE_OAK "oak"  //橡树
#define SEED_TREE_PINE "pine" //松树
#define SEED_TREE_MAPLE "maple"  //枫树



//场景相关宏定义
#define SCENE_MANOR "scene_manor"
#define SCENE_SPRING_TOWN "spring_town"
#define SCENE_SUMMER_TOWN "summer_town"
#define SCENE_AUTUMN_TOWN "autumn_town"
#define SCENE_WINTER_TOWN "winter_town"
#define SCENE_BEACH "scene_beach"
#define SCENE_HOME "scene_home"
#define SCENE_MINE "scene_mine"

#define OBJECT_LAYER "ObjectLayer"
#define PLOUGH_LAYER "PloughLayer"
#define DROP_LAYER "DropLayer"
#define PLAYER_CONTROLER "Player_cintrol_layer"
/* 全局层相关宏定义 */

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

//小镇场景相关宏定义
#define TOWN_SMALL_SCALE 3.5f
#define MANOR_TO_TOWN_X 0
#define MANOR_TO_TOWN_Y 27

//矿洞场景相关宏定义
#define MINE_SMALL_SCALE 3.5f
#define MANOR_TO_MINE_X 0
#define MANOR_TO_MINE_Y 0

//家场景相关宏定义
#define HOME_SMALL_SCALE 4.0f
#define MANOR_TO_HOME_X 0
#define MANOR_TO_HOME_Y 0

//扣血相关宏定义
#define ATTACK_LEVEL_ONE 25
#define ATTACK_LEVEL_TWO 50


// 定义每个季节的持续天数
#define SEASON_LENGTH 28  // 每个季节持续28天

// 更新时间的间隔为 1 秒
#define UPDATE_INTERVAL 0.01f 

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

#define DROPS_SCALE 0.6f

// 矿洞中生成石头的数量
#define STONE_GENERATE_NUM 20

// 定义每种 StoneType 的权重（概率）
extern std::map<StoneType, int> stoneTypeWeights;


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
#define LAND_DESTORY_THRESHOLD 5

// 树生长天数阈值
#define TREE_GROWTH_THRESHOLD 5

// 定义农作物的种类枚举
enum class CropsType {
    // 春季
    Carrot,     // 胡萝卜
    Garlic,     // 大蒜
    Potato,     // 土豆
    // 夏季
    Corn,       // 玉米
    Melon,      // 甜瓜
    Tomato,     // 西红柿
    // 秋季
    Cabbage,    // 小白菜
    Eggplant,   // 茄子
    Pumpkin,    // 南瓜
    // 酸菜
    Withered
};


//待添加完善
const std::map<std::string, int> itemPrices = {
    /*工具全部价格为0*/
    {"hammer",0},
    {"axe",0},
    {"draft",0},
    {"kettle",0},
    {"fishing_pole",0},

    //物品有价格,必须是双斜杠，否则会报错
    {"carrat_drop",30},
};

// 人物拾取半径
#define PICK_RADIUS 2.0

// 树遮挡的判定范围
#define TREE_BLOCK_X 1
#define TREE_BLOCK_Y 6
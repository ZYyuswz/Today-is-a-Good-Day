/* ----- 实现树的相关功能 ----- */

#include "tree.h"
#include "Control\Time.h"

// 构造函数
Tree::Tree(TreeType type, Vec2 tilePosition, TreeStage st, Layer* objectLayer) {
    // 基本项目的初始化
    this->type = type;  // 初始化树种类
    this->tilePosition = tilePosition;  // 初始化树的坐标
    this->stage = st;  // 初始化树的阶段
    this->growthDays = 0;  // 初始化生长天数
    this->growthDays_threshold = 5;  // 默认生长天数阈值
    this->health = (stage == TreeStage::Sapling) ? 10 : 100;  // 初始化血量

    // 加载纹理图集（只需要加载一次）
    auto spriteFrameCache = SpriteFrameCache::getInstance();
    spriteFrameCache->addSpriteFramesWithFile("res/Tree/tree.plist");

    // 创建初始贴图
    updateSpriteBySeason();
    if (!this->getTexture()) {
        CCLOG("Failed to load tree sprite!");
    }

    // 获取瓦片的像素坐标（瓦片中心）
    const Size tileSize = Size(TILESIZE, TILESIZE);  // 瓦片尺寸
    const Size mapSize = Size(GENERALMAPSIZE, GENERALMAPSIZE);  // 瓦片地图的尺寸
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);

    // 设置精灵的位置
    this->setPosition(pixelPosition);

    // 设置精灵的锚点为底部中心 (0.5, 0)
    this->setAnchorPoint(Vec2(0.5f, 0.0f));

    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

// 更新生长天数（增加一天，并可能改变阶段）
void Tree::updateStatus() {
    if (stage == TreeStage::Mature)
        return;
    growthDays++;
    if (growthDays >= growthDays_threshold) {
        health = 100;
        stage = TreeStage::Mature;
        growToMature();
    }
}

// 树长大，替换贴图sprite
void Tree::growToMature() {
    if (this->getTexture()) {
        updateSpriteBySeason();
    }
}

// 播放被砍的动画 同时生成掉落物
void Tree::playChopAnimation() {
    // 动作序列
    auto chopAction = Sequence::create(
        RotateBy::create(0.5f, 90),
        FadeOut::create(0.5f),
        CallFunc::create([this]() {
            // 动画结束后移除树的精灵
            this->removeFromParent();
            }),
        nullptr
    );
    this->runAction(chopAction);

    // 产生掉落物
    generateDrops();
}

// 生成掉落物
void Tree::generateDrops() {
    // 获取当前运行的场景
    auto scene = Director::getInstance()->getRunningScene();
    if (!scene) {
        CCLOG("No running scene found!");
        return;
    }
    // 检查场景中是否存在掉落物层
    auto dropLayer = scene->getChildByName("DropLayer");
    if (!dropLayer) {
        // 如果不存在，创建一个新的掉落物层
        dropLayer = Layer::create();
        dropLayer->setName("DropLayer");
        scene->addChild(dropLayer);
    }
    // 创建掉落物
    auto treeDrop = new TreeDrop(tilePosition, 5, dropLayer);  // 使用树的瓦片坐标作为掉落物的生成位置
    treeDrop->generate();                                     // 生成掉落物
}

// 判断树是否存活
bool Tree::isAlive() const {
    return health > 0;
}

// 减少血量
void Tree::reduceHealth(int damage) {
    health -= damage;
    if (!isAlive()) {
        // 播放动画
        playChopAnimation();
    }
}

// 更新树的贴图
void Tree::updateSpriteBySeason() {
    // 获取当前季节
    Season current_season = GameTime::getInstance()->getSeason();

    // 根据树种类和阶段，设置不同的贴图
    if (stage == TreeStage::Sapling) {
        // 树苗阶段的贴图在所有季节都是相同的
        switch (current_season) {
            case Season::Spring:
                this->setSpriteFrame("sapling_spring.png");
                break;
            case Season::Summer:
                this->setSpriteFrame("sapling_summer.png");
                break;
            case Season::Autumn:
                this->setSpriteFrame("sapling_autumn.png");
                break;
            case Season::Winter:
                this->setSpriteFrame("sapling_winter.png");
                break;
            default:
                break;
        }
    }
    else {
        // 成熟阶段的贴图根据当前季节变化
        std::string season_suffix;
        switch (current_season) {
            case Season::Spring:
                season_suffix = "spring";
                break;
            case Season::Summer:
                season_suffix = "summer";
                break;
            case Season::Autumn:
                season_suffix = "autumn";
                break;
            case Season::Winter:
                season_suffix = "winter";
                break;
            default:
                break;
        }

        std::string sprite_name;
        switch (type) {
            case TreeType::Oak:
                sprite_name = "oak_mature_" + season_suffix + ".png";
                break;
            case TreeType::Pine:
                sprite_name = "pine_mature_" + season_suffix + ".png";
                break;
            case TreeType::Maple:
                sprite_name = "maple_mature_" + season_suffix + ".png";
                break;
            default:
                break;
        }

        if (!sprite_name.empty()) {
            this->setSpriteFrame(sprite_name);
        }
    }
}

/* ----- 实现树的相关功能 ----- */

#include "tree.h"
#include "Control\Time.h"

// 构造函数
Tree::Tree(TMXTiledMap* tileMap, Vec2 tile, Layer* objectLayer, TreeType ty, Stage st){
    // 基本项目的初始化
    this->type = ty;  // 初始化树种类
    this->tilePosition = tile;  // 初始化树的坐标
    this->stage = st;  // 初始化树的阶段
    this->growthDays = 0;  // 初始化生长天数
    this->growthDaysThreshold = 5;  // 默认生长天数阈值
    this->health = (stage == Stage::Childhood) ? 10 : 100;  // 初始化血量

    // 加载纹理图集（只需要加载一次）
    //auto spriteFrameCache = SpriteFrameCache::getInstance();
    //spriteFrameCache->addSpriteFramesWithFile("res/Tree/tree.plist");

    // 创建初始贴图
    updateSpriteBySeason();
    if (!this->getTexture()) {
        CCLOG("Failed to load tree sprite!");
    }

    // 获取树木的像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);

    // 设置精灵的位置
    this->setPosition(pixelPosition);

    // 设置精灵的锚点为底部中心 (0.5, 0)
    this->setAnchorPoint(Vec2(0.5f, 0.0f));

    // 将精灵添加到物体层
    objectLayer->addChild(this);
}


// 树长大，替换贴图sprite
void Tree::growToMature() {
    if (this->getTexture()) {
        updateSpriteBySeason();
    }
}

// 播放被砍的动画 同时生成掉落物
void Tree::deathAnimation() {
    // 动作序列
    auto chopAction = Sequence::create(
        RotateBy::create(1.0f, 90),
        FadeOut::create(1.0f),
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
    // 检查场景中是否存在掉落物层，并确保它是 Layer 类型
    auto dropLayer = dynamic_cast<Layer*>(scene->getChildByName("DropLayer"));
    if (!dropLayer) {
        // 如果不存在，创建一个新的掉落物层
        dropLayer = Layer::create();
        dropLayer->setName("DropLayer");
        scene->addChild(dropLayer);
    }
    // 创建掉落物
    auto treeDrop = new TreeDrop(tilePosition, dropLayer);  // 使用树的瓦片坐标作为掉落物的生成位置
    treeDrop->generate();                                     // 生成掉落物
}

// 更新树的贴图
void Tree::updateSpriteBySeason() {
    // 获取当前季节
    Season current_season = GameTime::getInstance()->getSeason();

    // 根据树种类和阶段，设置不同的贴图
    if (stage == Stage::Childhood) {
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

// 在瓦片地图上随机生成 num 个树苗
void Tree::randomGenerate(int num, TMXTiledMap* tileMap, Layer* objectLayer) {
    // 获取瓦片地图的 floor 层
    auto floorLayer = tileMap->getLayer("floor");
    if (!floorLayer) {
        CCLOG("Error: 'floor' layer not found in tile map!");
        return;
    }

    // 获取瓦片地图的尺寸
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();

    // 随机数生成器
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> treeTypeDist(0, 2);  // 3种树：0 - Oak, 1 - Pine, 2 - Birch
    int maxRetries = 100;  // 最大重试次数，防止死循环

    // 随机生成 num 个树苗
    for (int i = 0; i < num;) {  // 只有成功生成时才会增加 i
        // 随机选择一个瓦片坐标
        int tileX = rand() % static_cast<int>(mapSize.width);
        int tileY = rand() % static_cast<int>(mapSize.height);

        // 检查瓦片是否属于 floor 层（即瓦片 GID 不为 0）
        if (floorLayer->getTileGIDAt(Vec2(tileX, tileY)) == 0) {
            // 如果瓦片为空，跳过当前循环，重新选择瓦片
            continue;
        }

        // 检查该位置是否已有精灵
        bool isValidTile = true;
        auto existingSprites = objectLayer->getChildren();
        // 遍历物体层的所有物体，看他的坐标和现在坐标是否相等
        for (auto sprite : existingSprites) {
            if (sprite->getPosition() == Vec2(tileX * tileSize.width, tileY * tileSize.height)) {
                isValidTile = false;  // 该位置已有精灵，无法生成树苗
                break;
            }
        }

        // 如果该瓦片有效且位置无精灵，则生成树苗
        if (isValidTile) {
            // 随机选择树的种类
            TreeType treeType = static_cast<TreeType>(treeTypeDist(gen));  // 随机生成树种类
            // 生成树苗
            auto sapling = new Tree(tileMap, Vec2(tileX, tileY), objectLayer, treeType, Stage::Childhood);
            objectLayer->addChild(sapling);  // 将树苗添加到 objectLayer 中
            // 增加成功生成的树苗数量
            i++;
        }

        // 如果重试次数超过最大重试次数，退出循环避免死循环
        if (--maxRetries <= 0) {
            CCLOG("Max retries reached, exiting tree generation.");
            break;
        }
    }
}
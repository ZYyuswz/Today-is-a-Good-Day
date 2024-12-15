#include "Crops.h"

// 生长
void Crops::update() {
    // 获取当前季节
    Season current_season = GameTime::getInstance()->getSeason();
    // 如果当前季节与作物季节不匹配
    if (current_season != cropsSeason) {
        // 获取 ObjectLayer
        auto objectLayer = dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByName("ObjectLayer"));
        if (!objectLayer) {
            CCLOG("ObjectLayer not found in the scene!");
            return;
        }
        // 销毁变成酸菜
        auto temp = new Withered(pMap, objectLayer, tilePosition, Stage::Childhood);
        if (temp) {
            objectLayer->addChild(temp); // 确保酸菜对象被添加到层中
        }
        this->removeFromParent(); // 移除当前对象
        return; // 提前返回，避免继续执行生长逻辑
    }
    // 如果季节匹配，继续生长
    growthDays++;
    // 检查是否需要更新阶段
    for (size_t i = 0; i < growthStageThreshold.size(); ++i) {
        if (growthDays == growthStageThreshold[i]) {
            stage = static_cast<Stage>(i + 1);  // 更新阶段
            this->setSpriteFrame(stageImages[i]);
            break;
        }
    }
}

// 死亡动画
void Crops::deathAnimation() {
    // 播放碎裂动画
    auto chopAction = Sequence::create(
        FadeOut::create(0.5f),
        nullptr
    );
    this->runAction(chopAction);
}

// 生成掉落物
void Crops::generateDrops() {
    // 酸菜直接返回
    if (type == CropsType::Withered)
        return;
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
    auto cropsDrop = new CropsDrop(tilePosition, dropLayer, type);  // 使用树的瓦片坐标作为掉落物的生成位置
    cropsDrop->generate();                                          // 生成掉落物
}

// 酸菜
Withered::Withered(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st){
    this->tilePosition = tile;
    this->stage = st;
    type = CropsType::Withered;  // 设置作物类型
    this->setSpriteFrame("withered.png");
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

// 胡萝卜类
Carrot::Carrot(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st){
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Spring;
    this->type = CropsType::Carrot;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "carrot_1.png";  // 阶段 1 图片路径
    stageImages[1] = "carrot_2.png";  // 阶段 2 图片路径
    stageImages[2] = "carrot_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 3, 5 };  // 生长阶段阈值
    // 贴图
    this->setSpriteFrame(stageImages[0]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.5f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}


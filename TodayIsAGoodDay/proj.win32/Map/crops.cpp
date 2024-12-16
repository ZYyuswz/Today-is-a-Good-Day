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
    // 如果季节匹配，且耕地浇水，继续生长 
    // 获取 ObjectLayer
    auto ploughLayer = dynamic_cast<Layer*>(Director::getInstance()->getRunningScene()->getChildByName("PloughLayer"));
    if (!ploughLayer) {
        CCLOG("PloughLayer not found in the scene!");
        return;
    }
    // 遍历 PloughLayer 的子节点，找到坐标为 tilePosition 的耕地
    bool isWatered = false;
    bool isFertilized = false;
    for (auto child : ploughLayer->getChildren()) {
        auto plough = dynamic_cast<Plough*>(child);  // 假设 Plough 是耕地对象的类
        if (plough && plough->getTilePosition() == tilePosition) {
            // 检查耕地状态
            LandState landState = plough->getState();
            if (landState == LandState::Watered || landState == LandState::FertilizedWatered) {
                isWatered = true;
            }
            if (landState == LandState::Fertilized || landState == LandState::FertilizedWatered) {
                isFertilized = true;
            }
            break;
        }
    }
    // 如果耕地已浇水，作物继续生长
    if (isWatered) {
        if (isFertilized) {
            // 如果施肥，生长天数增加 2
            growthDays += 2;
            CCLOG("Crop grows faster due to fertilization! Growth days += 2.");
        }
        else {
            // 如果只浇水，生长天数增加 1
            growthDays++;
            CCLOG("Crop grows normally. Growth days += 1.");
        }
        // 检查是否需要更新阶段
        for (size_t i = 0; i < growthStageThreshold.size(); ++i) {
            if (growthDays >= growthStageThreshold[i]) {
                stage = static_cast<Stage>(i + 1);  // 更新阶段
                this->setSpriteFrame(stageImages[i]);
                CCLOG("Crop stage updated to stage %d.", stage);
                break;
            }
        }
    }
}

// 收获
void Crops::harvest() {
    if (stage == Stage::Mature) {
        deathAnimation();// 死亡动画
        this->removeFromParent(); // 移除
        generateDrops(); // 产生掉落物
    }
}

// 减少血量
void Crops::reduceHealth(int damage) {
    health -= damage;
    if (health <= 0) {
        // 物体被摧毁
        deathAnimation();// 死亡动画
        // 生产掉落物
        generateDrops();
        this->removeFromParent(); // 移除
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
    auto cropsDrop = new CropsDrop(tilePosition, dropLayer, type, tileMap);  // 使用树的瓦片坐标作为掉落物的生成位置
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
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
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
    if(stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Garlic::Garlic(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Spring;
    this->type = CropsType::Garlic;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "garlic_1.png";  // 阶段 1 图片路径
    stageImages[1] = "garlic_2.png";  // 阶段 2 图片路径
    stageImages[2] = "garlic_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 4, 7 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Potato::Potato(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Spring;
    this->type = CropsType::Potato;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "potato_1.png";  // 阶段 1 图片路径
    stageImages[1] = "potato_2.png";  // 阶段 2 图片路径
    stageImages[2] = "potato_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 3, 5 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Corn::Corn(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Summer;
    this->type = CropsType::Corn;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "corn_1.png";  // 阶段 1 图片路径
    stageImages[1] = "corn_2.png";  // 阶段 2 图片路径
    stageImages[2] = "corn_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 5, 8 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Melon::Melon(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Summer;
    this->type = CropsType::Melon;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "melon_1.png";  // 阶段 1 图片路径
    stageImages[1] = "melon_2.png";  // 阶段 2 图片路径
    stageImages[2] = "melon_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 7, 12 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Tomato::Tomato(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Summer;
    this->type = CropsType::Tomato;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "tomato_1.png";  // 阶段 1 图片路径
    stageImages[1] = "tomato_2.png";  // 阶段 2 图片路径
    stageImages[2] = "tomato_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 4, 7 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Cabbage::Cabbage(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Autumn;
    this->type = CropsType::Cabbage;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "cabbage_1.png";  // 阶段 1 图片路径
    stageImages[1] = "cabbage_2.png";  // 阶段 2 图片路径
    stageImages[2] = "cabbage_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 3, 5 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Eggplant::Eggplant(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Autumn;
    this->type = CropsType::Eggplant;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "eggplant_1.png";  // 阶段 1 图片路径
    stageImages[1] = "eggplant_2.png";  // 阶段 2 图片路径
    stageImages[2] = "eggplant_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 6, 9 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}

Pumpkin::Pumpkin(TMXTiledMap* tileMap, Layer* objectLayer, Vec2 tile, Stage st) {
    this->tilePosition = tile;
    this->stage = st;
    this->cropsSeason = Season::Autumn;
    this->type = CropsType::Pumpkin;  // 设置作物类型
    this->pMap = tileMap;
    stageImages[0] = "pumpkin_1.png";  // 阶段 1 图片路径
    stageImages[1] = "pumpkin_2.png";  // 阶段 2 图片路径
    stageImages[2] = "pumpkin_3.png";  // 阶段 3 图片路径
    growthStageThreshold = { 0, 5, 8 };  // 生长阶段阈值
    // 贴图
    if (stage == Stage::Childhood)
        this->setSpriteFrame(stageImages[0]);
    else if (stage == Stage::Growth)
        this->setSpriteFrame(stageImages[1]);
    else
        this->setSpriteFrame(stageImages[2]);
    if (!this->getTexture()) {
        CCLOG("Failed to load sprite!");
    }
    // 获取像素坐标
    const Size mapSize = tileMap->getMapSize();
    const Size tileSize = tileMap->getTileSize();
    Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::BOTTOM_CENTER);
    // 将精灵的图像上下颠倒
    this->setFlippedY(false);
    // 设置精灵的锚点为底部中心
    this->setAnchorPoint(Vec2(0.5f, 0.0f));
    // 设置精灵的位置
    this->setPosition(pixelPosition);
    // 将精灵添加到物体层
    objectLayer->addChild(this);
}
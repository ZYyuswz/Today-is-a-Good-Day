/* ----- 实现石头的相关功能 ----- */
#include "stone.h"

// 构造函数
Stone::Stone(TMXTiledMap* tileMap, Layer* objectLayer, const Vec2& tile, StoneType ty) {
	// 基本初始化
	this->tilePosition = tile;
	this->type = ty;
	// 根据类别初始化
	switch (type)
	{
		case StoneType::Stone:
			this->setSpriteFrame("stonee.png");
			break;
		case StoneType::Copper:
			this->setSpriteFrame("copper.png");
			break;
		case StoneType::Silver:
			this->setSpriteFrame("silver.png");
			break;
		case StoneType::Gold:
			this->setSpriteFrame("gold.png");
			break;
		case StoneType::Coal:
			this->setSpriteFrame("coal.png");
			break;
		default:
			break;
	}
	// 获取石头的像素坐标
	const Size mapSize = tileMap->getMapSize();
	const Size tileSize = tileMap->getTileSize();
	Vec2 pixelPosition = getTilePixelPosition(tilePosition, tileSize, mapSize, TileCorner::CENTER);
	// 将精灵的图像上下颠倒
	this->setFlippedY(false);
	// 设置石头的位置
	this->setPosition(pixelPosition);
	// 设置石头的锚点为中心
	this->setAnchorPoint(Vec2(0.5f, 0.5f));
	// 将石头添加到物体层
	objectLayer->addChild(this);
}

// 死亡动画
void Stone::deathAnimation(){
	// 播放碎裂动画
	auto fadeOut = FadeOut::create(1.0f);
	// 产生掉落物
	generateDrops();
}

void Stone::generateDrops() {
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
	auto stoneDrop = new StoneDrop(tilePosition, dropLayer, type);  // 使用树的瓦片坐标作为掉落物的生成位置
	stoneDrop->generate();
}

void Stone::randomGenerate(TMXTiledMap* tileMap, Layer* objectLayer, int num, StoneType type) {
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

	// 随机生成 num 个
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
				isValidTile = false;  // 该位置已有精灵，无法生成
				break;
			}
		}

		// 如果该瓦片有效且位置无精灵，则生成
		if (isValidTile) {
			auto stone = new Stone(tileMap, objectLayer, Vec2(tileX, tileY), type);
			// 增加成功生成的数量
			i++;
		}

		// 如果重试次数超过最大重试次数，退出循环避免死循环
		if (--maxRetries <= 0) {
			CCLOG("Max retries reached, exiting tree generation.");
			break;
		}
	}


}
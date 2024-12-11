/* ----- 实现石头的相关功能 ----- */
#include "stone.h"

// 构造函数
Stone::Stone(TMXTiledMap* tileMap, const Vec2& tile, Layer* objectLayer, StoneType ty) {
	// 基本初始化
	this->tilePosition = tile;
	this->type = ty;
	// 根据类别初始化
	switch (type)
	{
		case StoneType::Stone:
			this->setSpriteFrame("stone.png");
			break;
		case StoneType::Copper:
			this->setSpriteFrame("copper.png");
			break;
		case StoneType::Iron:
			this->setSpriteFrame("iron.png");
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
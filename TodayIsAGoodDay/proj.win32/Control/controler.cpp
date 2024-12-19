
#include"cocos2d.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"
#include"Person/person.h"
#include"global.h"
#include "Time.h"

USING_NS_CC;


//总控鼠标按键
//按下时的调用
void control_mouseclick()
{

}






//总控场景切换
//当人物移动到场景某位置时自动切换场景
void control_changescene()
{

}


/* ----------地图切换---------- */
void manor_change_map()
{
	Scene* currentscene = MapManager::getInstance()->getCurrentScene();
	TMXTiledMap* oldMap = MapManager::getInstance()->getCurrentMap();
	Season season = GameTime::getInstance()->getSeason();
	// 获取旧地图的所有子节点
	auto children = oldMap->getChildren();


	// 层名称列表
	std::vector<std::string> layerNames = { "ObjectLayer", "PloughLayer", "DropLayer" };


	if (season == Season::Spring)
	{
		auto scene_spring = TMXTiledMap::create("manor/spring.tmx"); // 替换为你的 .tmx 文件名
		// 遍历层名称列表
		for (const auto& layerName : layerNames) {
			// 获取旧地图的层
			Layer* layer = dynamic_cast<Layer*>(oldMap->getChildByName(layerName));
			if (!layer) {
				CCLOG("Layer %s not found in the old map!", layerName.c_str());
				continue;
			}

			// 从旧地图中移除层（但不销毁）
			oldMap->removeChild(layer, false);  // false 表示不销毁层

			// 将层添加到新地图
			scene_spring->addChild(layer);
		}

		
		
		int visiablemood = get_window_size();
		if (visiablemood == SMALL_WINDOW)
		{
			//设置图缩放比例
			scene_spring->setScale(SRING_MANOR_SMALL_SCALE);

			//获取当前屏幕大小
			Size screensize = Director::getInstance()->getVisibleSize();
			//设置进入的瓦片地图坐标
			Vec2 entrence = Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y);
			// 获取地图的尺寸  
			Size mapSize = scene_spring->getMapSize();
			Size tileSize = scene_spring->getTileSize();
			//设置进入的屏幕坐标
			Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_spring->getScale());

			//屏幕左下角
			Vec2 point_row;

			point_row.x = (screensize.width / 2) - screen_enterence.x;
			point_row.y = (screensize.height / 2) - screen_enterence.y;

			scene_spring->setAnchorPoint(Vec2(0, 0));
			scene_spring->setPosition(point_row);


		}
		
		// 添加新地图到场景中
		// 删除旧地图（可选）
		oldMap->removeFromParentAndCleanup(true);  // 删除旧地图并清理内存
		currentscene->addChild(scene_spring);

	}
	else if (season == Season::Autumn) {
		auto scene_spring = TMXTiledMap::create("manor/autumn.tmx"); // 替换为你的 .tmx 文件名
		// 遍历层名称列表
		for (const auto& layerName : layerNames) {
			// 获取旧地图的层
			Layer* layer = dynamic_cast<Layer*>(oldMap->getChildByName(layerName));
			if (!layer) {
				CCLOG("Layer %s not found in the old map!", layerName.c_str());
				continue;
			}

			// 从旧地图中移除层（但不销毁）
			oldMap->removeChild(layer, false);  // false 表示不销毁层

			// 将层添加到新地图
			scene_spring->addChild(layer);
		}



		int visiablemood = get_window_size();
		if (visiablemood == SMALL_WINDOW)
		{
			//设置图缩放比例
			scene_spring->setScale(SRING_MANOR_SMALL_SCALE);

			//获取当前屏幕大小
			Size screensize = Director::getInstance()->getVisibleSize();
			//设置进入的瓦片地图坐标
			Vec2 entrence = Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y);
			// 获取地图的尺寸  
			Size mapSize = scene_spring->getMapSize();
			Size tileSize = scene_spring->getTileSize();
			//设置进入的屏幕坐标
			Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_spring->getScale());

			//屏幕左下角
			Vec2 point_row;

			point_row.x = (screensize.width / 2) - screen_enterence.x;
			point_row.y = (screensize.height / 2) - screen_enterence.y;

			scene_spring->setAnchorPoint(Vec2(0, 0));
			scene_spring->setPosition(point_row);


		}

		// 添加新地图到场景中
		// 删除旧地图（可选）
		oldMap->removeFromParentAndCleanup(true);  // 删除旧地图并清理内存
		currentscene->addChild(scene_spring);
	}
	else if (season == Season::Winter) {
		auto scene_spring = TMXTiledMap::create("manor/winter.tmx"); // 替换为你的 .tmx 文件名
		// 遍历层名称列表
		for (const auto& layerName : layerNames) {
			// 获取旧地图的层
			Layer* layer = dynamic_cast<Layer*>(oldMap->getChildByName(layerName));
			if (!layer) {
				CCLOG("Layer %s not found in the old map!", layerName.c_str());
				continue;
			}

			// 从旧地图中移除层（但不销毁）
			oldMap->removeChild(layer, false);  // false 表示不销毁层

			// 将层添加到新地图
			scene_spring->addChild(layer);
		}



		int visiablemood = get_window_size();
		if (visiablemood == SMALL_WINDOW)
		{
			//设置图缩放比例
			scene_spring->setScale(SRING_MANOR_SMALL_SCALE);

			//获取当前屏幕大小
			Size screensize = Director::getInstance()->getVisibleSize();
			//设置进入的瓦片地图坐标
			Vec2 entrence = Vec2(SPRING_MANOR_ENTER_X, SPRING_MANOR_ENTER_Y);
			// 获取地图的尺寸  
			Size mapSize = scene_spring->getMapSize();
			Size tileSize = scene_spring->getTileSize();
			//设置进入的屏幕坐标
			Vec2 screen_enterence = tile_change_screen(mapSize, tileSize, entrence, scene_spring->getScale());

			//屏幕左下角
			Vec2 point_row;

			point_row.x = (screensize.width / 2) - screen_enterence.x;
			point_row.y = (screensize.height / 2) - screen_enterence.y;

			scene_spring->setAnchorPoint(Vec2(0, 0));
			scene_spring->setPosition(point_row);


		}

		// 添加新地图到场景中
		// 删除旧地图（可选）
		oldMap->removeFromParentAndCleanup(true);  // 删除旧地图并清理内存
		currentscene->addChild(scene_spring);
	}
	else
		return;
	return;
}




//总控背包

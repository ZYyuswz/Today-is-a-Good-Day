
#include"cocos2d.h"

#include "menu.h"
#include "definition.h"
#include "totaltools.h"
#include "scene.h"
#include "./Setting/setting.h"
#include"Person/person.h"
#include"global.h"
#include "Time.h"
#include "Map/tree.h"
#include"Map/sundry.h"
USING_NS_CC;


//总控鼠标按键
//按下时的调用
void control_mouseclick(Vec2 mouse_pos)
{
	//鼠标瓦片坐标
	Vec2 mouse_tile_pos;
	TMXTiledMap* currentMap = MapManager::getInstance()->getCurrentMap();
	if (currentMap)
	{
		CCLOG("Current map name: %s", currentMap->getMapSize().width);
	}
	else
	{
		CCLOG("No map found for the current scene.");
	}
	Vec2 map_position = currentMap->getPosition();
	mouse_tile_pos = convertWorldToTileCoord(mouse_pos, map_position);

	//得到人所在瓦片地图位置
	Vec2 person_tile_pos = leading_charactor.getTiledPosition();

	//判断点击位置和人物距离是不是合法
	if (abs(person_tile_pos.x - mouse_tile_pos.x) < MAX_PERSON_LENTH && abs(person_tile_pos.y - mouse_tile_pos.y) < MAX_PERSON_LENTH)
	{
		//如果合法
		//判断当前点击处有无精灵
		// 
		std::string currentscenename = Director::getInstance()->getRunningScene()->getName();
		if (currentscenename == SCENE_MANOR) {
			auto thing_on_map = getSpriteOnMap(mouse_tile_pos);


			std::string person_tool = "";

			Tool* current_tool = leading_charactor.getTool();
			if (current_tool != NULL) {
				//得到现在人手上的工具
				person_tool = leading_charactor.getTool()->getName();

			}
			else
				return;


			if (thing_on_map) {
				//判断人手上拿的是否合法
				if (person_tool == TOOL_AXE) {
					//如果手上是斧子
					//判断手上斧子的等级对应的扣血量
					int blood = ATTACK_LEVEL_ONE;

					auto have_tree = dynamic_cast<Tree*>(thing_on_map);
					if (have_tree) {
						//人物动画
						leading_charactor.useTools();
						have_tree->reduceHealth(blood);

					}
				}
				else if (person_tool == TOOL_HAMMER) {
					//if hammer
					int blood = ATTACK_LEVEL_ONE;

					auto have_stone = dynamic_cast<Stone*>(thing_on_map);
					if (have_stone) {
						//人物动画
						leading_charactor.useTools();
						have_stone->reduceHealth(blood);
					}
				}
				else if (person_tool == TOOL_FISHING_POLE) {
					//IF fishingpole

				}
				
			}
			else {

				bool is_plough = is_have_plough(mouse_tile_pos);
				if (is_plough) {
					if (person_tool == SEED_CABBAGE) {
						auto put_cabbage = currentMap->getChildByName(CROPS_LAYER);
						auto put_cabbage_layer = dynamic_cast<Layer*>(put_cabbage);
						auto cabbage1 = new Cabbage(currentMap, put_cabbage_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_CABBAGE));
						if (leading_charactor.MyBag.removeItem(item(SEED_CABBAGE)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_CARROT) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto carrot1 = new Carrot(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_CARROT));
						if (leading_charactor.MyBag.removeItem(item(SEED_CARROT)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_CORN) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto corn1 = new Corn(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_CORN));
						if (leading_charactor.MyBag.removeItem(item(SEED_CORN)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_EGGPLANT) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto eggplant1 = new Eggplant(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_EGGPLANT));
						if (leading_charactor.MyBag.removeItem(item(SEED_EGGPLANT)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_GARLIC) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto garlic1 = new Garlic(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_GARLIC));
						if (leading_charactor.MyBag.removeItem(item(SEED_GARLIC)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_MELON) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto melon1 = new Melon(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_MELON));
						if (leading_charactor.MyBag.removeItem(item(SEED_MELON)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_POTATO) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto potato1 = new Potato(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_POTATO));
						if (leading_charactor.MyBag.removeItem(item(SEED_POTATO)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_PUMPIN) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto pumkin1 = new Pumpkin(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_PUMPIN));
						if (leading_charactor.MyBag.removeItem(item(SEED_PUMPIN)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == SEED_TOMATO) {
						auto put = currentMap->getChildByName(CROPS_LAYER);
						auto put_layer = dynamic_cast<Layer*>(put);
						auto tomato1 = new Tomato(currentMap, put_layer, mouse_tile_pos);
						//leading_charactor.MyBag.removeItem(item(SEED_TOMATO));
						if (leading_charactor.MyBag.removeItem(item(SEED_TOMATO)) == 0) {
							delete leading_charactor.getTool();
							leading_charactor.setTool(nullptr);
						}
					}
					else if (person_tool == TOOL_KETTLE) {
						//if kattle
						extern Plough* getPloughOnMap(Vec2 tilePosition);
						auto item = getPloughOnMap(mouse_tile_pos);
						item->water();
						leading_charactor.useTools();

					}
				}
				else if (!is_plough) {
					if (person_tool == SEED_TREE) {

						auto put_tree = currentMap->getChildByName(OBJECT_LAYER);
						auto put_tree_layer = dynamic_cast<Layer*>(put_tree);
						auto tree1 = new Tree(currentMap, put_tree_layer, mouse_tile_pos, TreeType::Maple, Stage::Childhood);

					}
					else if (person_tool == TOOL_DRAFT) {
						//如果手上是锄头

						leading_charactor.useTools();
						auto put_plough = currentMap->getChildByName(PLOUGH_LAYER);
						auto put_plough_layer = dynamic_cast<Layer*>(put_plough);
						auto plough1 = new Plough(currentMap, put_plough_layer, mouse_tile_pos, LandState::Tilled);


					}
				}


			}




		}
		else if (currentscenename == SCENE_MINE) {
			auto thing_on_map = getSpriteOnMap(mouse_tile_pos);

			std::string person_tool;
			Tool* current_tool = leading_charactor.getTool();
			if (current_tool!=NULL) {
				//得到现在人手上的工具
				person_tool = leading_charactor.getTool()->getName();

			}
			else
				return;


			if (thing_on_map) {
				//判断人手上拿的是否合法
				if (person_tool == TOOL_AXE) {
					//如果手上是斧子
					//判断手上斧子的等级对应的扣血量
					int blood = ATTACK_LEVEL_ONE;

					auto have_tree = dynamic_cast<Tree*>(thing_on_map);
					if (have_tree) {
						//人物动画
						leading_charactor.useTools();
						have_tree->reduceHealth(blood);
					}
				}
				else if (person_tool == TOOL_HAMMER) {
					//if hammer
					int blood = ATTACK_LEVEL_ONE;

					auto have_stone = dynamic_cast<Stone*>(thing_on_map);
					if (have_stone) {
						//人物动画
						leading_charactor.useTools();
						have_stone->reduceHealth(blood);
					}
				}
			}
		}
		else if (currentscenename == SCENE_BEACH) {
			fishing();
		}
		



	}

}






//总控场景切换
//当人物移动到场景某位置时自动切换场景
void control_changescene()
{
	Vec2 player_pos = leading_charactor.getTiledPosition();
	std::string current_scene_name = Director::getInstance()->getRunningScene()->getName();
	if (current_scene_name == SCENE_MANOR) {
		if (player_pos.x > 60 && player_pos.y > 34) {
			//庄园去小镇
			manor_to_towm();
		}
		else if (player_pos.x > 30 && player_pos.y > 60 && player_pos.x < 36)
		{
			//庄园去矿洞
			change_to_mine();
		}
		else if (player_pos.x > 43 && player_pos.x < 45 && player_pos.y > 42 && player_pos.y < 45) {
			change_to_home();
		}
		

	}
	else if (current_scene_name == SCENE_SPRING_TOWN || current_scene_name == SCENE_SUMMER_TOWN || current_scene_name == SCENE_AUTUMN_TOWN || current_scene_name == SCENE_WINTER_TOWN) {
		if (player_pos.x < 4 && player_pos.y > 24 && player_pos.y < 30) {
			//回小镇
			back_to_manor_from_town();

		}
		else if (player_pos.x > 25 && player_pos.x < 35 && player_pos.y > 0 && player_pos.y < 6)
		{
			//去沙滩
			change_to_beach();
		}
		else if (player_pos.x > 10 && player_pos.x < 13 && player_pos.y > 12 && player_pos.y < 17) {
			change_to_store();
		}
	}
	else if (current_scene_name == SCENE_MINE) {
		//回庄园
		if (player_pos.x >= 4 && player_pos.x <= 6 && player_pos.y > 15 && player_pos.y < 20) {
			back_to_manor_from_mine();
		}
		else if (player_pos.x >= 26 && player_pos.x <= 28 && player_pos.y >= 4 && player_pos.y <= 6)
		{
			change_to_mine();
		}
		//back_to_manor_from_mine();

	}
	else if (current_scene_name == SCENE_BEACH) {
		if (player_pos.x >= 22 && player_pos.x <= 28 && player_pos.y > 60 && player_pos.y < 70) {
			back_to_manor_from_home();
		}

	}
	else if (current_scene_name == SCENE_HOME)
	{
		if (player_pos.x >= 14 && player_pos.x <= 17 && player_pos.y > 2 && player_pos.y < 5) {
			back_to_manor_from_home();
		}
	}
	else if (current_scene_name == SCENE_STORE) {
		if (player_pos.x >= 6 && player_pos.x <= 9 && player_pos.y >= 0 && player_pos.y <= 3) {
			back_to_manor_from_home();
		}
	}

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



/*工具：返回鼠标点击坐标的plough的指针，如果没有为nullptr
* 传入参数：
* Vec2 tilePosition：鼠标点击的坐标
* 返回值：
* Plough*：基类指针
*/
Plough* getPloughOnMap(Vec2 tilePosition) {
	//得到当前地图
	auto map = MapManager::getInstance()->getCurrentMap();
	if (!map) {
		CCLOG("Map not found in the scene!-getPloughOnMap");
		return nullptr;
	}
	// 获取 ploughLayer
	auto ploughLayer = dynamic_cast<Layer*>(map->getChildByName("PloughLayer"));
	if (!ploughLayer) {
		CCLOG("ObjectLayer not found in the map!-getPloughOnMap");
		return nullptr;
	}
	// 遍历 ObjectLayer 的子节点
	for (auto child : ploughLayer->getChildren()) {
		// 检查子节点是否是 Plough 类的实例
		Plough* plough = dynamic_cast<Plough*>(child);
		if (plough && plough->getTilePosition() == tilePosition) {
			return plough;
		}
	}
	return nullptr;
}

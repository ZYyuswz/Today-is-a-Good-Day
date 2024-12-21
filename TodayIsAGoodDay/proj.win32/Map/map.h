/* ----- 该文件夹主cpp ----- */
/* 详细内容参阅开发者手册 */

#pragma once
#include "cocos2d.h"
#include "definition.h"

USING_NS_CC;


/**
 * @brief 获取瓦片指定角落的像素坐标。
 * @param tileCoord 瓦片的行列坐标（左上角为原点）。
 * @param tileSize 瓦片的像素宽高尺寸。
 * @param mapSize 地图的瓦片行列数。
 * @param corner 需要获取的角落类型（TOP_LEFT, BOTTOM_LEFT, TOP_RIGHT, BOTTOM_RIGHT）。
 * @return 指定角落的像素坐标。
 */
Vec2 getTilePixelPosition(const Vec2& tileCoord,const Size& tileSize, const Size& mapSize, TileCorner corner = CENTER); 
/* ----- 对整个项目均适用的工具集 ----- */

#include "cocos2d.h"
#include "totaltools.h"

USING_NS_CC;

//工具：瓦片地图坐标转换成屏幕像素坐标
/* 传入参数：
*  mapsize: size类型， 通过tileMap->getMapSize()方法获得当前地图大小
*  tilesize： size类型 ，通过tileMap->getTileSize()方法获得每个图块的大小
*  scale: float类型， 是最底层地图的缩放比例，可通过scale = tileMap ->getScale()方法获得，缺省为原地图大小为1.0f
* （其中，tilemap是自己的tmx图片名）
* 返回值：
* vec2类型：转换后在屏幕的坐标
*/
Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original,float scale = 1.0f)
{
	float x = original.x * tilesize.width;
	float y = original.y * tilesize.height;
	Vec2 screenpos = Vec2(x, y);
	screenpos = screenpos * scale;
	return screenpos;
}
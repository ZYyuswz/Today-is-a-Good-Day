/* ----- 对整个项目均适用的工具集 ----- */

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


//工具：将鼠标点击的位置转化成瓦片坐标
/* 传入参数：
*  const Vec2& worldPosition：鼠标点击位置的屏幕像素坐标
*  const Vec2& Tiledposition： 屏幕锚点的像素坐标
* 返回值：
* vec2类型：瓦片坐标
*/
Vec2 convertWorldToTileCoord(const Vec2& worldPosition, const Vec2& Tiledposition) {
    // 计算屏幕坐标与瓦片地图位置的差值
    Vec2 ScreenGap = worldPosition - Tiledposition;

    // 将差值转换为瓦片坐标
    Vec2 TiledGap = ScreenGap / (BEACH_SMALL_SCALE * TILESIZE);

    // 将结果转换为 int
    int tileX = static_cast<int>(TiledGap.x);
    int tileY = static_cast<int>(TiledGap.y);

    return Vec2(tileX, tileY);
}
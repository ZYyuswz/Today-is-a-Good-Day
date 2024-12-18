/* ----- 对整个项目均适用的工具集 ----- */

#include "totaltools.h"
#include <random>
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
*  const Vec2& mousePos：鼠标点击位置的屏幕像素坐标
*  const Vec2& mapCenter： 屏幕中心位置的瓦片坐标
*  float scale： 缩放比例
* 返回值：
* vec2类型：瓦片坐标
*/
Vec2 screenToTileCoords(const Vec2& mousePos, const Vec2& mapCenter, float scale)
{
	// 先计算鼠标点击坐标相对于屏幕中心坐标的位置
	Vec2 delta_pixel = (mousePos - mapCenter * TILESIZE) / scale;// 考虑缩放比例
	// 计算瓦片坐标
	int tileX = mapCenter.x + static_cast<int>(delta_pixel.x / TILESIZE);
	int tileY = mapCenter.y + static_cast<int>(delta_pixel.y / TILESIZE);
	// 检查余数，向上取整
	if (static_cast<int>(delta_pixel.x) % static_cast<int>(TILESIZE) != 0)
	{
		tileX += 1; // 向上取整
	}
	if (static_cast<int>(delta_pixel.y) % static_cast<int>(TILESIZE) != 0)
	{
		tileY += 1; // 向上取整
	}
	return Vec2(tileX, tileY);
}

/*工具：随机生成一组伯努利分布的离散变量
* 传入参数：
* double p 生成1的概率
* 返回值：
* 随机生成的一个bool值
*/
bool random_bernoulli(double p) {
	// 创建一个随机数生成器
	static std::random_device rd;  // 用于获取随机种子
	static std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
	std::bernoulli_distribution dist(p); // 创建一个伯努利分布，概率为p

	// 返回一个服从伯努利分布的随机数
	return dist(gen);
}

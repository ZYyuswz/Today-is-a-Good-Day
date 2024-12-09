/* ----- 该文件夹主cpp ----- */
/* 详细内容参阅开发者手册 */
#include "map.h"

Vec2 getTilePixelPosition(const Vec2& tileCoord, const Size& tileSize, const Size& mapSize, TileCorner corner)
{
    // 计算瓦片中心的像素坐标
    // 这样计算的是左下角的坐标
    const float x = tileCoord.x * tileSize.width;
    const float y = (mapSize.height - tileCoord.y - 1) * tileSize.height; // 注意y轴方向

    // 根据角点类型调整
    switch (corner) {
        case TOP_LEFT:
            return Vec2(x, y + tileSize.height); // 左上角
        case BOTTOM_LEFT:
            return Vec2(x, y); // 左下角
        case TOP_RIGHT:
            return Vec2(x + tileSize.width, y + tileSize.height); // 右上角
        case BOTTOM_RIGHT:
            return Vec2(x + tileSize.width, y); // 右下角
        default:
            // 瓦片中心
            return Vec2(x + tileSize.width / 2, y + tileSize.height / 2);
    }
}
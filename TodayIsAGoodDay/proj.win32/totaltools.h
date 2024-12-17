#pragma once
#include "cocos2d.h"
#include "definition.h"
USING_NS_CC;

Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original, float scale);

Vec2 screenToTileCoords(const Vec2& mousePos, const Vec2& mapCenter, float scale);
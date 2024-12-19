#pragma once
#include "cocos2d.h"
#include "definition.h"
USING_NS_CC;

Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original, float scale);

Vec2 convertWorldToTileCoord(const Vec2& worldPosition, const Vec2& Tiledposition);


bool random_bernoulli(double p);

void people_remove_change();

void people_change_scene(const Vec2 change_Vec2);


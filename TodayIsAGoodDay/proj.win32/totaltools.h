#pragma once
#include "cocos2d.h"
#include "definition.h"
#include "global.h"
#include "map/object.h"
#include "map/drop.h"

USING_NS_CC;

Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original, float scale);

Vec2 convertWorldToTileCoord(const Vec2& worldPosition, const Vec2& Tiledposition);

bool random_bernoulli(double p);

MyObject* getSpriteOnMap(Vec2 tilePosition);
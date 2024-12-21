#pragma once
#include "cocos2d.h"
#include "definition.h"
#include "global.h"

#include "Map/object.h"
#include "Map/drop.h"
#include "Map/tree.h"
#include "Map/plough.h"


USING_NS_CC;

Vec2 tile_change_screen(Size mapsize, Size tilesize, Vec2 original, float scale);

Vec2 convertWorldToTileCoord(const Vec2& worldPosition, const Vec2& Tiledposition);

bool random_bernoulli(double p);

MyObject* getSpriteOnMap(Vec2 tilePosition);

void people_remove_change();

void people_change_scene(const Vec2 change_Vec2);

std::vector<Dropper*>* getDrops(Vec2 personPosition);

void treeBlock(Vec2 personPosition);

void updateTreeBlock(Vec2 personPosition);

bool is_have_plough(Vec2 tilePosition);

bool is_have_object(Vec2 tilePosition);

bool isFiveTool(const std::string& name);

void harvest(Vec2 tilePosition);

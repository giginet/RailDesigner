//
//  Stage.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "Stage.h"
#include "define.h"

USING_NS_CC;

Stage::Stage()
: _tileNode(nullptr)
{
}

Stage::~Stage()
{
    CC_SAFE_RELEASE_NULL(_tileNode);
}

bool Stage::init()
{
    if (!cocos2d::Node::init()) {
        return false;
    }
    const int NUMBER_OF_ROADS = 4;
    for (int i = 0; i < NUMBER_OF_ROADS; ++i) {
        auto road = cocos2d::Sprite::create("road.png");
        auto x = i * (TILE_WIDTH + ROAD_WIDTH) + ROAD_WIDTH / 2.0;
        ;
        road->setPosition(x, 180);
        this->addChild(road);
    }
    this->setPosition(STAGE_MARGIN_X, 120);
    
    auto tileNode = cocos2d::Node::create();
    this->setTileNode(tileNode);
    this->addChild(tileNode);
    
    /*for (int x = 0; x < 3; ++x) {
     for (int y = 0; y < 10; ++y) {
     auto tile = RailTile::create();
     tileNode->addChild(tile);
     tile->setGridPos(cocos2d::Vec2(x, y));
     tile->adjustPosition();
     }
     }*/
    
    return true;
}

RailTile * Stage::getTileAt(int x, int y)
{
    for (auto& tile : _tiles) {
        auto gp = tile->getGridPos();
        if (gp.x == x && gp.y == y) {
            return tile;
        }
    }
    return nullptr;
}

void Stage::removeTileAt(int x, int y)
{
    auto tile = this->getTileAt(x, y);
    if (tile) {
        tile->removeFromParent();
        _tiles.eraseObject(tile);
    }
}

void Stage::addTile(RailTile *tile)
{
    auto gp = tile->getGridPos();
    if (tile->isValid()) {
        _tiles.pushBack(tile);
        this->addChild(tile);
        return;
    }
    assert("Grid point of the tile is invalid in Stage::addTile.");
}

bool Stage::isExistTile(int x, int y)
{
    return this->getTileAt(x, y) != nullptr;
}

cocos2d::Vec2 Stage::convertToGridSpace(cocos2d::Vec2 worldSpace)
{
    auto nodeSpace = this->convertToNodeSpace(worldSpace);
    auto gridY = floorf((nodeSpace.y + TILE_HEIGHT / 2.0) / TILE_HEIGHT);
    if (gridY >= 0) {
        for (int x = 0; x < 3; ++x) {
            auto boundLeft = (1 + x) * ROAD_WIDTH + x * TILE_WIDTH;
            auto boundRight = boundLeft + TILE_WIDTH;
            if (boundLeft <= nodeSpace.x && nodeSpace.x < boundRight) {
                return cocos2d::Vec2(x, gridY);
            }
        }
    }
    return cocos2d::Vec2(-1, -1);
}
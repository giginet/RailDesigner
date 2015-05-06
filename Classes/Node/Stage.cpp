//
//  Stage.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "Stage.h"
#include "define.h"

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
    
    for (int x = 0; x < 3; ++x) {
        for (int y = 0; y < 10; ++y) {
            auto tile = Tile::create();
            tileNode->addChild(tile);
            tile->setGridPos(cocos2d::Vec2(x, y));
            tile->adjustPosition();
        }
    }
    
    return true;
}

Tile * Stage::getTileAt(int x, int y)
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

void Stage::addTile(Tile *tile)
{
    auto gp = tile->getGridPos();
    if (tile->isValid()) {
        _tiles.pushBack(tile);
        this->addChild(tile);
        return;
    }
    assert("Grid point of the tile is invalid in Stage::addTile.");
}

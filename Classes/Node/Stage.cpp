//
//  Stage.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "Stage.h"

bool Stage::init()
{
    if (!Node::init()) {
        return false;
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
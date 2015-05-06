//
//  RailTile.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "RailTile.h"
#include "define.h"

RailTile::RailTile()
: _type(Type::MOVABLE)
{
}

bool RailTile::init()
{
    if (!Sprite::initWithFile("tile.png")) {
        return false;
    }
    return true;
}

bool RailTile::isValid()
{
    const auto& gp = _gridPos;
    return (floor(gp.x) == gp.x &&
            floor(gp.y) == gp.y &&
            gp.x >= 0 &&
            gp.x < 3 &&
            gp.y >= 0);
}

void RailTile::adjustPosition()
{
    if (this->isValid()) {
        const auto& gp = this->getGridPos();
        auto x = ((1 + gp.x) * ROAD_WIDTH + gp.x * TILE_WIDTH) + TILE_WIDTH / 2.0;
        auto y = gp.y * TILE_HEIGHT;
        this->setPosition(x, y);
    }
}
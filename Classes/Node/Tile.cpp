//
//  Tile.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "Tile.h"
#include "define.h"

Tile::Tile()
: _type(Type::MOVABLE)
{
}

bool Tile::init()
{
    if (!Sprite::initWithFile("tile.png")) {
        return false;
    }
    return true;
}

bool Tile::isValid()
{
    const auto& gp = _gridPos;
    return (floor(gp.x) == gp.x &&
            floor(gp.y) == gp.y &&
            gp.x >= 0 &&
            gp.x < 3 &&
            gp.y >= 0);
}

void Tile::adjustPosition()
{
    if (this->isValid()) {
        const auto& gp = this->getGridPos();
        auto x = ((1 + gp.x) * ROAD_WIDTH + gp.x * TILE_WIDTH) + TILE_WIDTH / 2.0;
        auto y = gp.y * TILE_HEIGHT;
        this->setPosition(x, y);
    }
}
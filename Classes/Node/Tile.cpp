//
//  Tile.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "Tile.h"

Tile::Tile()
: _type(Type::MOVABLE)
{
}

bool Tile::init()
{
    if (!Sprite::init()) {
        return false;
    }
    return true;
}
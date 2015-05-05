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
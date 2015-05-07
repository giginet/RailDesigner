//
//  Player.cpp
//  RailDesigner
//
//  Created by giginet on 5/7/15.
//
//

#include "Player.h"

USING_NS_CC;

Player::Player()
{
}

Player::~Player()
{
}

bool Player::init()
{
    if (!Sprite::initWithFile("player.png")) {
        return false;
    }
    return true;
}

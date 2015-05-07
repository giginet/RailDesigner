//
//  Player.h
//  RailDesigner
//
//  Created by giginet on 5/7/15.
//
//

#ifndef __RailDesigner__Player__
#define __RailDesigner__Player__

#include "cocos2d.h"

class Player :public cocos2d::Sprite
{
protected:
    Player();
    virtual ~Player();
    bool init();
public:
    CREATE_FUNC(Player);
};

#endif /* defined(__RailDesigner__Player__) */

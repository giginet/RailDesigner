//
//  MainScene.h
//  RailDesigner
//
//  Created by giginet on 5/4/15.
//
//

#ifndef __RailDesigner__MainScene__
#define __RailDesigner__MainScene__

#include "cocos2d.h"

class MainScene :public cocos2d::Layer
{
protected:
    bool init() override;
public:
    static cocos2d::Scene * createScene();
    CREATE_FUNC(MainScene);
};

#endif /* defined(__RailDesigner__MainScene__) */

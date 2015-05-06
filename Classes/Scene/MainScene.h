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
#include "Stage.h"

class MainScene :public cocos2d::Layer
{
protected:
    MainScene();
    virtual ~MainScene();
    bool init() override;
public:
    static cocos2d::Scene * createScene();
    /// ステージ
    CC_SYNTHESIZE_RETAIN(Stage *, _stage, Stage);
    CREATE_FUNC(MainScene);
};

#endif /* defined(__RailDesigner__MainScene__) */

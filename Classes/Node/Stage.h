//
//  Stage.h
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#ifndef __RailDesigner__Stage__
#define __RailDesigner__Stage__

#include "cocos2d.h"

/** ゲームステージ用のノードです
/* 画面をスクロールさせたり、特定のタイルを取り出したりします。
 */
class Stage :public cocos2d::Node
{
protected:
    bool init() override;
public:
    CREATE_FUNC(Stage);
};

#endif /* defined(__RailDesigner__Stage__) */

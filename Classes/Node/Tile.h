//
//  Tile.h
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#ifndef __RailDesigner__Tile__
#define __RailDesigner__Tile__

#include "cocos2d.h"

/** タイル用のSpriteクラスです
 */
class Tile :public cocos2d::Sprite
{
protected:
    Tile();
    bool init() override;
public:
    
    enum class Type
    {
        /// 移動可能
        MOVABLE,
        /// 固定
        FIXED
    };
    /// ラインの開始点
    CC_SYNTHESIZE(cocos2d::Vec2, _origin, Origin);
    /// ラインの終了点
    CC_SYNTHESIZE(cocos2d::Vec2, _destination, Destination);
    /// タイルの種類
    CC_SYNTHESIZE_READONLY(Type, _type, Type);
    CREATE_FUNC(Tile);
};


#endif /* defined(__RailDesigner__Tile__) */

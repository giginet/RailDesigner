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
#include "Tile.h"

typedef cocos2d::Vector<Tile *> TileList;

/** ゲームステージ用のノードです
 *  画面をスクロールさせたり、特定のタイルを取り出したりします。
 */
class Stage :public cocos2d::Node
{
private:
    TileList _tiles;
protected:
    Stage();
    virtual ~Stage();
    bool init() override;
public:

    /**
     指定グリッド位置にあるタイルを取り出します
     @param x x座標（0, 1, 2）
     @param y y座標（自然数）
     @return タイル、見つからなかったらnullptr
     */
    Tile * getTileAt(int x, int y);
    
    /** 
     * 指定位置にあるタイルを取り除きます
     * @param x x座標
     * @param y y座標
     */
    void removeTileAt(int x, int y);
    
    /**
     * タイルを追加します
     * Tile#_gridPosが不正な値の場合、assertを投げます
     * @param 追加するタイル
     */
    void addTile(Tile * tile);

    /// タイル配置用のノード
    CC_SYNTHESIZE(cocos2d::Node *, _tileNode, TileNode);
    CREATE_FUNC(Stage);
};

#endif /* defined(__RailDesigner__Stage__) */

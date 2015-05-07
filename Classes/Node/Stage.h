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
#include "RailTile.h"
#include "Player.h"

typedef cocos2d::Vector<RailTile *> TileList;

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
    
    void update(float dt) override;

    /**
     指定グリッド位置にあるタイルを取り出します
     @param x x座標（0, 1, 2）
     @param y y座標（自然数）
     @return タイル、見つからなかったらnullptr
     */
    RailTile * getTileAt(int x, int y);
    
    /** 
     * 指定位置にあるタイルを取り除きます
     * @param x x座標
     * @param y y座標
     */
    void removeTileAt(int x, int y);
    
    /**
     *  指定したタイルを取り除きます
     *  @param tile 消すタイル
     */
    void removeTile(RailTile * tile);
    
    /**
     * タイルを追加します
     * Tile#_gridPosが不正な値の場合、assertを投げます
     * @param 追加するタイル
     */
    void addTile(RailTile * tile);
    
    /**
     *  タイルが存在するかどうかを返します
     *  @param x x座標
     *  @param y y座標
     *  @return タイルが存在するかどうか
     */
    bool isExistTile(int x, int y);
    
    /**
     *  グローバル座標をグリッド座標に変換します
     *  @param worldSpace グローバル座標
     *  @return タイル座標。もし、タイルが設置できない場所だった場合、(-1, -1)を返す
     */
    cocos2d::Vec2 convertToGridSpace(cocos2d::Vec2 worldSpace);
    /// スクロール量
    CC_SYNTHESIZE(float, _scroll, Scroll);
    /// タイル配置用のノード
    CC_SYNTHESIZE_RETAIN(cocos2d::Node *, _tileNode, TileNode);
    /// プレイヤー
    CC_SYNTHESIZE_RETAIN(Player *, _player, Player);
    CREATE_FUNC(Stage);
};

#endif /* defined(__RailDesigner__Stage__) */

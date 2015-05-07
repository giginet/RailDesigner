//
//  Stage.cpp
//  RailDesigner
//
//  Created by giginet on 5/5/15.
//
//

#include "Stage.h"
#include "define.h"

USING_NS_CC;

const int Z_ORDER_PLAYER = 10000;

Stage::Stage()
: _scroll(0)
, _tileNode(nullptr)
, _player(nullptr)
{
}

Stage::~Stage()
{
    CC_SAFE_RELEASE_NULL(_tileNode);
    CC_SAFE_RELEASE_NULL(_player);
}

bool Stage::init()
{
    if (!cocos2d::Node::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto tileNode = cocos2d::Node::create();
    this->setTileNode(tileNode);
    this->addChild(tileNode);
    
    const int NUMBER_OF_ROADS = 4;
    for (int i = 0; i < NUMBER_OF_ROADS; ++i) {
        auto road = cocos2d::Sprite::create("road.png");
        auto x = i * (TILE_WIDTH + ROAD_WIDTH) + ROAD_WIDTH / 2.0;
        ;
        road->setPosition(x, 180);
        _tileNode->addChild(road);
    }
    this->setPosition(STAGE_MARGIN_X, 120);
    
    /*for (int x = 0; x < 3; ++x) {
     for (int y = 0; y < 10; ++y) {
     auto tile = RailTile::create();
     tileNode->addChild(tile);
     tile->setGridPos(cocos2d::Vec2(x, y));
     tile->adjustPosition();
     }
     }*/
    
    auto player = Player::create();
    this->setPlayer(player);
    _tileNode->addChild(player);
    
    _player->setPositionX(ROAD_WIDTH / 2.0);
    _player->setZOrder(Z_ORDER_PLAYER);
    
    this->scheduleUpdate();
    
    return true;
}

void Stage::update(float dt)
{
    _scroll += 1;
    _player->setPositionY(_scroll);
    _tileNode->setPositionY(-_scroll);
    
    // 画面外に消えたタイルを削除する
    cocos2d::Vector<RailTile *> deletedTile;
    
    for (auto& tile : _tiles) {
        auto nodePos = tile->getPosition();
        auto worldPos = _tileNode->convertToWorldSpace(nodePos);
        if (worldPos.y < -TILE_HEIGHT) {
            deletedTile.pushBack(tile);
        }
    }
    for (auto& tile : deletedTile) {
        this->removeTile(tile);
    }
    deletedTile.clear();
    
}

RailTile * Stage::getTileAt(int x, int y)
{
    for (auto& tile : _tiles) {
        auto gp = tile->getGridPos();
        if (gp.x == x && gp.y == y) {
            return tile;
        }
    }
    return nullptr;
}

void Stage::removeTileAt(int x, int y)
{
    auto tile = this->getTileAt(x, y);
    this->removeTile(tile);
}

void Stage::removeTile(RailTile *tile)
{
    if (tile) {
        tile->removeFromParent();
        _tiles.eraseObject(tile);
    }
}

void Stage::addTile(RailTile *tile)
{
    auto gp = tile->getGridPos();
    if (tile->isValid()) {
        _tiles.pushBack(tile);
        _tileNode->addChild(tile);
        return;
    }
    assert("Grid point of the tile is invalid in Stage::addTile.");
}

bool Stage::isExistTile(int x, int y)
{
    return this->getTileAt(x, y) != nullptr;
}

cocos2d::Vec2 Stage::convertToGridSpace(cocos2d::Vec2 worldSpace)
{
    auto nodeSpace = _tileNode->convertToNodeSpace(worldSpace);
    auto gridY = floorf((nodeSpace.y + TILE_HEIGHT / 2.0) / TILE_HEIGHT);
    if (gridY >= 0) {
        for (int x = 0; x < 3; ++x) {
            auto boundLeft = (1 + x) * ROAD_WIDTH + x * TILE_WIDTH;
            auto boundRight = boundLeft + TILE_WIDTH;
            if (boundLeft <= nodeSpace.x && nodeSpace.x < boundRight) {
                return cocos2d::Vec2(x, gridY);
            }
        }
    }
    return cocos2d::Vec2(-1, -1);
}
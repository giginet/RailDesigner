//
//  MainScene.cpp
//  RailDesigner
//
//  Created by giginet on 5/4/15.
//
//

#include "MainScene.h"
#include "RailTile.h"

USING_NS_CC;

MainScene::MainScene()
: _stage(nullptr)
{
}

MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(_stage);
}

cocos2d::Scene * MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    //auto center = cocos2d::Vec2(winSize.width / 2.0, winSize.height / 2.0);
    
    auto stage = Stage::create();
    //stage->setPosition(center);
    this->addChild(stage);
    this->setStage(stage);
    
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](cocos2d::Touch *touch, cocos2d::Event * e) {
        auto pos = touch->getLocation();
        auto gridPos = _stage->convertToGridSpace(pos);
        log("x = %d, y = %d", (int)gridPos.x, (int)gridPos.y);
        
        if (gridPos.x >= 0 && gridPos.y >= 0 && !_stage->isExistTile(gridPos.x, gridPos.y)) {
            auto tile = RailTile::create();
            tile->setGridPos(gridPos);
            tile->adjustPosition();
            _stage->addTile(tile);
        }
        
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
    
}
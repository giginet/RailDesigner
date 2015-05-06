//
//  MainScene.cpp
//  RailDesigner
//
//  Created by giginet on 5/4/15.
//
//

#include "MainScene.h"
#include "Stage.h"

USING_NS_CC;

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
    
    return true;
    
}
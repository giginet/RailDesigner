//
//  MainScene.cpp
//  RailDesigner
//
//  Created by giginet on 5/4/15.
//
//

#include "MainScene.h"

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
    return true;
    
}
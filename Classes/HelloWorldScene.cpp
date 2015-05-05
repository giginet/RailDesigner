#include "HelloWorldScene.h"
#include "KamcordManager.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    platform::KamcordManager::getInstance()->setup("zXLjTkAmWPQ7k0HUcQxKCUBkxqUJPXnwHW3xQZtn0L5",
                                                   "4nNzlb2h4OLJbC5MoZ1hV1a9YIaLGhxFuUnJsdS92wx",
                                                   "RailDesigner");


    auto startButton = ui::Button::create("sprite9.png");
    startButton->setScale9Enabled(true);
    startButton->setContentSize(cocos2d::Size(100, 100));
    startButton->setPosition(Vec2(visibleSize.width * 0.3, visibleSize.height * 0.2));
    startButton->setTitleText("start");
    startButton->setTitleColor(Color3B::BLACK);
    startButton->setTitleFontSize(20);
    this->addChild(startButton, 2);

    startButton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            log("start");
            platform::KamcordManager::getInstance()->startRecording();
        }
        return;
    });

    auto stopButton = ui::Button::create("sprite9.png");
    stopButton->setScale9Enabled(true);
    stopButton->setContentSize(cocos2d::Size(100, 100));
    stopButton->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.2));
    stopButton->setTitleText("stop");
    stopButton->setTitleColor(Color3B::BLACK);
    stopButton->setTitleFontSize(20);
    this->addChild(stopButton, 2);

    stopButton->addTouchEventListener([this](Ref* pSender, ui::Widget::TouchEventType type){
        if (type == ui::Widget::TouchEventType::ENDED) {
            log("stop");
            platform::KamcordManager::getInstance()->stopRecording();
        }
        return;
    });

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

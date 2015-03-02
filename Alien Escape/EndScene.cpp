#include "EndScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* EndScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = EndScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool EndScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto menu_item_1 = MenuItemFont::create("Main Menu (replace)", CC_CALLBACK_1(EndScene::MainMenu, this));
        
    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3) * 2));
    
    auto *menu = Menu::create(menu_item_1, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    return true;
}

// go back to previous scene
void EndScene::MainMenu(cocos2d::Ref *pSender)
{
	// create the main menu scene
	auto scene = MainMenu::createScene();

	// replace the end game scene with the main menu
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene));
		
}


void EndScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

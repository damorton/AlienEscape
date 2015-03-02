#include "PauseScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto menu_item_1 = MenuItemFont::create("Resume Game (pop)", CC_CALLBACK_1(PauseScene::Resume, this));
    auto menu_item_2 = MenuItemFont::create("Exit to Main Menu (pop/replaceScene)", CC_CALLBACK_1(PauseScene::MainMenu, this));
    
    menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3) * 2));
    menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3) * 1));
    
    auto *menu = Menu::create(menu_item_1, menu_item_2, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);
    
    return true;
}

/*
	Resume button pops the pause scene and returns to the game scene

	@param cocos2d::Ref *pSender pointer used by the engine
*/
void PauseScene::Resume(cocos2d::Ref *pSender)
{
	// pop pause scene
    Director::getInstance()->popScene();		
}

/*
	Main menu button pops the pause scene and then replaces the game scene with 
	a new main menu scene.
	
	@param cocos2d::Ref *pSender pointer used by the engine
*/
void PauseScene::MainMenu(cocos2d::Ref *pSender)
{
	// pop pause scene & replace game scene
	Director::getInstance()->popScene(); // pop the pause scene

    auto scene = MainMenu::createScene(); // create the mainmenu    
	Director::getInstance()->replaceScene(TransitionFlipX::create(1, scene)); // replace the game scene with the main menu

	// need to reset the game scene in order to play a fresh new game

}

void PauseScene::menuCloseCallback(Ref* pSender)
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

#include "GameScene.h"
#include "MainMenuScene.h"
#include "EndScene.h"
#include "PauseScene.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Player.h"

USING_NS_CC;

// game manager
GameManager* m_cGameManager;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// create the GameManager
	m_cGameManager = new GameManager();

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add a label shows "Hello World"
	// create and initialize a label    
	auto label = LabelTTF::create("Game Scene", "Helvetica", 18);
	label->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label->getContentSize().height));
	this->addChild(label, 1);

	// add foreground to game scene
	auto mySprite = Sprite::create("foreground.png");
	mySprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(mySprite, 0);

	// player
	WorldManager::getInstance()->getPlayer()->setSprite("Player.png");
	auto playerSprite = WorldManager::getInstance()->getPlayer()->getSprite();
	playerSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(playerSprite, 0);

	// pause button
	auto menu_item_pause = MenuItemImage::create("pause11.png", "pause36.png", CC_CALLBACK_1(GameScene::Pause, this));
	menu_item_pause->setPosition(Point(visibleSize.width - 50, visibleSize.height - 50));

	// end game button
	auto menu_item_endScene = MenuItemImage::create("cancel20.png", "cancel20.png", CC_CALLBACK_1(GameScene::EndGame, this));
	menu_item_endScene->setPosition(Point(visibleSize.width - 50, 50));

	// create menu, add menu items and add to the game scene
	auto *menu = Menu::create(menu_item_pause, menu_item_endScene, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	// call the schedule update in order to run this layers update function
	this->scheduleUpdate();
	return true;
}

/*
The hello world upate function is calling the game managers
update function 60 times per second or whatever the fps is set
to. This is the game loop implementation because if a seperate loop was added to the
game managers update function the application would be caught in an infinite loop.

@param delta time
*/
void GameScene::update(float delta)
{
	// call the game manager update function
	m_cGameManager->update();
}


/*
Pause button creates a new pause scene and pushes it over the game scene

@param cocos2d::Ref *pSender pointer used by the engine
*/
void GameScene::Pause(cocos2d::Ref *pSender)
{
	CCLOG("Pause");
	auto scene = PauseScene::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1, scene));
}

/*
EndGame button creates a new game game scene and replaces the game scene

@param cocos2d::Ref *pSender pointer used by the engine
*/
void GameScene::EndGame(cocos2d::Ref *pSender)
{
	CCLOG("End Game");
	auto scene = EndScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

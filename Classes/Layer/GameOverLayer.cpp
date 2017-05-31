#include "GameOverLayer.h"
#include "MenuLayer.h"
#include "yUtils\Helper\yUtils.h"
#include <SimpleAudioEngine.h>

Scene* GameOverLayer::createScene()
{
	Scene* scene = Scene::create();

	GameOverLayer* layer = GameOverLayer::create();

	scene->addChild(layer);

	return scene;
}

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();


	Sprite* spGameOver = Sprite::create("res/gameover.png");
	this->addChild(spGameOver);
	spGameOver->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);


	MenuItemFont* itemRePlay = MenuItemFont::create("back MainMenu", [&](Ref* ref)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});


//	MenuItemFont* itemRePlay = MenuItemFont::create(yUtils::GBK2UTF("返回主界面").c_str(), [&](Ref* ref)
//	{
//		CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//		Director::getInstance()->replaceScene(MenuLayer::createScene());
//	});

	itemRePlay->setPosition(visibleSize.width / 2, visibleSize.height / 4);
	Menu* menu = Menu::create(itemRePlay, NULL);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/gameover.aif");

	return true;
}

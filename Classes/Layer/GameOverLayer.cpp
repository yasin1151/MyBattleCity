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

	//¶ÁÈ¡ÅäÖÃ
	ValueMap vConfig = FileUtils::getInstance()->getValueMapFromFile("Config/FinalLayerConfig.xml");

	Sprite* spGameOver = Sprite::create("res/gameover.png");
	this->addChild(spGameOver);
	spGameOver->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);


	MenuItemFont* itemRePlay = MenuItemFont::create(vConfig["BackGameString"].asString(), [&](Ref* ref)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});


	itemRePlay->setPosition(visibleSize.width / 2, visibleSize.height / 4);
	Menu* menu = Menu::create(itemRePlay, NULL);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/gameover.aif");

	return true;
}

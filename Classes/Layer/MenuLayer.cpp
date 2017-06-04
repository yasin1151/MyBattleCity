#include "MenuLayer.h"


bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* spLogo = Sprite::create("res/BattleCity.png");
	spLogo->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);
	this->addChild(spLogo);

	MenuItemFont* itemPlayGame = MenuItemFont::create("Play Game", [&](Ref* ref)
	{
		Director::getInstance()->replaceScene(ChooseMenuLayer::createScene());
	});
	itemPlayGame->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 7);

	MenuItemFont* itemExitGame = MenuItemFont::create("Exit Game", [&](Ref* ref)
	{
		

		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif

	});
	itemExitGame->setPosition(visibleSize.width / 2, visibleSize.height / 4);

	Menu* menu = Menu::create(itemPlayGame, itemExitGame, NULL);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);



	return true;
}

MenuLayer::MenuLayer()
{
		
}
MenuLayer::~MenuLayer()
{

}

Scene* MenuLayer::createScene()
{
	Scene* scene = Scene::create();

	MenuLayer* layer = MenuLayer::create();

	scene->addChild(layer);

	return scene;
}

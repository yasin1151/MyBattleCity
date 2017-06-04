#include "WinLayer.h"
#include "MenuLayer.h"
#include <SimpleAudioEngine.h>

Scene* WinLayer::createScene()
{
	Scene* scene = Scene::create();

	WinLayer* layer = WinLayer::create();

	scene->addChild(layer);

	return scene;
}

bool WinLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Label* pLabel = Label::create();
	pLabel->setString("You Win!");
	pLabel->setSystemFontSize(32);
	this->addChild(pLabel);
	pLabel->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);


	MenuItemFont* itemRePlay = MenuItemFont::create(yUtils::GBK2UTF("返回主界面").c_str(), [&](Ref* ref)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	itemRePlay->setPosition(visibleSize.width / 2, visibleSize.height / 4);
	Menu* menu = Menu::create(itemRePlay, NULL);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);

	return true;
}

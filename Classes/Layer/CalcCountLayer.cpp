#include "CalcCountLayer.h"
#include "MenuLayer.h"
#include "GameLayer.h"

int CalcCountLayer::m_iMaxLevelCount = 0;

Scene* CalcCountLayer::createScene(int iScore, int iCurLevel)
{
	Scene* scene = Scene::create();

	CalcCountLayer* layer = CalcCountLayer::create(iScore, iCurLevel);

	scene->addChild(layer);

	return scene;
}

bool CalcCountLayer::init(int iScore, int iCurLevel)
{
	if (!Layer::init())
	{
		return false;
	}

	//初始化参数s
	m_iCurLevel = iCurLevel;
	m_iScore = iScore;
	m_iMaxLevelCount = 3;
	//读取配置文件
	m_vConfig = FileUtils::getInstance()->getValueMapFromFile("Config/CalcCountLayerConfig.xml");
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	

	//分数label
	Label* scoreLabel = Label::create();
	scoreLabel->setString(m_vConfig["CurScoreLabel"].asString() + yUtils::toStr(m_iScore));
	scoreLabel->setSystemFontSize(m_vConfig["FontSize"].asInt());
	scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 3 / 4);


	//当前关卡Label
	Label* curLevel = Label::create();
	curLevel->setString(m_vConfig["CurLevelLabel"].asString() + yUtils::toStr(iCurLevel));
	curLevel->setSystemFontSize(m_vConfig["CurLevelFontSize"].asInt());
	curLevel->setPosition(visibleSize.width / 2, visibleSize.height / 2);


	//返回主菜单Menu
	MenuItemFont* backMenu = MenuItemFont::create(m_vConfig["BackMenuLabel"].asString(),
		[&](Ref* ref)
	{
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});

	Menu* menu = nullptr;

	//如果还有下一关
	if (m_iCurLevel < m_iMaxLevelCount)
	{
		//创建下一关按钮
		MenuItemFont* nextLevelMenu = MenuItemFont::create(m_vConfig["NextLevelLabel"].asString(),
			[&](Ref* ref)
		{
			auto scene = Scene::create();
			scene->addChild(GameLayer::create(m_iCurLevel + 1));
			Director::getInstance()->replaceScene(scene);
		});

		backMenu->setPosition(visibleSize.width * 2 / 8,
			visibleSize.height / 8);


		nextLevelMenu->setPosition(visibleSize.width * 6 / 8,
			visibleSize.height / 8);

		menu = Menu::create(backMenu, nextLevelMenu, NULL);
	}
	else
	{
		backMenu->setPosition(visibleSize.width / 2,
			visibleSize.height / 8);

		menu = Menu::create(backMenu, NULL);
	}

	menu->setPosition(Vec2::ZERO);

	this->addChild(scoreLabel);
	this->addChild(curLevel);

	this->addChild(menu);

	return true;
}

CalcCountLayer* CalcCountLayer::create(int iScore, int iCurLevel)
{
	CalcCountLayer* pRet = new CalcCountLayer();
	if (pRet && pRet->init(iScore, iCurLevel))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

void CalcCountLayer::setMaxLevelCount(int iCount)
{
	m_iMaxLevelCount = iCount;
}

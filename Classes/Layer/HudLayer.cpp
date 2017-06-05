#include "HudLayer.h"

void HudLayer::flushShow()
{
	//刷新数据
	m_pScoreLabel->setString(String::createWithFormat("%d", m_iScore)->getCString());
	m_pLifeLabel->setString(String::createWithFormat("%d", m_iLife)->getCString());
	m_pCurLevel->setString(String::createWithFormat("%d", m_iCurLevel)->getCString());

	for (int i = m_iCurEnemyNum; i < m_iEnemyNum ; i++)
	{
		m_arrEnemySp[i]->setVisible(false);
	}

}

HudLayer* HudLayer::create(int iCurLevel, int iLife, int iEnemyNum)
{
	HudLayer* pRet = new HudLayer;
	if (pRet && pRet->init(iCurLevel, iLife, iEnemyNum))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool HudLayer::init(int iCurLevel, int iLife, int iEnemyNum)
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();


	//读取配置
	ValueMap vConfig = FileUtils::getInstance()->getValueMapFromFile("Config/HudeLayerConfig.xml");

	m_iCurLevel = iCurLevel;
	m_iLife = iLife;
	m_iEnemyNum = iEnemyNum;
	m_iCurEnemyNum = iEnemyNum;
	m_iScore = 0;
	m_bIsUpdata = false;
	m_vFirstEnemyPos = Vec2(visibleSize.width - 120, visibleSize.height - 80);


	//创建分数label
	Label* scoreLatter = Label::create();
	scoreLatter->setString(vConfig["ScoreLabel"].asString());
	scoreLatter->setSystemFontSize(25);
	scoreLatter->setPosition(visibleSize.width - 130, visibleSize.height - 30);
	this->addChild(scoreLatter);

	m_pScoreLabel = Label::create();
	m_pScoreLabel->setPosition(scoreLatter->getBoundingBox().getMaxX() + 30,
		scoreLatter->getPositionY());
	m_pScoreLabel->setString("0");
	m_pScoreLabel->setSystemFontSize(25);
	m_pScoreLabel->setAlignment(TextHAlignment::LEFT);
	this->addChild(m_pScoreLabel);

	//创建20个精灵对象，用于显示当前剩余的敌人数目
	for (int i = 0; i < m_iEnemyNum / 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			//2列，10行
			Sprite* spBuf = Sprite::create("res/p1-a-cell.png");
			this->addChild(spBuf);
			spBuf->setScale(0.8f);
			spBuf->setPosition(m_vFirstEnemyPos.x + j * spBuf->getContentSize().width + 10, m_vFirstEnemyPos.y - i * spBuf->getContentSize().height * 0.8f);
			m_arrEnemySp.push_back(spBuf);

		}
	}

	//创建生命label
	Label* lifeLetter = Label::create();
	lifeLetter->setString(vConfig["LifeLabel"].asString());
	lifeLetter->setPosition(visibleSize.width - 120, visibleSize.height / 4);
	lifeLetter->setSystemFontSize(25);
	lifeLetter->setAlignment(TextHAlignment::LEFT);
	this->addChild(lifeLetter);

	m_pLifeLabel = Label::create();
	m_pLifeLabel->setPosition(lifeLetter->getBoundingBox().origin.x +
		lifeLetter->getContentSize().width + 10,
		lifeLetter->getPositionY());
	m_pLifeLabel->setString(String::createWithFormat("%d", m_iLife)->getCString());
	m_pLifeLabel->setAlignment(TextHAlignment::LEFT);
	m_pLifeLabel->setSystemFontSize(25);
	this->addChild(m_pLifeLabel);

	//创建关卡等级label
	Label* levelLetter = Label::create();
	levelLetter->setString(vConfig["LevelLabel"].asString());
	levelLetter->setPosition(visibleSize.width - 120, visibleSize.height / 6);
	levelLetter->setSystemFontSize(25);
	levelLetter->setAlignment(TextHAlignment::LEFT);
	this->addChild(levelLetter);

	m_pCurLevel = Label::create();
	m_pCurLevel->setPosition(levelLetter->getBoundingBox().origin.x +
		levelLetter->getContentSize().width + 10,
		levelLetter->getPositionY());
	m_pCurLevel->setString(String::createWithFormat("%d", m_iCurLevel)->getCString());
	m_pCurLevel->setAlignment(TextHAlignment::LEFT);
	m_pCurLevel->setSystemFontSize(25);
	this->addChild(m_pCurLevel);


	//开启定时器
	this->scheduleUpdate();

	return true;
}

void HudLayer::update(float dt)
{
	if (m_bIsUpdata)
	{
		flushShow();
		m_bIsUpdata = false;
	}
}

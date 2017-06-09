#include "GameLayer.h"
#include <SimpleAudioEngine.h>
#include "MenuLayer.h"

GameLayer* GameLayer::create(int roundNum)
{
	GameLayer* pRet = new GameLayer();
	if (pRet && pRet->init(roundNum))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool GameLayer::init(int roundNum)
{
	if (!Layer::init())
	{
		return false;
	}

	//读取配置文件
	m_vConfig = FileUtils::getInstance()->getValueMapFromFile("Config/GameLayerConfig.xml");

	//创建一个灰色背景
	this->addChild(LayerColor::create(Color4B::GRAY), -100);

	//初始化地图
	initMap(String::createWithFormat("maps/Round%d.tmx", roundNum)->getCString());
	m_iCurRoundNum = roundNum;

	//初始化ui层
	m_pHudLayer = HudLayer::create(roundNum, m_vConfig["UserLifeNum"].asInt(), m_vConfig["EnemyTankNum"].asInt());
	this->addChild(m_pHudLayer, 100);

	//初始化摇杆对象
	m_pRocker = Rocker4AWithTrans::create("Rocker/Direction_bc.png", "Rocker/Direction_bt.png", Vec2(100, 100),  ROCKER_LD);
	this->addChild(m_pRocker);

	//初始化菜单
	initMenu();

	//初始化键盘事件
	initKeyboardEvent();

	//初始化坦克工厂对象
	m_pTankFactory = new TankFactory(m_pMap, 
		Vec2(m_vConfig["TankSpeedX"].asInt(), m_vConfig["TankSpeedY"].asInt()));

	//初始化玩家
	initPlayer();

	//初始话ai玩家
	initAIPlayer();

	//初始化道具管理对象
	initStage();

	//开启调度器
	this->scheduleUpdate();

	//开启ai创建器
	this->schedule(schedule_selector(GameLayer::aiCreator), 
		m_vConfig["AICreateInterval"].asInt(), -1, m_vConfig["FirstAICreateDelay"].asInt());

	//开启道具创建器
	this->schedule(schedule_selector(GameLayer::stageCreateUpdate), 
		m_vConfig["StageCreateInterval"].asInt(), -1, m_vConfig["FirstStageCreateDelay"].asInt());

	//开启背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/start.aif", true);

	//设置背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
	CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0);

	
	return true;
}

GameLayer::~GameLayer()
{
	m_pMap->release();
	
	CC_SAFE_DELETE(m_pPlayer);

	CC_SAFE_DELETE(m_pTankFactory);

	CC_SAFE_DELETE(m_pAIMgr);

	CC_SAFE_DELETE(m_pStageMgr);
}

void GameLayer::update(float dt)
{
	//键盘更新
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	for (auto it : m_listKeyCode)
	{
		KeyboardCallBack(it);
	}
#endif

	//摇杆更新
	rockerUpdate(dt);

	//ai更新
	m_pAIMgr->aiUpdte(this, dt);
	
	//碰撞检测
	m_pAIMgr->collisionUpdate(this, dt);

	//道具更新
	m_pStageMgr->update(m_pPlayer, dt);

}

void GameLayer::stageCreateUpdate(float dt)
{
	m_pStageMgr->createStage(m_pMap);
}

void GameLayer::rockerUpdate(float dt)
{
	switch (m_pRocker->getState())
	{
	case RockerState::Up: 
		UpCallBack(nullptr);
		break;
	case RockerState::Down: 
		DownCallBack(nullptr);
		break;
	case RockerState::Left: 
		LeftCallBack(nullptr);
		break;
	case RockerState::Right: 
		RightCallBack(nullptr);
		break;
	}
}

void GameLayer::aiCreator(float dt)
{
	//根据配置创建敌人
	if (0 >= m_pHudLayer->getRemainEnemyNum())
	{
		this->unschedule(schedule_selector(GameLayer::aiCreator));
	}
	//场上最多存在6个ai
	else if (m_vConfig["MaxOnlineAI"].asInt() <= m_pAIMgr->getAIPlayerNum())
	{
		return;
	}

	Player* pTmpPlayer = createPlayer(static_cast<TankType>(rand() % 4), 2, 
		m_arrAIPos[rand() % 3]);

	m_pMap->getTiledMap()->addChild(pTmpPlayer->getTank()->getSprite());

	m_pAIMgr->addAiPlayer(pTmpPlayer);

	m_pHudLayer->setRemainEnemyNum(m_pHudLayer->getRemainEnemyNum() - 1);

}

Player* GameLayer::createPlayer(const TankType& tankType, int playerType, const Vec2& vInitPos)
{
	Size tileSize = m_pMap->getTiledMap()->getTileSize();
	Player* pRet = nullptr;
	TankBase* pTankBase = m_pTankFactory->create(tankType);
	pTankBase->getSprite()->setPosition(vInitPos);
	pTankBase->setNextMoveRect(pTankBase->getSprite()->getBoundingBox());

	switch (playerType)
	{
	case 1:
		//创建普通玩家
		pRet = new UserPlayer(pTankBase);
		static_cast<MineTank*>(pRet->getTank())->setLife(m_vConfig["UserLifeNum"].asInt());
		break;
	case 2:
		//创建ai玩家
		pRet = new AIPlayer(pTankBase);
		pTankBase->getSprite()->setRotation(180);
		break;
	}

	//将坦克缩放到合适大小
	Size tankSize = pTankBase->getSprite()->getContentSize();
	pTankBase->getSprite()->setScale((tileSize.height * 2 - 4) / (tankSize.height));

	return pRet;
}

HudLayer* GameLayer::getHudLayer()
{
	return m_pHudLayer;
}

bool GameLayer::initMap(const char* fileName)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//实例化地图对象
	m_pMap = TankTiledMap::createWithTmxFile(fileName);
	m_pMap->retain();
	this->addChild(m_pMap->getTiledMap());

	m_pMap->getTiledMap()->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_pMap->getTiledMap()->setPosition(visibleSize / 2);

	//地图缩放
	//对地图进行缩放，以达到上下顶格
	int mapHeight = m_pMap->getTiledMap()->getContentSize().height / 2;
	float scaleRate = visibleSize.height / 2 / mapHeight;
	m_pMap->getTiledMap()->setScale(scaleRate);

	//加入一个黑色背景

	//为地图加上黑色背景
	Sprite* spMapBg = Sprite::create();
	spMapBg->setTextureRect(Rect(0, 0, m_pMap->getTiledMap()->getContentSize().width * scaleRate,
		m_pMap->getTiledMap()->getContentSize().height * scaleRate));
	spMapBg->setColor(Color3B::BLACK);
	this->addChild(spMapBg, -99);
	spMapBg->setPosition(visibleSize / 2);

	return true;
}

bool GameLayer::initMenu()
{
	MenuItemFont* itemExit =
		MenuItemFont::create(m_vConfig["ExitGameString"].asString(),
		[&](Ref* ref)
	{
		Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif

	});
	itemExit->setPosition(Vec2(90, 330));


	MenuItemFont* itemBack =
		MenuItemFont::create(m_vConfig["BackMenuString"].asString(),
		[&](Ref* ref)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	itemBack->setPosition(Vec2(90, 400));



	MenuItemImage* fireBtn =
		MenuItemImage::create("res/fire_button_default.png",
		"res/fire_button_press.png",
		CC_CALLBACK_1(GameLayer::ShotCallBack, this));
	fireBtn->setPosition(Vec2(Director::getInstance()->getWinSize().width - fireBtn->getContentSize().width / 2 - 20, 100));

	Menu* menu = Menu::create(itemExit, itemBack, fireBtn, NULL);
	menu->setPosition(0, 0);
	menu->setAnchorPoint(Vec2(0, 0));

	this->addChild(menu);

	return true;
}

bool GameLayer::initAIPlayer()
{
	Size mapSize = m_pMap->getTiledMap()->getContentSize();
	Size tileSize = m_pMap->getTiledMap()->getTileSize();

	//从地图中初始化aiPos数组
	TMXObjectGroup* pObjects = m_pMap->getTiledMap()->getObjectGroup("objects");

	//获取对应
	for (int i = 0; i < 3; i++)
	{

		ValueMap vEnemy = pObjects->getObject(CCString::createWithFormat("enemy%d", i + 1)->getCString());
		
		int x = vEnemy["x"].asInt();
		
		int y = vEnemy["y"].asInt();

		m_arrAIPos.push_back(Vec2(x, y));
	}

	//初始化ai管理对象
	m_pAIMgr = new AIPlayerManager();
	m_pAIMgr->setUserTank(m_pPlayer->getTank());

	//创建ai玩家
	m_arrAIPos.push_back(Vec2(tileSize.width, mapSize.height - tileSize.height));
	m_arrAIPos.push_back(Vec2(mapSize.width / 2, mapSize.height - tileSize.height));
	m_arrAIPos.push_back(Vec2(mapSize.width - tileSize.width,
		mapSize.height - tileSize.height));

	for (int i = 0; i < 3; i++)
	{
		Player* pTmpPlayer = createPlayer(static_cast<TankType>(i), 2, m_arrAIPos[i]);

		m_pMap->getTiledMap()->addChild(pTmpPlayer->getTank()->getSprite());

		m_pAIMgr->addAiPlayer(pTmpPlayer);

		m_pHudLayer->setRemainEnemyNum(m_pHudLayer->getRemainEnemyNum() - 1);
	}

	return true;
}

bool GameLayer::initPlayer()
{
	Size mapSize = m_pMap->getTiledMap()->getContentSize();
	Size tileSize = m_pMap->getTiledMap()->getTileSize();

	//从地图中初始化palyer位置
	TMXObjectGroup* pObjects = m_pMap->getTiledMap()->getObjectGroup("objects");
	ValueMap vPos = pObjects->getObject("player1");

	int x = vPos["x"].asInt();
	int y = vPos["y"].asInt();

	Vec2 vBuf = Vec2(x, y);


	m_pPlayer = createPlayer(MineTankA, 1, vBuf);
	m_pMap->getTiledMap()->addChild(m_pPlayer->getTank()->getSprite());

	return true;
}

bool GameLayer::initStage()
{

	//实例化一个管理类对象
	m_pStageMgr = new StageManager();

	//获取道具随机出现的位置
	TMXObjectGroup* pObjects = m_pMap->getTiledMap()->getObjectGroup("objects");

	int i = 1;
	while (true)
	{
		ValueMap vPos = pObjects->getObject(CCString::createWithFormat("item%d", i++)->getCString());

		if (vPos.empty())
		{
			break;
		}

		int x = vPos["x"].asInt();
		int y = vPos["y"].asInt();

		//加入随机坐标到道具管理类中
		m_pStageMgr->pushPos(Vec2(x, y));
	}

	return true;
}

bool GameLayer::initKeyboardEvent()
{
	//在win32下
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto myKeyListener = EventListenerKeyboard::create(); //创建事件监听器监听键盘事件
	//键盘按键按下时的响应
	myKeyListener->onKeyPressed = [&](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		//对发射子弹特殊处理
		if (EventKeyboard::KeyCode::KEY_J == keycode)
		{
			ShotCallBack(nullptr);
		}
		else
		{
			m_listKeyCode.push_back(keycode);
		}
	};

	myKeyListener->onKeyReleased = [&](EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		m_listKeyCode.remove(keycode);
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
#endif
	return true;
}

void GameLayer::LeftCallBack(Ref* ref)
{
	//log("GameLayer::LeftCallBack");
	m_pPlayer->hanleInput(PlayerLeft, this);
	m_pPlayer->getTank()->move();
}

void GameLayer::RightCallBack(Ref* ref)
{
	//log("GameLayer::RightCallBack");
	m_pPlayer->hanleInput(PlayerRight, this);
	m_pPlayer->getTank()->move();

}

void GameLayer::UpCallBack(Ref* ref)
{
	//log("GameLayer::UpCallBack");
	m_pPlayer->hanleInput(PlayerUp, this);
	m_pPlayer->getTank()->move();
}

void GameLayer::DownCallBack(Ref* ref)
{
	//log("GameLayer::DownCallBack");
	m_pPlayer->hanleInput(PlayerDown, this);
	m_pPlayer->getTank()->move();
}

void GameLayer::ShotCallBack(Ref* ref)
{
	//log("GameLayer::ShotCallBack");
	m_pPlayer->hanleInput(PlayerShot, this);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/bullet.aif");
}

void GameLayer::KeyboardCallBack(EventKeyboard::KeyCode keyCode)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		//left
		LeftCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_D:
		//right
		RightCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_W:
		//up
		UpCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_S:
		//down
		DownCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_J:
		//shot
		ShotCallBack(nullptr);
		break;
	case EventKeyboard::KeyCode::KEY_K:
		break;
	}

}

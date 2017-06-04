#include "StageManager.h"

StageManager::StageManager()
	:m_bIsCanCreate(true),
	m_bIsCollision(false)
{
	m_pStageBase = new NullStage();
}

StageManager::~StageManager()
{

	CC_SAFE_DELETE(m_pStageBase);
}

void StageManager::update(Player* pPlayer, float dt)
{
	//如果已经碰撞了，则不需要碰撞检测了
	if (m_bIsCollision)
	{
		m_pStageBase->getSprite()->setVisible(false);
		if (!m_pStageBase->isOver())
		{
			m_pStageBase->update(dt);
		}
		else
		{
			m_bIsCanCreate = true;
		}
	}
	//否则进行碰撞检测
	else
	{
		CollisionTest(pPlayer);
	}
	
}

std::vector<Vec2>& StageManager::getRandomPosArr()
{
	return m_arrRandomPos;
}

void StageManager::pushPos(const Vec2& randomPos)
{
	m_arrRandomPos.push_back(randomPos);
}

void StageManager::createStage(TankTiledMap* pMap)
{
	if (!m_bIsCanCreate)
	{
		return;
	}
	//进行退出操作
	m_pStageBase->onExit();
	//回收内存
	delete m_pStageBase;
	m_pStageBase = nullptr;

	int iRandNum = rand() % 2 + 1;

	//暂时只生成StageStell
	switch (iRandNum)
	{
	case StageSteel: 
		m_pStageBase = new SteelStage(Sprite::create("item/steel.png"), pMap, 10.0f);
		break;
	case StageActive:
		m_pStageBase = new ActiveStage(Sprite::create("item/active.png"), pMap, 10.0f);
		break;
	case StageStar:
		break;
	case StageTimer: 
		break;
	case StageBomb: 
		break;
	}


	//初始化变量
	m_bIsCanCreate = false;
	m_bIsCollision = false;

	//设置位置
	pMap->getTiledMap()->addChild(m_pStageBase->getSprite());

	//随机取一个位置
	m_pStageBase->getSprite()->setPosition(m_arrRandomPos[rand() % m_arrRandomPos.size()]);
}

void StageManager::CollisionTest(Player* pPlayer)
{
	//如果相撞
	if (StageNull != m_pStageBase->getStageType() &&
		pPlayer->getTank()->getSprite()->getBoundingBox().intersectsRect(
		m_pStageBase->getSprite()->getBoundingBox()))
	{
		m_bIsCollision = true;
		//进行进入操作
		m_pStageBase->onEnter(pPlayer);
	}
}

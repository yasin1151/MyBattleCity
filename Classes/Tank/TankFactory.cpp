#include "TankFactory.h"

TankFactory::TankFactory()
	:m_pMap(nullptr),
	m_vInitSpeed()
{

}

TankFactory::TankFactory(TankTiledMap* pMap, const Vec2& vSpeed)
	:m_pMap(pMap),
	m_vInitSpeed(vSpeed)
{

}

void TankFactory::setInitSpeed(const Vec2& vSpeed)
{
	m_vInitSpeed = vSpeed;
}

void TankFactory::setTankMap(TankTiledMap* pMap)
{
	m_pMap = pMap;
}

TankBase* TankFactory::create(const TankType& tankType)
{
	TankBase* pRet = nullptr;
	switch (tankType)
	{
	case EnemyTankGreen:
		pRet = new EnemyTank(Sprite::create("tank/armor/armor3U.png"), tankType, m_pMap,
			m_vInitSpeed);
		break;
	case EnemyTankYellow: 
		pRet = new EnemyTank(Sprite::create("tank/armor/armor2U.png"), tankType, m_pMap,
			m_vInitSpeed);
		break;
	case EnemyTankWhite: 
		pRet = new EnemyTank(Sprite::create("tank/armor/armor1U.png"), tankType, m_pMap,
			m_vInitSpeed);
		break;
	case EnemyTankRed: 
		pRet = new EnemyTank(Sprite::create("tank/armor/armor3U_R.png"), tankType, m_pMap,
			m_vInitSpeed);
		break;
	case MineTankA: 
	case MineTankB: 
	case MineTankC: 
		pRet = new MineTank(Sprite::create("tank/player2/player2U.png"), tankType,
			m_pMap, m_vInitSpeed, 16);
		break;
	}
	return pRet;
}

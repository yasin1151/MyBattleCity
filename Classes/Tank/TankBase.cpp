#include "TankBase.h"


TankBase::TankBase(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed)
	:m_spTank(spTank),
	m_tankType(tankType),
	m_bIsCanMoved(false),
	m_pMap(pMap),
	m_vSpeed(speed)
{
	m_rNextMoveRect = spTank->getBoundingBox();
	//new 一个子弹管理对象的实例
	m_pBulletMgr = new BulletManager();
}

TankBase::~TankBase()
{
	delete m_pBulletMgr;
}

void TankBase::command(const TankCommandType& type)
{
	//旋转方向
	float fRota = m_spTank->getRotation();

	float fOffsetX = 0.0f;
	float fOffsetY = 0.0f;

	switch (type)
	{
	case MoveUp: 
		fRota = 0.0f;
		fOffsetY = 1.0f;
		break;
	case MoveDown: 
		fRota = 180.0f;
		fOffsetY = -1.0f;
		break;
	case MoveLeft: 
		fRota = 270.0f;
		fOffsetX = -1.0f;
		break;
	case MoveRight: 
		fRota = 90.0f;
		fOffsetX = 1.0f;
		break;
	case Shot:
	{
		int iRota = fRota;
		float fSpeedOffsetX = 0;
		float fSpeedOffsetY = 0;
		switch (iRota)
		{
		case 0:
			fSpeedOffsetY = 1.0f;
			break;
		case 90:
			fSpeedOffsetX = 1.0f;
			break;
		case 180:
			fSpeedOffsetY = -1.0f;
			break;
		case 270:
			fSpeedOffsetX = -1.0f;
			break;
		}
		//速度是坦克的四倍
		Vec2 vSpeed = Vec2(m_vSpeed.x * fSpeedOffsetX * 4, m_vSpeed.y * fSpeedOffsetY * 4);

		m_pBulletMgr->fire(m_spTank->getPosition() + vSpeed * 2, vSpeed, this);

		return;
	}
		break;
	}

	//进行旋转
	m_spTank->setRotation(fRota);

	//获取碰撞盒子
	Rect nextRect = m_spTank->getBoundingBox();

	Size tileSize = m_pMap->getTiledMap()->getTileSize();


	//获取新的移动盒子
	//进行速度缩放

	nextRect = Rect(
		Vec2(nextRect.getMinX() + fOffsetX * m_vSpeed.x * tileSize.width, 
		nextRect.getMinY() + fOffsetY *  m_vSpeed.y * tileSize.height),
		nextRect.size
		);

	//碰撞检测
	if (m_pMap->isCollision(nextRect, [](int gid){return gid != 0;}))
	{
		m_bIsCanMoved = false;
		return;
	}

	m_bIsCanMoved = true;
	m_rNextMoveRect = nextRect;
	
	return;
	
}

void TankBase::move()
{
	m_spTank->setPosition(m_rNextMoveRect.getMidX(), m_rNextMoveRect.getMidY());
}

Sprite* TankBase::getSprite()
{
	return m_spTank;
}

TankType TankBase::getTankType() const
{
	return m_tankType;
}

void TankBase::setTankType(const TankType& tankType)
{
	m_tankType = tankType;
}

bool TankBase::isCanMove() const
{
	return m_bIsCanMoved;
}

void TankBase::setCanMove(bool bIsCanMove)
{
	m_bIsCanMoved = bIsCanMove;
}

Rect TankBase::getNextMoveRect() const
{
	return m_rNextMoveRect;
}

void TankBase::setNextMoveRect(const Rect& rect)
{
	m_rNextMoveRect = rect;
}

void TankBase::setMap(TankTiledMap* pMap)
{
	m_pMap = pMap;
}

TankTiledMap* TankBase::getMap()
{
	return m_pMap;
}

void TankBase::setSpeed(const Vec2& speed)
{
	m_vSpeed = speed;
}

Vec2 TankBase::getSpeed() const
{
	return m_vSpeed;
}

BulletManager* TankBase::getBulletMgr()
{
	return m_pBulletMgr;
}

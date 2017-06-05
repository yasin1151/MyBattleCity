#ifndef _EnemyTank_H_
#define _EnemyTank_H_


#include "TankBase.h"

/**
*	@class : EnemyTank
*	@brief : 重载TankBase的beAtk方法
*/


class EnemyTank : public TankBase
{
private:
	//是否死亡
	bool m_bIsDie;

	//用来标识当前的坦克类型
	TankType m_tCurType;

public:
	EnemyTank(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed)
		: TankBase(spTank, tankType, pMap, speed)
		, m_bIsDie(false),
		m_tCurType(tankType)
	{
	}

	virtual ~EnemyTank() override;

	virtual void beAtked() override;

	bool isDie() const
	{
		return m_bIsDie;
	}

	void setIsDie(bool bIsDie)
	{
		m_bIsDie = bIsDie;
	}
};


#endif
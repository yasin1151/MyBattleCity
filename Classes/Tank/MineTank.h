#ifndef _MineTank_H_
#define _MineTank_H_

#include "TankBase.h"

/**
*	@class : MineTank
*	@brief : 定义我方坦克被攻击时候的行为
*/

class MineTank : public TankBase
{
protected:
	//我方坦克的生命值
	int m_iLife; 


public:
	MineTank(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed, int iLife)
		: TankBase(spTank, tankType, pMap, speed),
		m_iLife(iLife)
	{
	}

	virtual ~MineTank() override;

	virtual void beAtked() override;

	//创建被攻击时的动画,确保该函数必须在加载完精灵帧后调用
	Animate* createBeAtkedAnimate(unsigned int loops, float delayTime);

	//设置我方坦克的生命值
	void setLife(int iLife)
	{
		m_iLife = iLife;
	}

	//获取我方坦克的生命值
	int getLife() const
	{
		return m_iLife;
	}
	
};

#endif
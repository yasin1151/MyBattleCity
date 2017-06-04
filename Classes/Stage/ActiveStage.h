#ifndef _ActiveStage_H_
#define _ActiveStage_H_

#include "StageBase.h"

/**
*	@class : ActiveStage
*	@brief : 无敌道具类
*/
class ActiveStage : public StageBase
{
private:
	//用于记录主角之前的生命值
	int m_iPreLife;

	//记录使用者
	Player* m_pPlayer;

	//坦克运行的无敌动画
	Animate* m_pAnimate;

	//持续时间
	float m_fMaxTime;

	//已经持续的时间
	float m_fCurTimeCount;

public:
	ActiveStage(Sprite* spSprite, TankTiledMap* pMap, float fDelayTime)
		: StageBase(spSprite, StageActive, pMap),
		m_fMaxTime(fDelayTime),
		m_fCurTimeCount(0),
		m_iPreLife(0)
	{

	}

	virtual void update(float dt) override;

	virtual void onEnter(Player* pPlayer) override;

	virtual void onExit() override;
};


#endif
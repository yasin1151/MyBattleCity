#ifndef _Player_H_
#define _Player_H_

#include "Tank\TankBase.h"
#include "PlayerState.h"
#include "Map\TankTiledMap.h"
#include "yUtils\MemPool\SimpleMemPool.h"

/**
*	@class : player
*	@brief : 抽象控制接口, 派生出玩家控制类，和ai控制类
*/
class  Player
{
protected:
	//操作的坦克实例
	TankBase* m_pTank;

	//状态模式指针
	PlayerState* m_pState;

	//状态模式内存池
	SimpleMemPool<PlayerState> m_memPoolState;

public:
	Player(TankBase* pTank);

	//虚析构函数
	virtual ~Player();

	//分发输入消息
	virtual void hanleInput(const PlayerInputType& type, Layer* layer);

	//每一帧或者间隔多少秒调用
	virtual void update(Layer* layer, float dt);

	//获取状态内存池
	SimpleMemPool<PlayerState>& getStateMemPool();

	//获取坦克实例
	TankBase* getTank();
};
#endif
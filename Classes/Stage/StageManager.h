#ifndef _StageManager_H_
#define _StageManager_H_


#include "StageBase.h"
#include "NullStage.h"
#include "SteelStage.h"
#include "ActiveStage.h"
#include "Player\Player.h"

/**
*	@class : StageManager
*	@brief : 用于道具管理
*/
class StageManager
{
private:
	//道具基类指针
	StageBase* m_pStageBase;

	//道具随机产生的位置集合
	std::vector<Vec2> m_arrRandomPos;

	//是否可以产生下一个道具
	bool m_bIsCanCreate;

	//是否产生碰撞
	bool m_bIsCollision;

public:
	StageManager();

	~StageManager();

	//用于更新道具效果
	void update(Player* pPlayer, float dt);

	//获取位置集合
	std::vector<Vec2>& getRandomPosArr();

	//加入一格位置到位置集合中
	void pushPos(const Vec2& randomPos);

	//创建下一个道具
	void createStage(TankTiledMap* pMap);

	//测试是否碰撞
	void CollisionTest(Player* pPlayer);
};

#endif
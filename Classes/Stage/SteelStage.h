#ifndef _StellStage_H_
#define _StellStage_H_

#include "StageBase.h"
#include "Map\TankTiledMap.h"
#include "Common\Common.h"
USING_NS_CC;


/**
*	@class : SteelStage
*	@brief : 用于将基地四周变成铁 
*/
class SteelStage : public StageBase
{
private:
	//总共持续的时间
	float m_fMaxTime;

	//当前已经持续的时间
	float m_fCurTimeCount;

	//用于存储基地四周的方块位置(相对于tiledmap的索引地图)
	std::vector<Vec2> m_arrHomeWallPos;

public:
	SteelStage(Sprite* spSprite,  TankTiledMap* pMap, float fMaxTime);

	virtual ~SteelStage();

	//从地图中获取数据
	bool initSteelPosFromMap();

	//设置地图的gid
	bool setHomeOtherGid(int gid);

	//更新
	virtual void update(float dt) override;

	virtual void onExit() override;

	virtual void onEnter(Player* pPlayer) override;
};

#endif
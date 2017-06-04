#ifndef _StageBase_H_
#define _StageBase_H_

#include <cocos2d.h>
#include "Map\TankTiledMap.h"
#include "Player\Player.h"
USING_NS_CC;

//道具类型枚举
typedef enum
{
	StageNull,
	StageSteel,
	StageActive,
	StageStar,
	StageTimer,
	StageBomb
}StageType;

/**
*	@class : StageBase
*	@brief : 道具基类
*/
class StageBase
{
protected:
	//道具精灵
	Sprite* m_spStage;

	//道具类型
	StageType m_eStageType;

	//当前所操作的地图
	TankTiledMap* m_pMap;

	//当前道具效果是否结束
	bool m_bIsOver;

public: 
	
	StageBase(Sprite* spSprite, const StageType& type, TankTiledMap* pMap);

	virtual ~StageBase();

	//获取道具精灵
	Sprite* getSprite();

	//设置道具类型
	void setStageType(const StageType& type);

	//获取道具类型
	StageType getStageType() const;

	//每一帧更新
	virtual void update(float dt) = 0; 

	//当道具效果结束时进行的操作
	virtual void onExit();

	//当道具效果开始时进行的操作
	virtual void onEnter(Player* pPlayer);

	//道具效果是否结束
	bool isOver() const;

};
#endif
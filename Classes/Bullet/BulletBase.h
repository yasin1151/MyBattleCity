#ifndef _BulletBase_H_
#define _BulletBase_H_

#include <cocos2d.h>
#include "Map/TankTiledMap.h"
#include "Tank/TankBase.h"
#include "Layer\GameOverLayer.h"
USING_NS_CC;

/**
*	@brief : 子弹基类
*	@class : BulletBase
*/
class BulletBase
{
protected:
	//子弹精灵
	Sprite* m_spBullet;

	//子弹速度
	Vec2 m_vSpeed;

	//地图对象
	TankTiledMap* m_pMap;

	//所属的坦克对象
	TankBase* m_pTank;
public:
	BulletBase(Sprite* spBullet, TankTiledMap* pMap, TankBase* pTank, const Vec2& vSpeed);

	virtual ~BulletBase();

	//子弹移动函数
	virtual void move();

	//子弹碰撞检测函数
	bool bulletCollision();

	//获取子弹精灵
	Sprite* getSprite();

	//设置子弹速度
	void setSpeed(const Vec2& vSpeed);

	//获取子弹速度
	Vec2 getSpeed() const;

	//设置所属坦克
	void setTank(TankBase* pTank);

	//设置所属地图
	void setTiledMap(TankTiledMap* pMap);
};

#endif
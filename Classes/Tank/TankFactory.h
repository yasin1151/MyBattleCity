#ifndef _TankFactory_H_
#define _TankFactory_H_

#include "MineTank.h"
#include "EnemyTank.h"

class TankFactory
{
private:
	//地图对象，用于传参
	TankTiledMap* m_pMap;

	//速度对象，用于传参
	Vec2 m_vInitSpeed;

public:
	TankFactory();

	TankFactory(TankTiledMap* pMap, const Vec2& vSpeed);

	//设置默认传入的速度对象
	void setInitSpeed(const Vec2& vSpeed);

	//设置默认的传入地图对象
	void setTankMap(TankTiledMap* pMap);

	//创建一个坦克对象
	TankBase* create(const TankType& tankType);
};


#endif
#ifndef _TankBase_H_
#define _TankBase_H_

#include <cocos2d.h>
#include "Map\TankTiledMap.h"
#include "Bullet\BulletManager.h"
USING_NS_CC;

/**
*	@brief : 坦克基类
*	@class : TankBase
*/

/*
	敌军坦克等级 : 绿色 -> 黄色 -> 白色 -> 红色
	我方坦克等级 : a -> b -> c 
*/
typedef enum
{
	//敌方坦克
	EnemyTankGreen,
	EnemyTankYellow,
	EnemyTankWhite,
	EnemyTankRed,

	//我方
	MineTankA,
	MineTankB,
	MineTankC
}TankType;

/**
*	对坦克进行操作命令
*/
typedef enum
{
	MoveUp = 1,
	MoveRight,
	MoveDown,
	MoveLeft,
	Shot
}TankCommandType;


class TankBase
{
protected:
	//坦克精灵
	Sprite* m_spTank;

	//坦克的类型
	TankType m_tankType;

	//是否可以移动，将碰撞检测和移动分开
	//为了ai的move
	bool m_bIsCanMoved;

	//下一个移动的位置
	Rect m_rNextMoveRect;

	//坦克行走的地图
	TankTiledMap* m_pMap;

	//坦克行走的速度，
	//最后移动 会 * tiledSize
	//即以格子为单位
	Vec2 m_vSpeed;


	//子弹管理对象
	BulletManager* m_pBulletMgr;

public:
	//传入的是一个精灵，为了灵活的使用createWithSpriteFrame();

	TankBase(Sprite* spTank, const TankType& tankType, TankTiledMap* pMap, const Vec2& speed);

	virtual ~TankBase();

	//坦克被攻击时的动作
	virtual void beAtked() = 0;

	//对坦克进行操作
	void command(const TankCommandType& type);

	//进行移动（设置到NextMoveRect位置)
	void move();

	//获取精灵
	Sprite* getSprite();

	//获取坦克类型
	TankType getTankType() const;

	//设置坦克类型
	void setTankType(const TankType& tankType);

	//是否可以移动
	bool isCanMove() const;

	//设置是否移动
	void setCanMove(bool bIsCanMove);

	//获取下一个移动的盒子
	Rect getNextMoveRect() const;

	//设置下一个移动的盒子
	void setNextMoveRect(const Rect& rect);

	//设置行走的地图
	void setMap(TankTiledMap* pMap);

	//获取行走的地图
	TankTiledMap* getMap();

	//设置移动的速度
	void setSpeed(const Vec2& speed);

	//获取移动的速度
	Vec2 getSpeed() const;

	//获取子弹管理对象
	BulletManager* getBulletMgr();
};

#endif
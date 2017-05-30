#ifndef _BulletManager_H_
#define _BulletManager_H_

#include <cocos2d.h>
#include "yUtils\MemPool\SimpleMemPool.h"

USING_NS_CC;

class BulletBase;
class TankBase;


class BulletManager
{
private:
	typedef std::list<BulletBase*> bulletListType;

	//现在在场中飞翔的子弹
	bulletListType m_listActiveBullet;

	//对象池
	SimpleMemPool<BulletBase> m_memPoolBullet;
public:
	BulletManager();

	//获取激活列表
	bulletListType& getActiveList();
	
	//获取内存池对象
	SimpleMemPool<BulletBase>& getMemPool();

	//每一帧调用
	void update(Layer* layer);

	//开火
	bool fire(const Vec2& vInitPos, const Vec2& vSpeed, TankBase* pTank);

};

#endif
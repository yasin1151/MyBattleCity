#include "BulletManager.h"
#include "BulletBase.h"

BulletManager::BulletManager()
{

}

BulletManager::bulletListType& BulletManager::getActiveList()
{
	return m_listActiveBullet;
}

SimpleMemPool<BulletBase>& BulletManager::getMemPool()
{
	return m_memPoolBullet;
}

void BulletManager::update(Layer* layer)
{
	for (auto it = m_listActiveBullet.begin();
		it != m_listActiveBullet.end();
		)
	{
		BulletBase* pBullet = *it;
		
		//如果发生碰撞或者出界
		if (pBullet->bulletCollision())
		{
			//将该节点加入对象池
			m_memPoolBullet.release(pBullet);

			//将该节点隐藏
			pBullet->getSprite()->setVisible(false);

			//将该节点从激活链表中取出
			it = m_listActiveBullet.erase(it);
		}
		else
		{
			//没有发生碰撞

			//更新位置
			pBullet->move();

			//遍历下一个节点
			++it;
		}
	}
}

bool BulletManager::fire(const Vec2& vInitPos, const Vec2& vSpeed, TankBase* pTank)
{
	//如果对象池子中没有，则创建一颗新子弹s
	BulletBase* pBullet = m_memPoolBullet.allocWithTag(0);
	if (!pBullet)
	{
		//新建一颗子弹
		pBullet = new BulletBase(Sprite::create("tank/bullet.png"),
			pTank->getMap(), pTank, vSpeed);

		if (!pBullet)
		{
			return false;
		}
		
		//设置位置
		pBullet->getSprite()->setPosition(vInitPos);
		
		//添加子弹到地图中
		pTank->getMap()->getTiledMap()->addChild(pBullet->getSprite());

		//添加子弹到对象池的已使用链表中
		m_memPoolBullet.addNewNodeToUsedList(SimpleMemPool<BulletBase>::MemTagNode(pBullet,0));
	}
	else
	{
		//有的话直接设置位置
		pBullet->getSprite()->setPosition(vInitPos);

		//设置可见
		pBullet->getSprite()->setVisible(true);

		//设置速度
		pBullet->setSpeed(vSpeed);
	}

	//加入到激活链表中
	m_listActiveBullet.push_back(pBullet);

	return true;
}
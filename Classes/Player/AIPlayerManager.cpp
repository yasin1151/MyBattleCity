#include "AIPlayerManager.h"
#include "Layer\GameLayer.h"
#include <Layer/WinLayer.h>
#include <SimpleAudioEngine.h>


AIPlayerManager::AIPlayerManager()
	:m_pUserTank(nullptr)
{

}

AIPlayerManager::~AIPlayerManager()
{

}


void AIPlayerManager::addAiPlayer(Player* pPlayer)
{
	m_listAIPlayer.push_back(pPlayer);
}

void AIPlayerManager::aiUpdte(Layer* layer, float dt)
{
	for (auto it = m_listAIPlayer.begin();
		it != m_listAIPlayer.end(); )
	{
		AIPlayer* pBuf = static_cast<AIPlayer*>(*it);
		pBuf->update(layer, dt);
		++it;
	}
}

void AIPlayerManager::collisionUpdate(Layer* layer, float dt)
{
	static float fDeletTime = 0.0f;

	fDeletTime += dt;

	GameLayer* pLayer = static_cast<GameLayer*>(layer);

	//获取用户子弹管理对象
	BulletManager* pUserBulletMgr = m_pUserTank->getBulletMgr();
	
	//我方子弹和ai坦克的碰撞检测
	auto userBulletList = pUserBulletMgr->getActiveList();
	
	for (auto it_bullet = userBulletList.begin();
		it_bullet != userBulletList.end();
		)
	{
		BulletBase* pBullet = *it_bullet;
		bool bIsClearBullet = false;
		//取出每一个ai坦克
		for (auto it = m_listAIPlayer.begin();
			it != m_listAIPlayer.end();
			)
		{
			AIPlayer* pBuf = static_cast<AIPlayer*>(*it);

			if (
				pBullet->getSprite()->isVisible() && 
				pBullet->getSprite()->getBoundingBox().intersectsRect(
				pBuf->getTank()->getNextMoveRect()))
			{
				//发生碰撞

				//移除敌军坦克
				pBuf->getTank()->beAtked();

				//如果死亡
				if (static_cast<EnemyTank*>(pBuf->getTank())->isDie())
				{
					//添加分数
					pLayer->getHudLayer()->setScore(
						pLayer->getHudLayer()->getScore() + 
						(pBuf->getTank()->getTankType() + 1) * 100);

					//从容器中移除ai玩家
					it = m_listAIPlayer.erase(it);

					auto deleteList = pBuf->getTank()->getBulletMgr()->getActiveList();
					//清理所有子弹
					for (auto it_delete = deleteList.begin();
						it_delete != deleteList.end();
						)
					{
						BulletBase* pDeleteBullet = *it_delete;
						
						//子弹回收
						pBuf->getTank()->getBulletMgr()->getMemPool().release(pDeleteBullet);

						//隐藏子弹
						pDeleteBullet->getSprite()->setVisible(false);

						//从容器中移除
						it_delete = deleteList.erase(it_delete);
					}

					//从层上移除
					pBuf->getTank()->getSprite()->removeFromParentAndCleanup(true);

					//回收内存
					delete pBuf;

					//播放被击毁的音效
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/blast.aif");

					//胜利判断
					if (m_listAIPlayer.empty() && pLayer->getHudLayer()->getRemainEnemyNum() <= 0)
					{
						//胜利
						Director::getInstance()->replaceScene(WinLayer::createScene());
					}

					

				}

				//子弹清理
				pUserBulletMgr->getMemPool().release(pBullet);

				//隐藏子弹
				pBullet->getSprite()->setVisible(false);

				//将子弹从激活列表中取出
				it_bullet = userBulletList.erase(it_bullet);

				bIsClearBullet = true;

				break;
			}
			else
			{
				++it;
			}

		}

		if (!bIsClearBullet)
		{
			++it_bullet;
		}

	}



	//ai子弹和用户坦克碰撞检测
	for (auto it = m_listAIPlayer.begin();
		it != m_listAIPlayer.end();)
	{
		AIPlayer* pBuf = static_cast<AIPlayer*>(*it);
		BulletManager* pBufBulletMgr = pBuf->getTank()->getBulletMgr();
		auto bulletList = pBufBulletMgr->getActiveList();


		//每一个ai的子弹列表
		for ( auto it_bullet = bulletList.begin();
			it_bullet != bulletList.end(); )
		{
			BulletBase* pBullet = *it_bullet;
			if (
				pBullet->getSprite()->isVisible() && 
				pBullet->getSprite()->getBoundingBox().intersectsRect(
				m_pUserTank->getNextMoveRect()))
			{
				//用户被攻击
				m_pUserTank->beAtked();

				//子弹消失
				pBufBulletMgr->getMemPool().release(pBullet);

				//将子弹隐藏
				pBullet->getSprite()->setVisible(false);

				//将子弹从列表中移除
				it_bullet = bulletList.erase(it_bullet);

				break;
			}
			else
			{
				++it_bullet;
			}
		}

		++it;
	}

	for (auto it : m_listAIPlayer)
	{
		it->getTank()->getBulletMgr()->update(layer);
	}

	//移动
	pUserBulletMgr->update(layer);
}

void AIPlayerManager::setUserTank(TankBase* pUserTank)
{
	m_pUserTank = pUserTank;
}

size_t AIPlayerManager::getAIPlayerNum() const
{
	return m_listAIPlayer.size();
}

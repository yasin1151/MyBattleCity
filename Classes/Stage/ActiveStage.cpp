#include "ActiveStage.h"
#include "Tank/MineTank.h"

void ActiveStage::update(float dt)
{
	m_fCurTimeCount += dt;

	if (m_fCurTimeCount - m_fMaxTime >= 0.001f)
	{
		//结束
		m_bIsOver = true;
	}
}

void ActiveStage::onEnter(Player* pPlayer)
{
	MineTank* pTank = static_cast<MineTank*>(pPlayer->getTank());
	m_iPreLife = pTank->getLife();
	m_pPlayer = pPlayer;

	//设置成无限血
	pTank->setLife(MY_INT_MAX);

	//加上无敌动画
	//1. 创建一个空精灵
	Sprite* spAction = Sprite::create();
	//2. 加入Tank的子节点
	pTank->getSprite()->addChild(spAction, 0, 10086);
	//3. 设置位置
	spAction->setPosition(pTank->getSprite()->getContentSize() / 2);
	//4. 创建动画
	m_pAnimate = pTank->createBeAtkedAnimate(-1, 0.2f);
	//5. 让新建的精灵创建动画
	spAction->runAction(m_pAnimate);
	//6. 让精灵进行缩放
	spAction->setScale(2.0f);
}

void ActiveStage::onExit()
{
	MineTank* pTank = static_cast<MineTank*>(m_pPlayer->getTank());

	//设置回之前的血量
	pTank->setLife(m_iPreLife);

	//去掉动画
	//1. 找到播放动画的精灵
	Sprite* spAction = static_cast<Sprite*>(pTank->getSprite()->getChildByTag(10086));
	//2. 停止序列帧
	spAction->stopAllActions();
	//3. 移除精灵
	spAction->removeFromParentAndCleanup(true);
}

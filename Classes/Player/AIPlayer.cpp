#include "AIPlayer.h"
#include "Layer\GameLayer.h"

AIPlayer::~AIPlayer()
{

}

void AIPlayer::update(Layer* layer, float dt)
{
	m_fAllDelayTime += dt;

	//按照上次走的方向一直走
	int rota = m_pTank->getSprite()->getRotation();
	m_pTank->command(static_cast<TankCommandType>(rota / 90 + 1));

	//1s开一次开火
	if (m_fAllDelayTime - 1.0f >= -0.0001f)
	{
		m_pTank->command(Shot);
		m_fAllDelayTime = 0.0f;
	}

	//如果当前方向不可以走，则换一个方向
	if (!m_pTank->isCanMove())
	{
		m_pTank->getSprite()->setRotation(static_cast<int>(rand() % 4) * 90);
	}

	m_pTank->move();
}

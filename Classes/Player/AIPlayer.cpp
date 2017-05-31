#include "AIPlayer.h"
#include "Layer\GameLayer.h"

AIPlayer::~AIPlayer()
{

}

void AIPlayer::update(Layer* layer)
{
	//按照上次走的方向一直走
	int rota = m_pTank->getSprite()->getRotation();
	m_pTank->command(static_cast<TankCommandType>(rota / 90 + 1));

	//开火
	m_pTank->command(Shot);

	//如果当前方向不可以走，则换一个方向
	if (!m_pTank->isCanMove())
	{
		m_pTank->getSprite()->setRotation(static_cast<int>(rand() % 4) * 90);
	}

	m_pTank->move();
}

#ifndef _AIPlayer_H_
#define _AIPlayer_H_

#include "Player.h"

class AIPlayer : public Player
{
private:
	bool m_bIsDie;
public:
	virtual ~AIPlayer() override;
	virtual void update(Layer* layer) override;

	explicit AIPlayer(TankBase* pTank)
		: Player(pTank),
		m_bIsDie(false)
	{

	}

	bool isDie() const
	{
		return m_bIsDie;
	}

	void setIsDie(bool bIsDie)
	{
		m_bIsDie = bIsDie;
	}
};

#endif

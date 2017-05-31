#ifndef _AIPlayer_H_
#define _AIPlayer_H_

#include "Player.h"

class AIPlayer : public Player
{
private:
	float m_fAllDelayTime;
	bool m_bIsDie;
public:
	virtual ~AIPlayer() override;
	virtual void update(Layer* layer, float dt) override;

	explicit AIPlayer(TankBase* pTank)
		: Player(pTank),
		m_bIsDie(false),
		m_fAllDelayTime(0.0f)
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

#ifndef _UserPlayer_H_
#define _UserPlayer_H_

#include "Player.h"

class UserPlayer : public Player
{
public:
	UserPlayer(TankBase* pTank)
		: Player(pTank)
	{
	}


};

#endif
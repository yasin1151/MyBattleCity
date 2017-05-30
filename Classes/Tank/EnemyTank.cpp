#include "EnemyTank.h"

EnemyTank::~EnemyTank()
{

}

void EnemyTank::beAtked()
{
	//每被攻击一次，都会改变颜色，直到死亡
	switch (m_tankType)
	{
	case EnemyTankGreen: 
		//死亡
		m_bIsDie = true;
		break;
	case EnemyTankYellow:
		m_tankType = EnemyTankGreen;
		break;
	case EnemyTankWhite: 
		m_tankType = EnemyTankYellow;
		break;
	case EnemyTankRed: 
		m_tankType = EnemyTankWhite;
		break;
	}
}

#ifndef _AIPlayerManager_H_
#define _AIPlayerManager_H_

#include "AIPlayer.h"
#include "Bullet\BulletBase.h"
#include "Tank\EnemyTank.h"


class AIPlayerManager
{
private:
	//ai玩家数组
	std::list<Player*> m_listAIPlayer;

	//用户操作的坦克
	TankBase* m_pUserTank;

public:
	AIPlayerManager();

	~AIPlayerManager();

	//添加一个ai玩家到管理中来
	void addAiPlayer(Player* pPlayer);

	//ai更新
	void aiUpdte(Layer* layer, float dt);

	//碰撞检测更新
	void collisionUpdate(Layer* layer, float dt);

	//设置用户操作的坦克
	void setUserTank(TankBase* pUserTank);

	//获取ai玩家数目
	size_t getAIPlayerNum() const;

};

#endif
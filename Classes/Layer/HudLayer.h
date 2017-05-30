#ifndef _HudLayer_H_
#define _HudLayer_H_

#include <cocos2d.h>
USING_NS_CC;

class HudLayer : public Layer
{
private:
	//还未出场的敌军的数目，固定不变
	int m_iEnemyNum;

	//当前还未出场的敌军数目
	int m_iCurEnemyNum;

	//未出场敌军列表的第一个显示的位置
	Vec2 m_vFirstEnemyPos;

	//用于显示未出场的敌军
	std::vector<Sprite*> m_arrEnemySp;


	//当前玩家的得分
	int m_iScore;

	//当前玩家得分Label,用于显示
	Label* m_pScoreLabel;

	//当前的关卡等级
	int m_iCurLevel;

	//当前的关卡等级，用于显示
	Label* m_pCurLevel;

	//玩家剩下的生命数目
	int m_iLife;

	//当前玩家剩余的生命，用于显示
	Label* m_pLifeLabel;

	//是否更新了数据
	bool m_bIsUpdata;


	//刷新当前层显示的数据
	void flushShow();

public:
	static HudLayer* create(int iCurLevel, int iLife, int iEnemyNum);

	bool init(int iCurLevel, int iLife, int iEnemyNum);

	virtual void update(float dt) override;

	//获取剩下的敌军数目
	int getRemainEnemyNum() const
	{
		return m_iCurEnemyNum;
	}

	//设置剩下的敌军数目
	void setRemainEnemyNum(int iEnemyNum)
	{
		m_iCurEnemyNum = iEnemyNum;
		m_bIsUpdata = true;
	}

	//获取当前玩家的得分
	int getScore() const
	{
		return m_iScore;
	}

	//设置当前玩家的得分
	void setScore(int iScore)
	{
		m_iScore = iScore;
		m_bIsUpdata = true;
	}

	//获取当前关卡等级
	int getCurLevel() const
	{
		return m_iCurLevel;
	}

	//设置当前关卡等级
	void setCurLevel(int iCurLevel)
	{
		m_iCurLevel = iCurLevel;
		m_bIsUpdata = true;
	}

	//设置玩家的生命数
	int getLifeNum() const
	{
		return m_iLife;
	}

	//获取玩家的生命数目
	void setLifeNum(int iLife)
	{
		m_iLife = iLife;
		m_bIsUpdata = true;
	}

	//获取未出场敌军列表的第一个显示的位置
	Vec2 getFirstEnemyPos() const
	{
		return m_vFirstEnemyPos;
	}

	void setFirstEnemyPos(const Vec2& pos)
	{
		m_vFirstEnemyPos = pos;
		m_bIsUpdata = true;
	}


};

#endif
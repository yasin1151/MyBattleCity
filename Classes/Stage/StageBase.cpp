#include "StageBase.h"

StageBase::StageBase(Sprite* spSprite, const StageType& type, TankTiledMap* pMap)
	:m_spStage(spSprite),
	m_eStageType(type),
	m_pMap(pMap),
	m_bIsOver(false)
{

}

StageBase::~StageBase()
{
	if (m_spStage)
	{
		m_spStage->removeFromParentAndCleanup(true);
	}
}

Sprite* StageBase::getSprite()
{
	return m_spStage;
}

void StageBase::setStageType(const StageType& type)
{
	m_eStageType = type;
}

StageType StageBase::getStageType() const
{
	return m_eStageType;
}

void StageBase::onExit()
{

}

void StageBase::onEnter(Player* pPlayer)
{

}

bool StageBase::isOver() const
{
	return m_bIsOver;
}

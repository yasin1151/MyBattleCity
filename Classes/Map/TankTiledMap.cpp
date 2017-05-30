#include "TankTiledMap.h"

TankTiledMap* TankTiledMap::createWithTmxFile(const std::string& fileName)
{
	TankTiledMap* pRet = new TankTiledMap();
	if (pRet && pRet->initWithTmxFile(fileName))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool TankTiledMap::initWithTmxFile(const std::string& fileName)
{
	m_pMap = TMXTiledMap::create(fileName);
	m_pLayer0 = m_pMap->getLayer("layer_0");
	m_pLayer1 = m_pMap->getLayer("layer_1");
	return true;
}

TMXTiledMap* TankTiledMap::getTiledMap()
{
	return m_pMap;
}

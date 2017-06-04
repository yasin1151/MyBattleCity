#include "SteelStage.h"

SteelStage::SteelStage(Sprite* spSprite, TankTiledMap* pMap, float fMaxTime)
	:StageBase(spSprite, StageSteel, pMap),
	m_fMaxTime(fMaxTime),
	m_fCurTimeCount(0)
{
	initSteelPosFromMap();
}

SteelStage::~SteelStage()
{
	
}

bool SteelStage::initSteelPosFromMap()
{
	assert(nullptr != m_pMap);

	TMXObjectGroup* pObjects = m_pMap->getTiledMap()->getObjectGroup("objects");


	//获取地图相关大小
	Size mapSize = m_pMap->getTiledMap()->getContentSize();
	Size tiledSize = m_pMap->getTiledMap()->getTileSize();

	//获取对应的参数对象
	ValueMap homePos = pObjects->getObject("mapLeftDownBegin");

	//获取相对与tiledMap的索引x,y
	int x = homePos["x"].asInt() / tiledSize.width;
	int y = (mapSize.height - homePos["y"].asInt()) / tiledSize.height;

	//加入到数组中

	//左边墙
	m_arrHomeWallPos.push_back(Vec2(x, y));
	m_arrHomeWallPos.push_back(Vec2(x, y - 1));

	//家的屋顶
	m_arrHomeWallPos.push_back(Vec2(x, y - 2));
	m_arrHomeWallPos.push_back(Vec2(x + 1, y - 2));
	m_arrHomeWallPos.push_back(Vec2(x + 2, y - 2));
	m_arrHomeWallPos.push_back(Vec2(x + 3, y - 2));

	//右边墙
	m_arrHomeWallPos.push_back(Vec2(x + 3, y - 1));
	m_arrHomeWallPos.push_back(Vec2(x + 3, y));

	return true;
}

bool SteelStage::setHomeOtherGid(int gid)
{
	TMXLayer* pLayer = m_pMap->getTiledMap()->getLayer("layer_0");
	for (auto it : m_arrHomeWallPos)
	{
		pLayer->setTileGID(gid, it);
	}
	return true;
}

void SteelStage::update( float dt)
{
	if (m_bIsOver)
	{
		return;
	}

	m_fCurTimeCount += dt;
	//如果持续时间过了
	if (m_fCurTimeCount - m_fMaxTime >= 0.001f)
	{
		m_bIsOver = true;
		return;
	}
	else if (m_fMaxTime - m_fCurTimeCount > 0.001f &&
		m_fMaxTime - m_fCurTimeCount < m_fMaxTime / 2)
	{
		//如果剩余时间在2s以内
		//开始闪烁
		static float fFadeTime = 0;
		if (fFadeTime >= -0.001f && 
			fFadeTime < 0.001f)
		{
			//设置铁
			setHomeOtherGid(MAP_STEEL);
		}
		else if (fFadeTime >= 0.4f)
		{
			fFadeTime = 0;
			//设置墙体
			setHomeOtherGid(MAP_WALL);
			return;
		}

		fFadeTime += dt;
	}
	
}

void SteelStage::onExit()
{
	//设置回墙体
	setHomeOtherGid(MAP_WALL);
}

void SteelStage::onEnter(Player* pPlayer)
{
	//设置成铁
	setHomeOtherGid(MAP_STEEL);
}

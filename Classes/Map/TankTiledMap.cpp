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




bool TankTiledMap::isCollision(const Rect& tankBoundingBox, Vec2& offsetPos)
{
	//log("isCollision");
	int gid = 0;
	//地图大小
	Size mapSize = m_pMap->getContentSize();
	//每一片瓦片的大小
	Size tileSize = m_pMap->getTileSize();

	//越界检测
	if (tankBoundingBox.getMinX() < 0.01 || tankBoundingBox.getMaxX() >= mapSize.width ||
		tankBoundingBox.getMinY() < 0.01 || tankBoundingBox.getMaxY() >= mapSize.height)
	{
		return true;
	}

	//将cocos坐标系，转换为tiled坐标系
	int minY = mapSize.height - tankBoundingBox.getMinY();
	int maxY = mapSize.height - tankBoundingBox.getMaxY();
	int midY = mapSize.height - tankBoundingBox.getMidY();

	//获取8个顶点的坐标
	Vec2 arrVec[] = {
		//左上角
		Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)),

		//右上角
		Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)),

		//左下角
		Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)),

		//右下角
		Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)),

		//上中
		Vec2(
		static_cast<int>(tankBoundingBox.getMidX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)),

		//左中
		Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(midY / tileSize.height)),

		//右中
		Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(midY / tileSize.height)),

		//下中
		Vec2(
		static_cast<int>(tankBoundingBox.getMidX() / tileSize.width),
		static_cast<int>(minY / tileSize.height))
	};

	//遍历arrVec
	for (int i = 0; i < 8; i++)
	{
		gid = m_pLayer0->getTileGIDAt(arrVec[i]);
		if (gid != 0)
		{
//			//生成有碰撞的Rect
//			Rect tiledRect = Rect(
//				arrVec[i].x * tileSize.width,
//				arrVec[i].y * tileSize.height,
//				tileSize.width,
//				tileSize.height
//				);
//			//计算一个单位offset，传回给调用者，并用调用者的速度进行缩放
//
//			offsetPos = Vec2(tankBoundingBox.getMinX() - tiledRect.getMinX(),
//				tankBoundingBox.getMinY() - tiledRect.getMinY());
//
//			offsetPos.normalize();

			//进行一个偏移量的计算
			return true;
		}
	}

	return false;
}
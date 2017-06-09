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



int TankTiledMap::findMinDisPos( int arrGid[], int iArrSize, int iRota)
{
	/**
	0 1
	2 3
	**/

	int iFirst = 0;
	int iSecond = 0;


	switch (iRota)
	{
	case 0:
		iFirst = 0;
		iSecond = 1;
		break;
	case 90:
		iFirst = 1;
		iSecond = 3;
		break;
	case 180:
		iFirst = 2;
		iSecond = 3;
		break;
	case 270:
		iFirst = 0;
		iSecond = 2;
		break;

	}

	if ((arrGid[iFirst] == 0 && arrGid[iSecond] == 0) ||
		(arrGid[iFirst] != 0 && arrGid[iSecond] != 0))
	{
		//全为相同
		return -1;
	}
	else if (arrGid[iFirst] != 0 && arrGid[iSecond] == 0)
	{
		return iFirst;
	}
	else if (arrGid[iFirst] == 0 && arrGid[iSecond] != 0)
	{
		return iSecond;
	}

	return -1;
}


bool TankTiledMap::isCollision(const Rect& tankBoundingBox, Vec2& offsetPos, bool isUseOffset, int iRota)
{
	//log("isCollision");
	int gid = 0;
	//地图大小
	Size mapSize = m_pMap->getContentSize();
	//每一片瓦片的大小
	Size tileSize = m_pMap->getTileSize();
	//发生了碰撞，但是没有把对角的四个点判断完
	bool bIsCollAndNotFinal = false;

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

	int arrGid[8] = {};

	//遍历arrVec
	for (int i = 0; i < 8; i++)
	{
		gid = m_pLayer0->getTileGIDAt(arrVec[i]);
		arrGid[i] = gid;
		if (gid != 0 || bIsCollAndNotFinal)
		{
			//如果不弃用修正
			if (!isUseOffset)
			{
				//直接返回
				return true;
			}
			else if (3 > i)
			{
				//如果没有判断完上下左右，则不进入修正
				bIsCollAndNotFinal = true;
				continue;
			}

			//获取坦克中点位置
			Vec2 vecMidPos = Vec2(
				static_cast<int>(tankBoundingBox.getMidX() / tileSize.width),
				static_cast<int>(midY / tileSize.height));

			//获取碰撞面的碰撞点
			int iBuf = findMinDisPos(arrGid, 4, iRota);

			//错误检测
			if (iBuf < 0)
			{
				return true;
			}

			//log("index : %d", iBuf);
			
			offsetPos = Vec2(
				vecMidPos.x- arrVec[iBuf].x,
				arrVec[iBuf].y - vecMidPos.y
				);

			//如果是在y轴上
			if (0 == iRota || 180 == iRota)
			{
				offsetPos.y = 0;
			} 
			else if (90 == iRota || 270 == iRota)
			{
				//x轴上
				offsetPos.x = 0;
			}

			//log("before normalize : offsetPos : %0.2f , %0.2f", offsetPos.x, offsetPos.y);

			//进行一个偏移量的计算
			return true;
		}
	}

	return false;
}
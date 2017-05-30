#include "BulletBase.h"
#include <SimpleAudioEngine.h>


BulletBase::BulletBase(Sprite* spBullet, TankTiledMap* pMap, TankBase* pTank, const Vec2& vSpeed)
	:m_spBullet(spBullet),
	m_pMap(pMap),
	m_pTank(pTank),
	m_vSpeed(vSpeed)
{

}

BulletBase::~BulletBase()
{

}

void BulletBase::move()
{
	m_spBullet->setPosition(m_spBullet->getPosition() + m_vSpeed);
}

bool BulletBase::bulletCollision()
{
	Rect bulletRect = m_spBullet->getBoundingBox();
	Size mapSize = m_pMap->getTiledMap()->getContentSize();

	//边界检查
	if (bulletRect.getMinX() < 0 || bulletRect.getMaxX() >= mapSize.width ||
		bulletRect.getMinY() < 0 || bulletRect.getMaxY() >= mapSize.height)
	{
		return true;
	}

	//将cocos坐标系调整到tiled坐标系
	TMXLayer* pTxmLayer = m_pMap->getTiledMap()->getLayer("layer_0");
	Size tiledSize = m_pMap->getTiledMap()->getTileSize();

	float fMinY = mapSize.height - bulletRect.getMinY();
	float fMaxY = mapSize.height - bulletRect.getMaxY();

	bool bIsCollision = false;

	//将与子弹进行碰撞的砖块删除掉
	
	//获取行走层
	TMXLayer* pLayer = m_pMap->getTiledMap()->getLayer("layer_0");


	Vec2 arrVec[4] = {
		//1.1 左上角
		Vec2(
		static_cast<int>(bulletRect.getMinX() / tiledSize.width),
		static_cast<int>(fMaxY / tiledSize.height)),

		//2.1 右上角
		Vec2(
		static_cast<int>(bulletRect.getMaxX() / tiledSize.width),
		static_cast<int>(fMaxY / tiledSize.height)),

		//3.1 左下角
		Vec2(
		static_cast<int>(bulletRect.getMaxX() / tiledSize.width),
		static_cast<int>(fMinY / tiledSize.height)),

		//4.1 右下角
		Vec2(
		static_cast<int>(bulletRect.getMinX() / tiledSize.width),
		static_cast<int>(fMinY / tiledSize.height))

	};

	//遍历arrVec
	for (int i = 0; i < 4; i++)
	{
		switch (gid2Type[pLayer->tileGIDAt(arrVec[i])])
		{
		case MapWall:
			//消除方块
			pLayer->setTileGID(0, arrVec[i]);
			bIsCollision = true;
			
			break;
		case MapSteel:
			//消除子弹
			bIsCollision = true;
			break;
		case MapRiver: 
			//不做处理

			break;
		case MapHome:
			//游戏结束
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
			Director::getInstance()->replaceScene(GameOverLayer::createScene());
			break;
		}
	}

//	//1.1 左上角
//	Vec2 vBuf = Vec2(
//		static_cast<int>(bulletRect.getMinX() / tiledSize.width),
//		static_cast<int>(fMaxY / tiledSize.height));
//
//	//1.2 将与子弹碰撞的wall删除
//	if (MapWall == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		//删除
//		pLayer->setTileGID(0, vBuf);
//		bIsCollision = true;
//	}
//	else if (MapSteel == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		bIsCollision = true;
//	}
//
//
//	//2.1 右上角
//	vBuf = Vec2(
//		static_cast<int>(bulletRect.getMaxX() / tiledSize.width),
//		static_cast<int>(fMaxY / tiledSize.height));
//
//	//2.2
//	if (MapWall == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		//删除
//		pLayer->setTileGID(0, vBuf);
//		bIsCollision = true;
//	}
//	else if (MapSteel == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		bIsCollision = true;
//	}
//
//
//	//3.1 左下角
//	vBuf = Vec2(
//		static_cast<int>(bulletRect.getMaxX() / tiledSize.width),
//		static_cast<int>(fMinY / tiledSize.height));
//
//	//3.2
//	if (MapWall == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		//删除
//		pLayer->setTileGID(0, vBuf);
//		bIsCollision = true;
//	}
//	else if (MapSteel == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		bIsCollision = true;
//	}
//
//	//4.1 右下角
//	vBuf = Vec2(
//		static_cast<int>(bulletRect.getMinX() / tiledSize.width),
//		static_cast<int>(fMinY / tiledSize.height));
//
//
//	//4.2
//	if (MapWall == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		//删除
//		pLayer->setTileGID(0, vBuf);
//		bIsCollision = true;
//	}
//	else if (MapSteel == gid2Type[pLayer->tileGIDAt(vBuf)])
//	{
//		bIsCollision = true;
//	}


	return bIsCollision;
}

Sprite* BulletBase::getSprite()
{
	return m_spBullet;
}

void BulletBase::setSpeed(const Vec2& vSpeed)
{
	m_vSpeed = vSpeed;
}

Vec2 BulletBase::getSpeed() const
{
	return m_vSpeed;
}

void BulletBase::setTank(TankBase* pTank)
{
	m_pTank = pTank;
}

void BulletBase::setTiledMap(TankTiledMap* pMap)
{
	m_pMap = pMap;
}

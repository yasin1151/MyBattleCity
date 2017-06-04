#ifndef _TankTiledMap_H_
#define _TankTiledMap_H_

#include <cocos2d.h>
#include "Common\Common.h"
USING_NS_CC;

/**
*	@class : TankTiledMap
*	@brief : 为坦克大战的地图定制的地图类，用于坦克的碰撞检测
*/

class TankTiledMap : public Ref
{
private:
	//瓦片地图对象
	TMXTiledMap* m_pMap;

	//地图层0
	TMXLayer* m_pLayer0;

	//地图层1
	TMXLayer* m_pLayer1;

public:
	//确保地图有layer_0 和 layer_1 两个层
	static TankTiledMap* createWithTmxFile(const std::string& fileName);

	bool initWithTmxFile(const std::string& fileName);

	//获取瓦片地图对象
	TMXTiledMap* getTiledMap();

	//检测碰撞，true为碰撞，false为无碰撞, 可以指定碰撞函数
	template <typename CollisionFunc>
	bool isCollision(const Rect& tankBoundingBox, CollisionFunc func = [=](int gid){return gid != 0; });
};



template <typename CollisionFunc>
bool TankTiledMap::isCollision(const Rect& tankBoundingBox, CollisionFunc func)
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

	//坦克只占用4个格子
	//所以只用进行4个顶点的碰撞检测

	//1.1 获取左上角tileMapGid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)));

	//log("collision1 gid : %d", gid); 

	//1.2 判断gid是否为空，或者特殊值
	if (func(gid))
	{
		return true;
	}

	//2.1 获取右上角的gid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(maxY / tileSize.height)));
	//log("collision2 gid : %d", gid);

	//2.2 
	if (func(gid))
	{
		return true;
	}

	//3.1 获取左下角gid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMinX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)));
	//log("collision3 gid : %d", gid);

	//3.2
	if (func(gid))
	{
		return true;
	}

	//4.1 获取右下角gid
	gid = m_pLayer0->getTileGIDAt(Vec2(
		static_cast<int>(tankBoundingBox.getMaxX() / tileSize.width),
		static_cast<int>(minY / tileSize.height)));
	//log("collision4 gid : %d", gid);

	//4.2
	if (func(gid))
	{
		return true;
	}

	return false;
}

#endif

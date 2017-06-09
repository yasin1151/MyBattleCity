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

	//去找离指定点最近的位置，返回arrPos中的位置
	int findMinDisPos(int arrGid[], int iArrSize, int iRota);

public:
	//确保地图有layer_0 和 layer_1 两个层
	static TankTiledMap* createWithTmxFile(const std::string& fileName);

	bool initWithTmxFile(const std::string& fileName);

	//获取瓦片地图对象
	TMXTiledMap* getTiledMap();

	/**
	*	@brief : 用于碰撞检测
	*	@param tankBoundingBox : 坦克的碰撞检测盒子
	*	@param offfsetPos : 用于回传的偏移量，如果isUseOffset为false，则不会回传
	*	@param isUseOffset : 是否使用偏移量处理
	*	@param iRota : 当前旋转的方向
	*	@return : 如果发生碰撞，返回true, 如果未发生碰撞，返回false
	*/
	bool isCollision(const Rect& tankBoundingBox, Vec2& offsetPos, bool isUseOffset, int iRota = 0);
};



#endif

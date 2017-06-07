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

	//检测碰撞，true为碰撞，false为无碰撞，传入一个Vec&， 可以对当前位置进行修正，优化用户体验
	bool isCollision(const Rect& tankBoundingBox, Vec2& offsetPos);
};



#endif

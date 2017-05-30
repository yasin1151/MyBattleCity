#ifndef _Common_H_
#define _Common_H_

/**
*	@brief : 公共的全局定义
*/
#include <vector>
#include <unordered_map>
#include <string>

//地图类型枚举
typedef enum
{
	//空地图
	MapNone,
	//草
	MapGrass,
	//墙
	MapWall,
	//铁
	MapSteel,
	//河流
	MapRiver,
	//家
	MapHome
}TiledMapType;


/**
*	@brief : 用于地图的碰撞检测
*/
static std::unordered_map<int, TiledMapType> gid2Type = {
	
	{ 5, MapSteel },
	{ 6, MapSteel },
	{ 11, MapSteel },
	{ 12, MapSteel },

	{ 13, MapWall },
	{ 14, MapWall },
	{ 19, MapWall },
	{ 20, MapWall },

	{ 15, MapRiver },
	{ 16, MapRiver },
	{ 21, MapRiver },
	{ 22, MapRiver },

	{ 17, MapHome },
	{ 18, MapHome },
	{ 23, MapHome },
	{ 24, MapHome },
};



#endif
#ifndef __Rocker4A__H__
#define __Rocker4A__H__

#include "RockerBase.h"

/*
	@class : Rocker4A
	@brief : 四个方向的摇杆
*/
class Rocker4A : public RockerBase
{
protected:
	
	/*
		@brief : 重写父类的setState方法，
				 本类只实现4个方向的状态
	*/
	virtual void setState(float radian) override;

public:
	/*
	@brief : 创建一个摇杆
	@param szBgFileName : 背景图片文件名
	@param szRockerFileName : 摇杆图片文件名
	@param pos : 初始坐标点
	*/
	static Rocker4A* create(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos);
};

#endif
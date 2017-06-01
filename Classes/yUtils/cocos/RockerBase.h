#ifndef __RockerBase__H__
#define __RockerBase__H__

#include "cocos2d.h"
#include "yUtils\Helper\yUtils.h"

USING_NS_CC;

enum class RockerState : int
{
	Stay,
	Up,
	Down,
	Left,
	Right,
	LeftUp,
	LeftDown,
	RightUp,
	RightDown
};

/*
	@class : RockerBase
	@brief : 摇杆类
*/
class RockerBase : public Layer
{
protected:
	Sprite* m_spBg;
	Sprite* m_spRocker;
	bool m_bIsTouchRocker;			//是否触摸到摇杆
	int m_iState;					//当前运动的方向


	/*
		@brief :onTouchMoved调用，传入一个弧度（-pi ~ pi） 
				通过弧度来设置当前运动的方向,
				可以通过重写该方法来扩展设置的状态
		@param radian : 弧度()
	*/
	virtual void setState(float radian) = 0;

	/*
		@brief : 通过create调用的初始化方法
		@param szBgFileName : 背景图片文件名
		@param szRockerFileName : 摇杆图片文件名
		@param pos : 初始坐标点
	*/

public:

	RockerBase();
	
	virtual ~RockerBase();

	bool init(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos);

	/*
		@brief : 初始化touch事件
				 子类可以重写这个方法来替换父类的onTouch函数
	*/
	virtual void initTouchEvent();

	/*
		@brief : 获得当前运动的状态
	*/
	RockerState getState() const;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;

	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;

	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;

};


#endif
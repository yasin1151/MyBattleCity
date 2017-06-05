#ifndef __Rocker4AWithTrans__H__
#define __Rocker4AWithTrans__H__

#include "Rocker4A.h"


//为触摸区域赋值的宏定义
//左下，宽为1/3, 高为3/4 可视区域
#define ROCKER_LD \
	(Rect(0, 0, Director::getInstance()->getVisibleSize().width / 3,\
		Director::getInstance()->getVisibleSize().height * 3 / 4))
//右下，宽为1/3, 高为3/4 可视区域
#define ROCKER_RD \
	(Rect(Director::getInstance()->getVisibleSize().width * 2 / 3, 0, \
		Director::getInstance()->getVisibleSize().width / 3, \
		Director::getInstance()->getVisibleSize().height * 3 / 4))

/*
	@class : Rocker4AWithTrans
	@brief : 一个只标明4个方向，并且在一定区域显示的摇杆
*/
class Rocker4AWithTrans : public Rocker4A
{
protected:
	Rect m_touchRect;		//在这个区域内进行触摸才会显示摇杆

	/*
		@brief : 显示并设置摇杆的位置
		@param pos : 摇杆的位置
	*/
	void setRockerPosWithShow(const Vec2& pos);

	/*
		@brief : 设置摇杆的显示与否
		@param bIsShow : 是否显示
	*/
	void setRockerShow(bool bIsShow);
public:
	static Rocker4AWithTrans* create(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos, const Rect& touchRect);

	bool init(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos, const Rect& touchRect); 

	virtual void initTouchEvent() override;

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;

	virtual void onTouchEnded(Touch *touch, Event *unused_event) override;

};


#endif
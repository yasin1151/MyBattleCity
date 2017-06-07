#ifndef _CalcCountLayer_H_
#define _CalcCountLayer_H_

#include <cocos2d.h>
#include "yUtils/Helper/yUtils.h"
USING_NS_CC;

/**
*	@class : CalcCountLayer
*	@brief : 结算界面
*/
class CalcCountLayer : public Layer
{
private:
	//最后分数
	int m_iScore;

	//当前关卡
	int m_iCurLevel;

	//最大关卡数目
	static int m_iMaxLevelCount;

	//保存配置参数
	ValueMap m_vConfig;
public:
	static Scene* createScene(int iScore, int iCurLevel);

	bool init(int iScore, int iCurLevel);

	static CalcCountLayer* create(int iScore, int iCurLevel);

	//设置最大的关卡数目,用于判断是否能进入下一关
	static void setMaxLevelCount(int iCount);

	void nextLayer();
};

#endif
#ifndef _WinLayer_H_
#define _WinLayer_H_

#include <cocos2d.h>
USING_NS_CC;

class WinLayer : public Layer
{
public:
	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(WinLayer);
};

#endif

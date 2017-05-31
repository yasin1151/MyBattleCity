#ifndef _MenuLayer_H_
#define _MenuLayer_H_

#include <cocos2d.h>
#include "GameLayer.h"

USING_NS_CC;

class MenuLayer : public Layer
{
public:
	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(MenuLayer);

	MenuLayer();

	virtual ~MenuLayer();
};


#endif
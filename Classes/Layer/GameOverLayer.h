#ifndef _GameOverLayer_H_
#define _GameOverLayer_H_

#include <cocos2d.h>
USING_NS_CC;

class GameOverLayer : public Layer
{
public:
	static Scene* createScene();

	virtual bool init() override;

	CREATE_FUNC(GameOverLayer);
};

#endif

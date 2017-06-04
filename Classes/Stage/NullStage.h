#ifndef _NullStage_H_
#define _NullStage_H_


#include "StageBase.h"

/**
*	@class : NullStage
*	@brief : 用于标识空道具状态
*/
class NullStage : public StageBase
{
public:
	virtual void update(float dt) override
	{

	}

	NullStage()
		: StageBase(nullptr, StageNull, nullptr)
	{

	}
};

#endif

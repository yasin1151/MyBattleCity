#ifndef _BULLET_CONFIG_HANDLER_H_
#define _BULLET_CONFIG_HANDLER_H_

#include "Common/BulletConfigCommon.h"
#include "HandlerTemplate.h"
#include "../../Tmp/CSingleInstanceTmp.h"

namespace yUtils
{
	class CBulletConfigHandler : public HandlerTemplate < CBulletConfigNode >,
								 public CSingleInstanceTmp < CBulletConfigHandler >
	{
	public:
		CBulletConfigNode* at(int typeID);
	};
}


#endif
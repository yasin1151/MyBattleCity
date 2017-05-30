#ifndef _MONSTER_CONFIG_HANDLER_H_
#define _MONSTER_CONFIG_HANDLER_H_

#include "../../../Common/MonsterConfigCommon.h"
#include "../../Tmp/CSingleInstanceTmp.h"
#include "HandlerTemplate.h"

namespace yUtils
{
	class CMonsterConfigHandler : public HandlerTemplate< CMonsterConfigNode > ,
								public CSingleInstanceTmp< CMonsterConfigHandler >
	{
	public:
		CMonsterConfigNode* at(int typeId);
	};
}
	



#endif
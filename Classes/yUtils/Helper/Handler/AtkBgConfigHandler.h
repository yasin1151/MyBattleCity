#ifndef _ATK_BG_CONFIG_HANLDER_H_
#define _ATK_BG_CONFIG_HANDLER_H_


#include "Common/AtkBgConfigCommon.h"
#include "../../Tmp/CSingleInstanceTmp.h"
#include "HandlerTemplate.h"

namespace yUtils
{
	class CAtkBgConfigHandler : public HandlerTemplate< CAtkBgConfigNode >,
								public CSingleInstanceTmp< CAtkBgConfigHandler >
	{
	public:
		CAtkBgConfigNode* at(int id);
	};
}

#endif
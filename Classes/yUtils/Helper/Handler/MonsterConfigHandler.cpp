#include "MonsterConfigHandler.h"

namespace yUtils
{
	CMonsterConfigNode* CMonsterConfigHandler::at(int typeId)
	{
		for (auto it : m_arr)
		{
			if (it->iMonsterTypeId == typeId)
			{
				return it;
			}
		}
		return nullptr;
	}
}

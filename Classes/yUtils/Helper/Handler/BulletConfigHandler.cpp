#include "BulletConfigHandler.h"

namespace yUtils
{
	CBulletConfigNode* CBulletConfigHandler::at(int typeID)
	{
		for (auto i : m_arr)
		{
			if (i->iTypeId == typeID)
			{
				return i;
			}
		}
		return nullptr;
	}
}

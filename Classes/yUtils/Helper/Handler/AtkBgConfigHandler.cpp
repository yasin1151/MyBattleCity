#include "AtkBgConfigHandler.h"

namespace yUtils
{
	CAtkBgConfigNode* CAtkBgConfigHandler::at(int id)
	{
		for (auto i : m_arr)
		{
			if (i->iId == id)
			{
				return i;
			}
		}
	}
}

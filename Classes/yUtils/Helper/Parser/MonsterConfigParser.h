#ifndef _MONSTER_CONFIG_PARSER_H_
#define _MONSTER_CONFIG_PARSER_H_
#include "AbsParser.h"
#include "../tinyxml2.h"
#include "../Handler/MonsterConfigHandler.h"

namespace yUtils
{
	class CMonsterConfigParser : public CAbsParser
	{
	public:
		bool Parse(const char* fileName) override;
	};

}

#endif
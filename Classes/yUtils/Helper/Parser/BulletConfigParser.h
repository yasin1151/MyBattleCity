#ifndef _BULLET_CONFIG_PARSER_H_
#define _BULLET_CONFIG_PARSER_H_

#include "AbsParser.h"
#include "../tinyxml2.h"
#include "../Handler/BulletConfigHandler.h"

namespace yUtils
{
	class CBulletConfigParser : public CAbsParser
	{
	public:
		bool Parse(const char* fileName) override;
	};
}

#endif
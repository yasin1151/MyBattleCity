#ifndef _ATK_BG_CONFIG_PARSER_H_
#define _ATK_BG_CONFIG_PARSER_H_

#include "AbsParser.h"
#include "../tinyxml2.h"
#include "../Handler/AtkBgConfigHandler.h"

namespace yUtils
{
	class CAtkBgConfigParser : public CAbsParser
	{
	public:
		virtual bool Parse(const char* fileName) override;
	};
}

#endif
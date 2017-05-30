/*
	name	: TaskReader.h
	auther	: PengYao
	time	: 2017/1/2
	des		: 用于实现CAbsIO的LoadXml接口
*/
#ifndef _READER_H_
#define _READER_H_

#include "AbsIO.h"

namespace Helper
{
	class CReader : public CAbsIO
	{
	public:
		CReader(const char* fileName = nullptr, const char* mode = nullptr)
			:CAbsIO(fileName, mode)
		{}

		/*
		@brief : 加载xml文件，并返回xml数据
		@param szPath : xml文件的路径
		*/
		virtual std::string LoadXml(std::string szPath) override;
	};
}
#endif
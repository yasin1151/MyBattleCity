/*
name	: TaskWriter.h
auther	: PengYao
time	: 2016/12/15
des		: 用于实现AbsTaskIO的SaveAsXml接口
*/

#ifndef _WRITER_H_
#define _WRITER_H_

#include "AbsIO.h"

namespace Helper
{
	class CWriter : public CAbsIO
	{
	public:
		CWriter(const char* fileName = nullptr, const char* mode = nullptr)
			:CAbsIO(fileName, mode)
		{}
		/*
		@brief : 保存xml文件到指定路径
		@param szData : xml数据
		@param szPath : xml保存的路径
		@return : 保存成功返回 true , 保存失败返回 false
		*/
		virtual bool SaveAsXml(std::string szDate, std::string szPath) override;
	};
}
#endif
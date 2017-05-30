#ifndef _ABS_IO_H_
#define _ABS_IO_H_

/*
	name   : AbsIO.h
	auther : PengYao
	time   : 2017/1/11
	des	   : 抽象io接口，基于我自己的yFile库，定义接口
*/

#include "../yfile.h"
#include <string>

namespace Helper
{
	class CAbsIO
	{
	protected:
		yUtils::CFile* m_cFileMgr;
	public:
		CAbsIO(const char* fileName = nullptr, const char* mode = nullptr)
		{
			m_cFileMgr = new yUtils::CFile;
			if (fileName && mode)
			{
				m_cFileMgr->load(fileName, mode);
			}
		}

		virtual ~CAbsIO()
		{
			if (m_cFileMgr)
			{
				delete m_cFileMgr;
			}
		}

		/*
			@brief : 加载xml文件
			@param szPath : xml文件的路径
			@warning : 具体实现看派生类
		*/
		virtual std::string LoadXml(std::string szPath)
		{
			return "";
		}

		/*
			@brief : 保存xml文件到指定路径
			@param szData : xml数据
			@param szPath : xml保存的路径
			@warning ； 具体实现看派生类
		*/
		virtual bool SaveAsXml(std::string szDate, std::string szPath)
		{
			return false;
		}


		//获取文件指针
		FILE* GetFilePtr() const
		{
			if (m_cFileMgr->isOpen())
			{
				return m_cFileMgr->getFilePtr();
			}
			return nullptr;
		}
	};
}

#endif
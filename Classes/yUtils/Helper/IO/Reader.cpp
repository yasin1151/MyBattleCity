#include "Reader.h"

namespace Helper
{
	std::string CReader::LoadXml(std::string szPath)
	{
		if (!m_cFileMgr->load(szPath.c_str(), "r"))
		{
			return "";
		}

		//¶ÁÈ¡
		int fileSize = m_cFileMgr->getSize();

		char* szBuf = new char[fileSize + 1];
		memset(szBuf, 0, fileSize + 1);

		if (false == m_cFileMgr->read(szBuf, fileSize))
		{
			if (fileSize > 0)
			{
				delete[] szBuf;
			}
			else
			{
				delete szBuf;
			}
			m_cFileMgr->close();
			return "";
		}
		szBuf[fileSize] = '\0';


		std::string szRetBuf = szBuf;
		if (fileSize > 0)
		{
			delete[] szBuf;
		}
		else
		{
			delete szBuf;
		}

		m_cFileMgr->close();
		return std::move(szRetBuf);
	}
}

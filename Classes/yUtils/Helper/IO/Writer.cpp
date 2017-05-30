#include "Writer.h"

namespace Helper
{

	bool CWriter::SaveAsXml(std::string szDate, std::string szPath)
	{
		if (szDate.empty())
		{
			return false;
		}

		if (!m_cFileMgr->load(szPath.c_str(), "w"))
		{
			return false;
		}

		if (!m_cFileMgr->write(szDate.c_str(), szDate.size()))
		{
			m_cFileMgr->close();
			return false;
		}

		m_cFileMgr->close();
		return true;
	}

}

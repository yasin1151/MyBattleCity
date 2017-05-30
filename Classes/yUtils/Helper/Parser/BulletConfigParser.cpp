#include "BulletConfigParser.h"

namespace yUtils
{
	bool CBulletConfigParser::Parse(const char* fileName)
	{
		if (!fileName)
		{
			return false;
		}


		using namespace tinyxml2;
		auto handler = CBulletConfigHandler::GetInstance();
		XMLDocument doc;
		doc.LoadFile(fileName);
		XMLElement* Root = doc.RootElement();


		if (!Root)
		{
			return false;
		}
		XMLElement* Node = Root->FirstChildElement();

		//临时变量声明
		int iId = 0;
		std::string szPath;
		int iAtk = 0;
		int iSpeedX = 0;
		int iSpeedY = 0;
		bool bIsHaveChild = false;
		float fAngle = 0.0f;
		int iBulletNum = 0;

		while (Node)
		{
			auto ChildNode = Node->FirstChildElement();

			iId = atoi(ChildNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();

			szPath = ChildNode->GetText();
			ChildNode = ChildNode->NextSiblingElement();

			iAtk = atoi(ChildNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();

			auto speedNode = ChildNode->FirstChildElement();
			iSpeedX = atoi(speedNode->GetText());

			speedNode = speedNode->NextSiblingElement();
			iSpeedY = atoi(speedNode->GetText());

			ChildNode = ChildNode->NextSiblingElement();

			bIsHaveChild = atoi(ChildNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();


			CBulletConfigNode* pNode;
			if (bIsHaveChild)
			{
				auto ChildConfigNode = ChildNode->FirstChildElement();
				fAngle = atof(ChildConfigNode->GetText());
				ChildConfigNode = ChildConfigNode->NextSiblingElement();

				iBulletNum = atoi(ChildConfigNode->GetText());

				pNode = new CBulletConfigNode(iId, szPath, iAtk,
					iSpeedX, iSpeedY, true, fAngle, iBulletNum);
			}
			else
			{
				pNode = new CBulletConfigNode(iId, szPath, iAtk,
					iSpeedX, iSpeedY, false);
			}

			handler->PushBack(pNode);
			Node = Node->NextSiblingElement();
		}
		return true;
	}
}

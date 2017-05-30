#include "MonsterConfigParser.h"

namespace yUtils
{
	bool CMonsterConfigParser::Parse(const char* fileName)
	{
		if (!fileName)
		{
			return false;
		}


		using namespace tinyxml2;
		auto handler = CMonsterConfigHandler::GetInstance();
		XMLDocument doc;
		doc.LoadFile(fileName);
		XMLElement* Root = doc.RootElement();


		if (!Root)
		{
			return false;
		}
		XMLElement* Node = Root->FirstChildElement();

		//临时变量声明
		int iTypeId = 0;
		int iHp = 0;
		int iAtk = 0;
		std::string szPath;
		int iInitPosX;
		int iInitPosY;
		int iSpeedX;
		int iSpeedY;

		while (Node)
		{
			auto ChildNode = Node->FirstChildElement();

			iTypeId = atoi(ChildNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();

			iHp = atoi(ChildNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();

			iAtk = atoi(ChildNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();

			szPath = ChildNode->GetText();
			ChildNode = ChildNode->NextSiblingElement();
				
			auto initPosNode = ChildNode->FirstChildElement();
			iInitPosX = atoi(initPosNode->GetText());

			initPosNode = initPosNode->NextSiblingElement();
			iInitPosY = atoi(initPosNode->GetText());
			ChildNode = ChildNode->NextSiblingElement();

			auto speedNode = ChildNode->FirstChildElement();
			iSpeedX = atoi(speedNode->GetText());

			speedNode = speedNode->NextSiblingElement();
			iSpeedY = atoi(speedNode->GetText());

			Node = Node->NextSiblingElement();

			CMonsterConfigNode* node = new CMonsterConfigNode(
				iTypeId, iHp, iAtk, szPath, iInitPosX, iInitPosY, iSpeedX, iSpeedY);

			handler->PushBack(node);

		}

		return true;
	}
}

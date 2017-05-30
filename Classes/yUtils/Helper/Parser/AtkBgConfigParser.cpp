#include "AtkBgConfigParser.h"

bool yUtils::CAtkBgConfigParser::Parse(const char* fileName)
{
	if (!fileName)
	{
		return false;
	}


	using namespace tinyxml2;
	auto handler = CAtkBgConfigHandler::GetInstance();
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
	std::vector< std::string > szPaths;
	int iSpeedX = 0;
	int iSpeedY = 0;
	int iBlankX = 0;
	int iBlankY = 0;
	int iInitX = 0;
	int iInitY = 0;

	while (Node)
	{
		auto ChildNode = Node->FirstChildElement();

		iId = atoi(ChildNode->GetText());
		ChildNode = ChildNode->NextSiblingElement();

		auto PathNode = ChildNode->FirstChildElement();
		while (PathNode)
		{
			szPaths.push_back(PathNode->GetText());
			PathNode = PathNode->NextSiblingElement();
		}
		ChildNode = ChildNode->NextSiblingElement();

		
		auto speedNode = ChildNode->FirstChildElement();
		iSpeedX = atoi(speedNode->GetText());

		speedNode = speedNode->NextSiblingElement();
		iSpeedY = atoi(speedNode->GetText());
		
		ChildNode = ChildNode->NextSiblingElement();


		auto blankNode = ChildNode->FirstChildElement();
		iBlankX = atoi(blankNode->GetText());

		blankNode = blankNode->NextSiblingElement();
		iBlankY = atoi(blankNode->GetText());

		ChildNode = ChildNode->NextSiblingElement();

		auto initPosNode = ChildNode->FirstChildElement();
		iInitX = atoi(initPosNode->GetText());

		initPosNode = initPosNode->NextSiblingElement();
		iInitY = atoi(initPosNode->GetText());


		Node = Node->NextSiblingElement();

		CAtkBgConfigNode* node = new CAtkBgConfigNode(
			iId, szPaths, iSpeedX, iSpeedY, iBlankX, iBlankY,iInitX, iInitY);

		handler->PushBack(node);

		szPaths.clear();
	}
	return true;
}

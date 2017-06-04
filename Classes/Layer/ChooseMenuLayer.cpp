#include "ChooseMenuLayer.h"
#include "MenuLayer.h"
#include "GameLayer.h"

Scene* ChooseMenuLayer::createScene()
{
	Scene* scene = Scene::create();

	ChooseMenuLayer* layer = ChooseMenuLayer::create();

	scene->addChild(layer);

	return scene;
}

bool ChooseMenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//读取配置
	m_vConfig = FileUtils::getInstance()->getValueMapFromFile("Config/ChooseMenuConfig.xml");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//创建一个talbleview 将datasource设置为当前的类的对象 tableview的显示区域大小为 
	TableView* tableView = TableView::create(this, Size(m_vConfig["TableViewShowWidth"].asInt(),
		m_vConfig["TableViewShowHeight"].asInt()));
	//设置tableview为水平方向  ScrollView::Direction::VERTICAL 为垂直,ScrollView::Direction::HORIZONTAL 为水平
	tableView->setDirection(ScrollView::Direction::HORIZONTAL);
	//设置位置
	tableView->setPosition(m_vConfig["TableViewPosX"].asInt(), m_vConfig["TableViewPosY"].asInt());
	//设置代理对象
	tableView->setDelegate(this);
	// 填充顺序
	//tableView->setVerticalFillOrder(TableView::VerticalFillOrder::BOTTOM_UP);
	//添加tableview到当前layer
	this->addChild(tableView);
	//加载tableview
	tableView->reloadData();

	//创建返回按钮
	MenuItemFont* itemBackMenu = MenuItemFont::create("Back", [&](Ref* ref)
	{
		Director::getInstance()->replaceScene(MenuLayer::createScene());
	});
	itemBackMenu->setPosition(visibleSize.width - itemBackMenu->getContentSize().width / 2,
		itemBackMenu->getContentSize().height);

	Menu* menu = Menu::create(itemBackMenu, NULL);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);

	//创建字体
	Label* selectLabel = Label::create();
	selectLabel->setString(m_vConfig["SelectLabel"].asString());
	selectLabel->setSystemFontSize(m_vConfig["FontSize"].asInt());
	selectLabel->setPosition(tableView->getBoundingBox().getMidX() - 10,
		tableView->getBoundingBox().getMaxY() + selectLabel->getContentSize().height + 10);
	this->addChild(selectLabel);

	return true;
}



void ChooseMenuLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	Scene* scene = Scene::create();
	GameLayer* layer = GameLayer::create(cell->getIdx() + 1);
	scene->addChild(layer);
	Director::getInstance()->replaceScene(scene);
}

Size ChooseMenuLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return Size(m_vConfig["SmallWidth"].asInt(),
		m_vConfig["SmallHeight"].asInt());
}

TableViewCell* ChooseMenuLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	std::string szBuf = CCString::createWithFormat("Round %d", idx + 1)->getCString();
	
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new (std::nothrow) TableViewCell();
		cell->autorelease();

		//创建缩略图
		TMXTiledMap* pMap = TMXTiledMap::create(CCString::createWithFormat("maps/Round%d.tmx", idx + 1)->getCString());
		float rota = static_cast<float>(m_vConfig["SmallHeight"].asInt()) / pMap->getContentSize().width;
		pMap->setScale(rota);
		//pMap->setScale(0.5f);
		pMap->setPosition(Vec2::ZERO);
		pMap->setAnchorPoint(Vec2::ZERO);


		auto label = Label::createWithSystemFont(szBuf, "Helvetica", 25);
		label->setPosition(m_vConfig["SmallWidth"].asInt() / 4 - 10,
			0);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);

		cell->addChild(pMap);
		cell->addChild(label);
	}
	else
	{
		auto label = (Label*)cell->getChildByTag(123);
		label->setString(szBuf);
	}


	return cell;
}

ssize_t ChooseMenuLayer::numberOfCellsInTableView(TableView *table)
{
	return m_vConfig["MaxMapCount"].asInt();
}

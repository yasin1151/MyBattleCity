#include "RockerBase.h"


RockerBase::RockerBase()
	:m_iState(static_cast<int>(RockerState::Stay)),
	m_bIsTouchRocker(false)
{

}

RockerBase::~RockerBase()
{

}


RockerState RockerBase::getState() const
{
	return static_cast<RockerState>(m_iState);
}

bool RockerBase::init(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos)
{
	if (!Layer::init())
	{
		return false;
	}

	m_spBg = Sprite::create(szBgFileName);
	this->addChild(m_spBg);
	m_spBg->setPosition(pos);

	m_spRocker = Sprite::create(szRockerFileName);
	this->addChild(m_spRocker);
	m_spRocker->setPosition(pos);

	initTouchEvent();

	return true;
}

void RockerBase::initTouchEvent()
{
	EventListenerTouchOneByOne* _event = EventListenerTouchOneByOne::create();
	_event->onTouchBegan = CC_CALLBACK_2(RockerBase::onTouchBegan, this);
	_event->onTouchMoved = CC_CALLBACK_2(RockerBase::onTouchMoved, this);
	_event->onTouchEnded = CC_CALLBACK_2(RockerBase::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_event, this);
}

bool RockerBase::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 pos = touch->getLocation();

	if (m_spRocker->getBoundingBox().containsPoint(pos))
	{
		m_bIsTouchRocker = true;
	}

	return true;
}

void RockerBase::onTouchMoved(Touch* touch, Event* unused_event)
{
	if (!m_bIsTouchRocker)
	{
		return;
	}

	Vec2 pos = touch->getLocation();
	Vec2 origin = m_spBg->getPosition();
	Vec2 setPos = pos;
	float radius = m_spBg->getContentSize().width / 2;
	float dis = pos.distance(origin);



	if (dis <= radius)
	{
		setPos = pos;
	}
	else
	{
		//相似三角形
		Vec2 relPos = pos - origin;		//相对于原点的坐标
		float xDis = relPos.x * radius / dis;
		float yDis = relPos.y * radius / dis;

		setPos = Vec2(xDis, yDis) + origin;
	}

	m_spRocker->setPosition(setPos);
	setState(yUtils::GetRadian(setPos, origin));
}

void RockerBase::onTouchEnded(Touch* touch, Event* unused_event)
{
	m_bIsTouchRocker = false;
	m_spRocker->setPosition(m_spBg->getPosition());
	m_iState = static_cast<int>(RockerState::Stay);
}


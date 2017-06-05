#include "Rocker4AWithTrans.h"


void Rocker4AWithTrans::setRockerPosWithShow(const Vec2& pos)
{
	m_spBg->setPosition(pos);
	m_spRocker->setPosition(pos);
	setRockerShow(true);
}

void Rocker4AWithTrans::setRockerShow(bool bIsShow)
{
	m_spRocker->setVisible(bIsShow);
	m_spBg->setVisible(bIsShow);
}

Rocker4AWithTrans* Rocker4AWithTrans::create(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos, const Rect& touchRect)
{
	Rocker4AWithTrans* pRet = new Rocker4AWithTrans();
	if (pRet && pRet->init(szBgFileName, szRockerFileName, pos, touchRect))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool Rocker4AWithTrans::init(const char* szBgFileName, const char* szRockerFileName, const Vec2& pos, const Rect& touchRect)
{
	m_touchRect = touchRect;
	RockerBase::init(szBgFileName, szRockerFileName, pos);
	setRockerShow(false);
	return true;
}

void Rocker4AWithTrans::initTouchEvent()
{
	EventListenerTouchOneByOne* _event = EventListenerTouchOneByOne::create();
	_event->onTouchBegan = CC_CALLBACK_2(Rocker4AWithTrans::onTouchBegan, this);
	_event->onTouchMoved = CC_CALLBACK_2(RockerBase::onTouchMoved, this);
	_event->onTouchEnded = CC_CALLBACK_2(Rocker4AWithTrans::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_event, this);
}

bool Rocker4AWithTrans::onTouchBegan(Touch* touch, Event* unused_event)
{
	Vec2 touchPos = touch->getLocation();
	Size visiSize = Director::getInstance()->getVisibleSize();
	
	if (m_touchRect.containsPoint(touchPos))
	{
		//œ‘ æ
		setRockerPosWithShow(touchPos);
		m_bIsTouchRocker = true;
	}
	return true;
}

void Rocker4AWithTrans::onTouchEnded(Touch* touch, Event* unused_event)
{
	setRockerShow(false);
	m_bIsTouchRocker = false;
	m_iState = static_cast<int>(RockerState::Stay);
}


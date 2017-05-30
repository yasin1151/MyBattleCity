#include "ScrollBg.h"

namespace yUtils
{
	void CScrollBg::ResetPosition(const Vec2& initPos)
	{
		if (2 > m_queueOfSprite.size())
		{
			return;
		}

		Vec2 vBufPos = initPos;

		if (Vec2::ZERO == initPos)
		{
			vBufPos = (Director::getInstance()->getWinSize()) / 2;
		}

		//获取速度的标准向量
		Vec2 normalizedVec = m_vSpeed.getNormalized();

		//获取第一个背景
		auto it = m_queueOfSprite.begin();

		//设置初始背景的坐标
		(*it)->setPosition(vBufPos);

		//设置一个buf
		auto itBuf = it;

		//转移到第二章图片
		++it;

		while (it != m_queueOfSprite.end())
		{
			//获取上一个背景的坐标
			Vec2 vPreBgPos = (*itBuf)->getPosition();

			//获取速度的标量(为了获取滚动的方向)
			Vec2 vSpeedNor = m_vSpeed.getNormalized();

			/*
				设置当前的坐标为, 
				上一张图片的位置 + 上一张图片的大小 * vSpeedNor
				+ 当前图片的大小 * vSpeedNor
			*/

			Size sPreBgSize = (*itBuf)->getContentSize();

			Vec2 vPreBgBuf = Vec2(vSpeedNor.x * sPreBgSize.width, vSpeedNor.y * sPreBgSize.height) / 2;

			Size sCurBgSize = (*it)->getContentSize();

			Vec2 vCurBgBuf = Vec2(vSpeedNor.x * sCurBgSize.width, vSpeedNor.y * sCurBgSize.height) / 2;

			(*it)->setPosition(
				(*itBuf)->getPosition() - vPreBgBuf - vCurBgBuf + m_sBlankSize);

			itBuf = it;

			++it;
		}
	}

	CScrollBg* CScrollBg::create(const Vec2& vSpeed)
	{
		CScrollBg* pNode = new CScrollBg;
		if (pNode && pNode->init(vSpeed))
		{
			pNode->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pNode);
		}
		return pNode;
	}

	bool CScrollBg::init(const Vec2& vSpeed)
	{
		if (!Node::init())
		{
			return false;
		}
		m_vSpeed = vSpeed;
		m_sBlankSize = Size(0, 0);
		return true;
	}

	bool CScrollBg::Start(const Vec2& initPos)
	{
		if (m_bIsStart)
		{
			return false;
		}

		if (2 > m_queueOfSprite.size())
		{
			return false;
		}

		ResetPosition(initPos);
		this->scheduleUpdate();
		m_bIsStart = true;
		return true;
	}

	void CScrollBg::update(float dt)
	{
		if (2 > m_queueOfSprite.size())
		{
			return; 
		}

		Sprite* spFront = m_queueOfSprite.front();

		Size winSize = Director::getInstance()->getWinSize();

		Rect curBoudingBox = spFront->getBoundingBox();

		if (!curBoudingBox.intersectsRect(Rect(0, 0, winSize.width, winSize.height)))
		{
			//如果第一张图片已经出了屏幕
			//将第一张图片出队，并且将第一张图片重新加入队列末尾

			m_queueOfSprite.pop_front();
			m_queueOfSprite.push_back(spFront);
			spFront = m_queueOfSprite.front();
		}

		ResetPosition(spFront->getPosition() + m_vSpeed);


	}

	void CScrollBg::AddNewBg(Sprite* spBg)
	{
		m_queueOfSprite.push_back(spBg);
		this->addChild(spBg);
	}

	void CScrollBg::RemoveBg(Sprite* spBg)
	{
		if (m_queueOfSprite.empty())
		{
			return;
		}

		auto it = m_queueOfSprite.begin();
		while (it != m_queueOfSprite.end())
		{
			if ((*it) == spBg)
			{
				m_queueOfSprite.erase(it);
				this->removeChild(*it, true);
				break;
			}
		}
	}

	Sprite* CScrollBg::GetFrontNode() const
	{
		return m_queueOfSprite.front();
	}

	inline int CScrollBg::GetBgSize() const
	{
		return m_queueOfSprite.size();
	}

	void CScrollBg::Pause()
	{
		if (!m_bIsStart)
		{
			return;
		}

		this->unscheduleUpdate();
	}

	void CScrollBg::Resume()
	{
		if (!m_bIsStart)
		{
			return;
		}
		this->scheduleUpdate();
	}
}

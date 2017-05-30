#include "LoadingBar.h"

namespace yUtils
{
	void CLoadingBar::RunCallBackFun()
	{
		for (auto i : m_arrCallBack)
		{
			i();
		}
		m_arrCallBack.clear();
	}

	CLoadingBar* CLoadingBar::create(const std::string& bgFileName, const std::string& loadFileName, const Vec2& offset)
	{
		CLoadingBar* pNode = new CLoadingBar;
		if (pNode && pNode->init(bgFileName, loadFileName, offset))
		{
			pNode->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pNode);
		}
		return pNode;
	}

	bool CLoadingBar::init(const std::string& bgFileName, const std::string& loadFileName, const Vec2& offset)
	{
		if (!Node::init())
		{
			return false;
		}

		m_spBg = Sprite::create(bgFileName);
		m_spLoading = Sprite::create(loadFileName);

		Size size = m_spBg->getContentSize();
		m_spBg->addChild(m_spLoading);
		this->addChild(m_spBg);

		m_spLoading->setPosition(Vec2(0, size.height / 2) + offset);
		m_spLoading->setAnchorPoint(Vec2(0, 0));

		//获取进度条的纹理矩形，并设置
		m_LoadingRect = m_spLoading->getTextureRect();
		m_spLoading->setTextureRect(Rect(m_LoadingRect.size.width, 0, 0, m_LoadingRect.size.height));

		//开启调度器
		this->scheduleUpdate();
		return true;
	}

	CLoadingBar::CLoadingBar()
		:m_fCurLoadingRate(0.0f), m_bIsChange(false), m_bIsFinal(false), m_fFinalDelayTime(0.1f)
	{
		
	}

	void CLoadingBar::AddCallBack(LoadingBarCallBack callBack)
	{
		m_arrCallBack.push_back(callBack);
	}

	void CLoadingBar::SetRate(float rate)
	{
		static float Float_EP = 0.000001;
		if (m_bIsFinal)
		{
			return;
		}

		if (yUtils::IsEqualF(rate, 1.0f))
		{
			rate = 1.0f;
			m_bIsFinal = true;
		}

		m_fCurLoadingRate = rate;
		m_bIsChange = true;
	}

	void CLoadingBar::update(float dt)
	{
		if (m_bIsChange)
		{
			float fFactor = m_LoadingRect.size.width * m_fCurLoadingRate;
			m_spLoading->setTextureRect(Rect(m_LoadingRect.size.width - fFactor, 0, fFactor, m_LoadingRect.size.height));
			m_bIsChange = false;

			if (m_bIsFinal)
			{
				this->unscheduleUpdate();
				this->scheduleOnce(schedule_selector(CLoadingBar::FinalUpdate), m_fFinalDelayTime);
			}
		}

	}

	void CLoadingBar::FinalUpdate(float dt)
	{
		RunCallBackFun();
	}
}

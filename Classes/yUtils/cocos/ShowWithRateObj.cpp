#include "ShowWithRateObj.h"

namespace yUtils
{
	void CShowWithRateObj::CallBack()
	{
		for (auto i : m_arrNoParamFun)
		{
			i();
		}
	}

	bool CShowWithRateObj::init(Texture2D* bgTexture, Texture2D* stripeTexture, const Vec2& offset)
	{
		if (!Node::init())
		{
			return false;
		}

		m_spBg = Sprite::createWithTexture(bgTexture);
		m_spRateStripe = Sprite::createWithTexture(stripeTexture);

		this->addChild(m_spBg);
		m_spBg->addChild(m_spRateStripe);

		m_spRateStripe->setPosition(offset);

		m_sStripe = m_spRateStripe->getContentSize();
		
		return true;
	}

	void CShowWithRateObj::AddCallBack(NoParamCallBack& callBack)
	{
		m_arrNoParamFun.push_back(callBack);
	}
}

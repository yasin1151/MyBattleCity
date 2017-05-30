#include "BloodLabel.h"

namespace yUtils
{

	CBloodLabel* CBloodLabel::create(Texture2D* bgTexture, Texture2D* bloodTexture, int initHp, const Vec2& offsetPos)
	{
		CBloodLabel* pNode = new CBloodLabel;
		if (pNode && pNode->init(bgTexture, bloodTexture, initHp, offsetPos))
		{
			pNode->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pNode);
		}
		return pNode;
	}

	CBloodLabel* CBloodLabel::create(const std::string& bgFileName, const std::string& bloodFileName, int initHp, const Vec2& offsetPos)
	{
		CBloodLabel* pNode = new CBloodLabel;
		Texture2D* bgTexture = TextureCache::getInstance()->addImage(bgFileName);
		Texture2D* bloodTexture = TextureCache::getInstance()->addImage(bloodFileName);
		if (pNode && pNode->init(bgTexture, bloodTexture, initHp, offsetPos))
		{
			pNode->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pNode);
		}
		return pNode;
	}

	bool CBloodLabel::init(Texture2D* bgTexture, Texture2D* bloodTexture, int initHp, const Vec2& offsetPos)
	{
		if (!Node::init())
		{
			return false;
		}

		m_spBg = Sprite::createWithTexture(bgTexture);
		m_spBlood = Sprite::createWithTexture(bloodTexture);

		Size bgSize = m_spBg->getContentSize();
		m_spBg->addChild(m_spBlood);		
		m_spBlood->setPosition(Vec2(0, bgSize.height / 2) + offsetPos);
		m_spBlood->setAnchorPoint(Vec2(0, 0));

		this->addChild(m_spBg);
		m_iHp = initHp;
		m_iCurHp = initHp;

		m_BloodRect = m_spBlood->getTextureRect();
		this->scheduleUpdate();
		//m_spBlood->setVertexRect();
		
		return true;
	}

	void CBloodLabel::UpdateHp()
	{
		float fRate = m_iCurHp / m_iHp;

		float fFactor = fRate * m_BloodRect.size.width;

		m_spBlood->setTextureRect(Rect(m_BloodRect.size.width - fFactor, 0,
			fFactor, m_BloodRect.size.height));
	}

	void CBloodLabel::SetHp(float iHp)
	{
		if (iHp > m_iHp)
		{
			return;
		}
		else if ( iHp == m_iCurHp )
		{
			return;
		}
			
			
		m_iCurHp = iHp;
		m_bIsChangeHp = true;
	}

	void CBloodLabel::update(float dt)
	{
		if (!m_bIsChangeHp)
		{
			return;
		}

		UpdateHp();

		m_bIsChangeHp = false;
	}
}


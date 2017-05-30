#ifndef _BLOOD_LABEL_H_
#define _BLOOD_LABEL_H_

/*
	@brief : 血条控制库
	@auther: PengYao
	@time  : 2017/2/3
	@ver   : 1.0

*/

#include "cocos2d.h"
USING_NS_CC;



/*
	@brief : 
*/
namespace yUtils
{
	class CBloodLabel : public Node
	{
	protected:
		float m_iHp;				//总血量
		float m_iCurHp;			//当前血量
		bool m_bIsChangeHp;		//血量是否被改变
		Sprite* m_spBg;
		Sprite* m_spBlood;
		Rect m_BloodRect;

	public:

		//通过血条的长度，血条背景图片，血条前景图片，位置，初始血量来创建一个新的血条
		static CBloodLabel* create(Texture2D* bgTexture, Texture2D* bloodTexture, int initHp, const Vec2& offsetPos = Vec2(0,0));

		static CBloodLabel* create(const std::string& bgFileName, const std::string& bloodFileName, int initHp, const Vec2& offsetPos = Vec2(0, 0));

		bool init(Texture2D* bgTexture, Texture2D* bloodTexture, int initHp, const Vec2& offsetPos);

		void UpdateHp();

		void SetHp(float iHp);

		float GetHp() const
		{
			return m_iHp;
		}

		virtual void update(float dt) override;
	};

}

#endif
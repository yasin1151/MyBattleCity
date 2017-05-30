#ifndef _SHOW_WITH_RATE_OBJ_H_
#define _SHOW_WITH_RATE_OBJ_H_

/*
	@brief : 在写完血条库和进度条库后抽象出的基类
	@auther: PengYao
	@time  : 2017/2/9
	@ver   : 1.0
*/
#include "cocos2d.h"
USING_NS_CC;

namespace yUtils
{
	typedef std::function<void(void)> NoParamCallBack;


	class CShowWithRateObj : public Node
	{
	protected:
		Sprite* m_spBg;				//背景
		Sprite* m_spRateStripe;		//需要按照一定比例显示的条
		Size m_sStripe;				//条的初始大小

		std::vector<NoParamCallBack> m_arrNoParamFun;		//无参回调函数的数组

		/*
			@brief : 调用所有的回调函数
		*/
		void CallBack();

	public:
		/*
			@brief : 初始化类中的两个精灵，背景精灵作为当前节点的子节点，条精灵作为背景节点的子节点
			@param bgTexture : 背景纹理
			@param stripeTexture : 条纹理
			@param offset : 条精灵在背景精灵上的偏移值，默认为(0, 0)
		*/
		bool init(Texture2D* bgTexture, Texture2D* stripeTexture, const Vec2& offset = Vec2(0, 0));

		/*
			@brief : 添加无参回调函数
			@param callBack : 回调函数
		*/
		void AddCallBack(NoParamCallBack& callBack);


		/*
			Getter
		*/
		Size GetStripeSize() const
		{
			return m_sStripe;
		}

		Sprite* GetBgSprite() const
		{
			return m_spBg;
		}

		Sprite* GetStripeSprite() const
		{
			return m_spRateStripe;
		}
	};
}

#endif
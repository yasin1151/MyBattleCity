#ifndef _LOADING_BAR_H_
#define _LOADING_BAR_H_


/*
	@brief : 进度条控件类, 进度条作为背景的子节点
	@auther: PengYao
	@time  : 2017/1/18
	@ver   : 1.0
*/
#include "cocos2d.h"
#include "../Helper/yUtils.h"
#include <functional>

USING_NS_CC;



namespace yUtils
{
	typedef std::function<void(void)> LoadingBarCallBack;

	class CLoadingBar : public Node
	{
	protected:
		Sprite* m_spBg;				//背景
		Sprite* m_spLoading;		//进度条
		Rect m_LoadingRect;			//进度条的纹理矩形
		float m_fCurLoadingRate;	//当前加载的进度


		float m_fFinalDelayTime;	//当进度条加载完后，间隔多少秒调用回调函数，默认为0.1f
									//为了使进度条先加载完，在调用回调函数

		bool m_bIsChange;			//是否改变了数值
		bool m_bIsFinal;			//是否开始回调

		std::vector<LoadingBarCallBack> m_arrCallBack;

		void RunCallBackFun();

	public:
		static CLoadingBar* create(const std::string& bgFileName, const std::string& loadFileName, const Vec2& offset = Vec2(0, 0));

		bool init(const std::string& bgFileName, const std::string& loadFileName, const Vec2& offset);

		/*
			@brief : 对无需在init中初始化的变量，在初始化列表中进行初始化
		*/
		CLoadingBar();

		/*
			@brief : 增加一个回调函数（当进度条读取完成时调用）
					 只会调用一次
		*/
		void AddCallBack(LoadingBarCallBack callBack);


		/*
			@brief : 获取最后的延迟时间

		*/
		float GetFinalDelayTime() const
		{
			return m_fFinalDelayTime;
		}

		void SetFinalDelayTime(float dt)
		{
			m_fFinalDelayTime = dt;
		}


		/*
			@brief : 设置当前加载的进度比例
			@rate  : 比例从0 到 1
		*/
		void SetRate(float rate);

		float GetRate() const
		{
			return m_fCurLoadingRate;
		}

		void update(float dt) override;

		void FinalUpdate(float dt);
	};
}

#endif
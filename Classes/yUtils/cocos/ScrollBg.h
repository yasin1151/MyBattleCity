#ifndef _SCROLL_BG_H_
#define _SCROLL_BG_H_

/*
	@brief : 我的滚轴背景类
	@auther: PengYao
	@time  : 2017/1/19
	@ver   : 1.0
*/

#include "cocos2d.h"
#include <deque>

USING_NS_CC;

namespace yUtils
{
	class CScrollBg : public Node
	{
	protected:
		Vec2 m_vSpeed;		//滚动的速度（方向）

		Size m_sBlankSize;	//两张图的间隔大小

		std::deque<Sprite*> m_queueOfSprite;

		bool m_bIsStart;

		/*
			@brief : 重置当前所有节点的位置
					 至少要有两个背景以上
			@param initPos : 第一个节点的初始位置
							传入0,0为默认屏幕中心坐标
		*/
		void ResetPosition(const Vec2& initPos = Vec2::ZERO);


	public:
		CScrollBg():m_bIsStart(false){}

		static CScrollBg* create(const Vec2& vSpeed);

		bool init(const Vec2& vSpeed);


		/*
			@brief : 将所有的场景加入本类后，调用该方法开始滚动
			@param initPos : 第一个场景的初始位置

		*/
		bool Start(const Vec2& initPos = Vec2::ZERO);

		/*
			@brief : 默认调度器函数
		*/
		void update(float dt) override;
		
		/*
			@brief : 支持动态插入新图片
			@param spBg 新的图片
		*/
		void AddNewBg(Sprite* spBg);

		/*
			@brief : 支持动态删除图片
			@param spBg 需要删除的图片节点
		*/
		void RemoveBg(Sprite* spBg);


		/*
			@brief : 获取当前处于第一位的节点
		*/
		Sprite* GetFrontNode() const;

		/*
			@brief : 获取精灵的背景图片的个数
		*/
		int GetBgSize() const;

		/*
			@brief : 暂停背景滚动
		*/
		void Pause();


		/*
			@brief : 恢复背景滚动
		*/
		void Resume();



		/*
			Getter and Setter
		*/
		void SetSpeed(const Vec2& speed)
		{
			m_vSpeed = speed;
		}

		Vec2 GetSpeed() const
		{
			return m_vSpeed;
		}

		/*
		@brief : 获取两张图片之间的间隔大小，默认为(0,0)
		*/
		Size GetBlankSize() const
		{
			return m_sBlankSize;
		}

		/*
		@brief : 设置两张图片之间的间隔大小
		@param blankSize : 间隔大小
		*/
		void SetBlankSize(const Size& blankSize)
		{
			m_sBlankSize = blankSize;
		}
	};
}

#endif
#ifndef _HANDLER_TEMPLATE_H_
#define _HANDLER_TEMPLATE_H_

/*
	@brief : 我的Handler模板类
	@auther: PengYao
	@time  : 2017/1/18
	@ver   : 1.0
*/

#include <vector>

namespace yUtils
{
	template < typename T >
	class HandlerTemplate
	{
	protected:
		std::vector <T*> m_arr;
	public:

		/*
			@brief : 将节点的指针加入数组中
			@param node : T*
		*/
		void PushBack(T* node);

		/*
			@brief : 获取指定下标的数据
			@param i : 下标
		*/
		T* operator[] (int i);

		/*
			@brief : 获取数组当前元素的个数
		*/
		size_t GetSize();
	};

	template <typename T>
	void HandlerTemplate<T>::PushBack(T* node)
	{
		m_arr.push_back(node);
	}

	template <typename T>
	T* HandlerTemplate<T>::operator[](int i)
	{
		return m_arr[i];
	}

	template <typename T>
	size_t HandlerTemplate<T>::GetSize()
	{
		return m_arr.size();
	}
}

#endif
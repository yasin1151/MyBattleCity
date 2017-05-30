#ifndef _MEM_POOL_H_
#define _MEM_POOL_H_

/*
	@brief : 一个简单的内存池
	@auther: PengYao
	@time  : 2017/1/17
	@ver   : 1.0
*/

#include <list>
namespace yUtils
{
	template <typename T>
	class CMemPool
	{
	public:
		/*
		*	@param beginSize : 初始new的内存的个数
		*/
		CMemPool(int beginSize = 10, int chunkSize = sizeof(T))
			:m_chunkSize(chunkSize)
		{
			//addMem(beginSize);
		}

		virtual ~CMemPool()
		{
			clear();
		}

		/*
		*@brief : 去分配一个内存给外部
		*/
		T* Alloc();

		/**@brief : 回收外部内存
		@param ptr : 需要被回收的内存
		*/
		void  Delete(T* ptr);

		
	protected:

		/*
			@brief : 在分配内存时调用
		*/

		virtual void onAllocMem(T* ptr)
		{
			
		}


		/*
			@brief : 在增加内存后调用
		*/
		virtual void OnAddMem(std::list<T*>& listHasMem)
		{

		}

		/*
			@brief : 在回收内存时调用
		*/
		virtual void OnDelete(T* ptr)
		{
			
		}

		/*
			@brief : 在清理内存时调用
		*/
		virtual void OnClearup(T* ptr)
		{
			
		}

		/*
		@brief : 增加分配的内存数目
		*/
		void addMem(int size = 0);

		/*
		@brief : 清理所有的内存
		*/
		void clear();


		void Init();

		std::list<T*> m_curUseMem;				//当前已经使用的内存池,即需要释放的内存
		std::list<T*> m_curHasMem;				//当前可以使用的内存池
		size_t		  m_chunkSize;				//内存块的大小
	};

	template <typename T>
	void CMemPool<T>::addMem(int size)
	{
		size_t curSize = m_curUseMem.size();
		if (curSize <= 0 && size != 0)
		{
			curSize = size;
		}

		for (int i = 0; i < curSize * 3 / 2; i++)
		{
			//只分空间，不调用构造函数
			//m_curHasMem.push_back(static_cast<T*>(operator new (sizeof(T))));
			OnAddMem(m_curHasMem);
		}
	}

	template <typename T>
	T* CMemPool<T>::Alloc()
	{
		if (m_curHasMem.empty())
		{
			addMem();
		}

		//从可以使用的内存块中取出，并加入到已经使用的内存块中
		T* retBuf = m_curHasMem.back();
		m_curHasMem.pop_back();
		m_curUseMem.push_back(retBuf);

		onAllocMem(retBuf);

		return retBuf;
	}

	template <typename T>
	void  CMemPool<T>::Delete(T* ptr)
	{
		if (!ptr)
		{
			return;
		}

		m_curUseMem.remove(ptr);
		m_curHasMem.push_back(ptr);
		
		OnDelete(m_curHasMem.back());
	}

	template <typename T>
	void CMemPool<T>::clear()
	{
		if (!m_curUseMem.empty())
		{
			for (auto i : m_curUseMem)
			{
				OnClearup(i);
				delete i;
			}
		}

		if (!m_curHasMem.empty())
		{
			for (auto i : m_curHasMem)
			{
				OnClearup(i);
				delete i;
			}
		}
	}

	template <typename T>
	void CMemPool<T>::Init()
	{
		addMem(10);
	}
}


#endif// _MEM_POOL_H_
#ifndef _C_SINGLE_INSTANCE_TMP_H_
#define _C_SINGLE_INSTANCE_TMP_H_
/*
	@brief : 我的单例模板
	@auther: PengYao
	@time  : 2017/1/17
	@ver   : 1.0
*/
template < typename T >
class CSingleInstanceTmp
{
public:
	static T* GetInstance()
	{
		static T instance;
		return &instance;
	}
};

#endif
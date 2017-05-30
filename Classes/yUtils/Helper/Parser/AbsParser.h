#ifndef _ABS_PARSER_H_
#define _ABS_PARSER_H_

/*
	@name	: AbsParser.h
	@auther	: PengYao
	@time	: 2017/1/2
	@des	: Parser的抽象基类
*/
namespace yUtils
{
	class CAbsParser
	{
	public:
		virtual ~CAbsParser()
		{
		}

		/*
		@brief : 可正向或逆向翻译一个xml文件
		@param fileName : xml文件存储或者另存为的地址
		*/
		virtual bool Parse(const char* fileName) = 0;
	};
}

#endif
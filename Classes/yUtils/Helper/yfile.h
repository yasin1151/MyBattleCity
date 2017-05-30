/*
	name   : YFile.h
	auther : Pengyao
	time   : 2016/12/1
	ext	   : 参考了 https://github.com/masterworkcoder/File 的作品后自己修改后的版本
*/

#ifndef _YASIN_FILE_H_
#define _YASIN_FILE_H_

#include <cstdio>

namespace yUtils
{
	class CFile
	{
	protected:
		FILE* m_file;			//内部文件指针
	public:
		CFile()
			:m_file(nullptr)
		{}

		~CFile()
		{
			this->close();
		}


		/*
		*	brief : 加载一个文件， 如果文件已打开则会关闭上一个打开的文件指针
		*	param_modeName : r	---- 打开一个文件去读，如果文件不存在则无法打开 
		*					 w  ---- 创建一个文件去写，如果文件不存在会创建一个，但文件已经已经存在就会覆盖
		*					 a  ---- 打开一个文件去附加，如果文件不存在会创建，文件存在会在末尾开始写
		*					 r+ ---- 打开一个文件去读/写，如果文件不存在会报错
		*					 w+ ---- 创建一个文件去读/写
		*					 a+ ---- 打开一个文件去读/写
		*					 b  ---- 用二进制打开
		*/
		bool load(const char* fileName, const char* modeName)
		{
			if (this->isOpen())
			{
				this->close();
			}

			m_file = fopen(fileName, modeName);
			return this->isOpen();
		}


		/*
		*	brief : 判断文件是否打开
		*/
		bool isOpen() const
		{
			if (m_file)
			{
				return true;
			}
			return false;
		}

		/*
		*	brief : 封装了fseek, form 有三个值 SEEK_CUR、SEEK_SET、SEEK_END
		*/
		bool seek(size_t pos, int form)
		{
			if (!this->isOpen())
			{
				return false;
			}
			if (0 < fseek(m_file, pos, form))
			{
				return false;
			}
			return true;
		}

		/*
		*	brief : 从已经打开的文件中读，size为每次读的大小，numread为读的次数
		*/
		bool read(char* buffer, int size, int numread = 1)
		{
			if (!this->isOpen())
			{
				return false;
			}

			fread(buffer, size, numread, m_file);

			return true;
		}
		/*
		*	brief : 从已经打开的文件中写，size为每次写的大小，numwrite为写的次数
		*/
		bool write(const char* buffer, int size, int numwrite = 1)
		{
			if (!this->isOpen())
			{
				return false;
			}

			if (numwrite > fwrite(buffer, size, numwrite, m_file))
			{
				return false;
			}
			return true;
		}

		/*
		*    brief : 获取一个字符，文件指针往后偏移一个
		*/
		char getC()
		{
			if (!this->isOpen())
			{
				return 0;
			}
			return fgetc(m_file);
		}

		/*
		*    brief : 返回下一个字符的值，文件指针位置不会动
		*/
		char PeekC()
		{
			char c = this->getC();
			if (this->seek(-1, SEEK_CUR))
			{
				return c;
			}
			return 0;
		}



		/*
		*    brief : 从当前位置开始的文件大小
		*/
		size_t getSize()
		{
			if (!this->isOpen())
			{
				return false;
			}
			size_t cur_pos = ftell(m_file);
			if (!this->seek(0, SEEK_END))
			{
				return 0;
			}

			size_t size = ftell(m_file);
			if (!this->seek(cur_pos, SEEK_SET))
			{
				return -1;
			}

			return size;
		}

		/*
		*	brief : 关闭文件
		*/
		bool close() const
		{
			if (m_file)
			{
				fclose(m_file);
				return true;
			}
			return false;
		}


		/*
		*	brief : 获取文件指针
		*/
		FILE* getFilePtr() const
		{
			return m_file;
		}
	};
}


#endif
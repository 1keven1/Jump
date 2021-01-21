#include "stableheader.h"
#include "GtFile.h"

GtFile::GtFile(const std::string& name) :
	m_name(name),
	m_open(false),
	m_data(NULL)
{

}

GtFile::~GtFile(void)
{
	Close();
}

void GtFile::Open()
{
	std::string realpath = getMediaPath() + m_name;

	FILE* pFile = NULL;
	fopen_s(&pFile, realpath.c_str(), "rb");

	if (pFile)
	{
		// 获取文件长度
		fseek(pFile, 0, SEEK_END);
		m_size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		// 文件大小为0
		if (m_size == -1)
		{
			fclose(pFile);
			return;
		}

		// 申请内存中的文件
		char* pTmp = new char[m_size];
		if (!pTmp)
		{
			m_size = 0;
			fclose(pFile);
			return;
		}

		// 从文件中拷贝数据到内存
		size_t BytesRead = fread(pTmp, 1, m_size, pFile);

		// 拷贝是否成功
		if (BytesRead != m_size)
		{
			delete[] pTmp;
			m_size = 0;
		}
		else
		{
			m_data = pTmp;
			m_open = true;
		}

		fclose(pFile);
	}
	else
	{
		// cannot open
	}
}

void GtFile::Close()
{
	m_open = false;
	delete[] m_data;
}

char* GtFile::Data() const
{
	return m_data;
}

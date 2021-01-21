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
		// ��ȡ�ļ�����
		fseek(pFile, 0, SEEK_END);
		m_size = ftell(pFile);
		fseek(pFile, 0, SEEK_SET);

		// �ļ���СΪ0
		if (m_size == -1)
		{
			fclose(pFile);
			return;
		}

		// �����ڴ��е��ļ�
		char* pTmp = new char[m_size];
		if (!pTmp)
		{
			m_size = 0;
			fclose(pFile);
			return;
		}

		// ���ļ��п������ݵ��ڴ�
		size_t BytesRead = fread(pTmp, 1, m_size, pFile);

		// �����Ƿ�ɹ�
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

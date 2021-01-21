#include "stableheader.h"
#include "GtLogger.h"

const int LOG_FILE_SZIE = 1024 * 50;

GtLogger::GtLogger(void)
{
	// 1mb
	m_data = new char[LOG_FILE_SZIE];
	m_size = 0;

	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
}

GtLogger::~GtLogger(void)
{
	FlushToFile();

	delete[] m_data;

	fclose(stdout);
	fclose(stdin);
	FreeConsole();
}

void GtLogger::Log(const char* line)
{
	uint32 length = strlen(line);

	// 缓存装不下了，写入文件
	if (m_size + length + 2 > LOG_FILE_SZIE)
	{
		FlushToFile();
	}

	// 装入缓存
	{
		SYSTEMTIME time;
		GetSystemTime(&time);

		char* buffer = new char[length + 100];

		sprintf(buffer, "[%d/%d/%d %d:%d(+8)] %s \r\n", time.wYear, time.wMonth, time.wDay, (time.wHour + 8) % 24, time.wMinute, line);


		memcpy(m_data + m_size, buffer, strlen(buffer));
		m_size += strlen(buffer);

		std::cout << buffer;

		delete buffer;
	}

}

void GtLogger::Log(const char* format, va_list args)
{
	char buffer[512];
	vsprintf(buffer, format, args);

	Log(buffer);
}

void GtLogger::FlushToFile()
{
	// write to file
	FILE* pFile = NULL;

	std::string path("log.txt");
	path = getMediaPath() + path;

	fopen_s(&pFile, path.c_str(), "ab");

	fwrite(m_data, 1, m_size, pFile);

	fclose(pFile);

	// remove size to 0
	m_size = 0;
}

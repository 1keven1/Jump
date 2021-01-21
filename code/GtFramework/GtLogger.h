/**
  @file GtLogger.h

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef GtLogger_h__
#define GtLogger_h__

class GtLogger
{
public:
	GtLogger(void);
	~GtLogger(void);

	void Log(const char* line);
	void Log(const char* format, va_list args);

private:
	void FlushToFile();
	char* m_data;
	uint32 m_size;
};
extern GtLogger* g_logger;

//	 Simple logs of data with low verbosity.
inline void GtLog(const char* format, ...)
{
	if (g_logger)
	{
		va_list args;
		va_start(args, format);
		g_logger->Log(format, args);
		va_end(args);
	}
}

#endif


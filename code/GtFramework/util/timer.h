/**
  @file GtTimer.h

  @author Kaiming

  ������־ history
  ver:1.0

 */

#ifndef GtTimer_h__
#define GtTimer_h__

class GtTimer
{
public:
	GtTimer() :m_time(0)
		, m_elapsedTime(0)
	{

	}
	~GtTimer()
	{

	}

	void Init()
	{

		m_elapsedTime = 0;
		QueryPerformanceFrequency(&m_freq); // ��ȡcpuʱ������
		m_time = getRealTime();
	}

	void Update()
	{
		QueryPerformanceFrequency(&m_freq); // ��ȡcpuʱ������
		float newTime = getRealTime();
		m_elapsedTime = newTime - m_time;
		m_time = newTime;
	}

	void Stop()
	{
		m_elapsedTime = 0;
	}

	float getElapsedTime()
	{
		return m_elapsedTime;
	}

	float getTime()
	{
		return getRealTime();
	}

	float getRealTime()
	{
		LARGE_INTEGER now;
		QueryPerformanceCounter(&now); // ��ȡcpuʱ�Ӽ���
		return (float)(now.QuadPart) / m_freq.QuadPart;
	}

private:
	float m_time;
	float m_elapsedTime;

	// high precision
	LARGE_INTEGER m_freq;
};

#endif



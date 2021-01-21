/**
  @file GtFramework.h

  @author Kaiming

  ������־ history
  ver:1.0

 */

#ifndef GtFramework_h__
#define GtFramework_h__

#include "prerequisite.h" ///< ����ȫ��ǰ��
#include "GtPresenter.h"

class GtFrameworkAppBase;

struct GtFrameworkInitParam
{
	HINSTANCE hInst;
	int width;
	int height;
	const char* windowName;

	GtFrameworkAppBase* app;

	GtFrameworkInitParam()
	{
		memset(this, 0, sizeof(GtFrameworkInitParam));
	}
};

class GtFramework
{
public:
	GtFramework(void);
	~GtFramework(void);

	/**
	  @brief ��ʼ��Gt���
	  @return bool
	 */
	bool Init(const GtFrameworkInitParam& createParam);
	/**
	  @brief ����Gt���
	  @return bool
	 */
	bool Run();
	/**
	  @brief �ر�Gt���
	  @return bool
	 */
	bool Shutdown();
	void SetPause(bool b);
private:
	/**
	  @brief Gt���֡����
	  @return bool
	 */
	bool Update();

	/**
	  @brief �ڲ�����window
	  @return bool
	  @param const GtFrameworkInitParam & createParam
	 */
	bool InnerCreateWindow(const GtFrameworkInitParam& createParam);


private:
	HWND m_hWnd;

	GtPresenter m_presenter;
	GtFrameworkAppBase* m_app;
	GtLogger m_logger;
	bool bPause;
};

#endif



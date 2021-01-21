/**
  @file GtFramework.h

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef GtFramework_h__
#define GtFramework_h__

#include "prerequisite.h" ///< 引入全局前提
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
	  @brief 初始化Gt框架
	  @return bool
	 */
	bool Init(const GtFrameworkInitParam& createParam);
	/**
	  @brief 运行Gt框架
	  @return bool
	 */
	bool Run();
	/**
	  @brief 关闭Gt框架
	  @return bool
	 */
	bool Shutdown();
	void SetPause(bool b);
private:
	/**
	  @brief Gt框架帧更新
	  @return bool
	 */
	bool Update();

	/**
	  @brief 内部创建window
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



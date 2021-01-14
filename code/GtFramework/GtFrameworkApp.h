/**
  @file GtFrameworkApp.h

  @brief GtFramework游戏框架, App范例
  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef GtFrameworkApp_h__
#define GtFrameworkApp_h__

#include "prerequisite.h"
#include "GtFramework.h"

 /**
  GtFramework App框架
  */
struct GtFrameworkAppBase
{
	virtual ~GtFrameworkAppBase() {}


	/**
	  @brief 当Framwork初始化时被调用，在函数内部处理app需要的初始化
	  @remark 初始化操作例如：创建一些管理器
	  @return void
	 */
	virtual void OnInit(HWND h) = 0;
	/**
	  @brief Framework每一帧调用一次
	  @return void
	  @param float fElapsedTime
	 */
	virtual void OnUpdate(float fElapsedTime) = 0;
	/**
	  @brief 当Framework退出时调用，在函数内部处理app需要的清除操作
	  @remark 清除操作例如：存档，摧毁动态内存对象，等等
	  @return void
	 */
	virtual void OnShutdown() = 0;
};

#endif
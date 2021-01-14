#include "stableheader.h"
#include "GtFramework.h"
#include "GtGameDemo.h"
//

// win32程序的main函数
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	char* lpCmdLine,
	int       nCmdShow)
{
	// 创建你的GameApp
	GtGameDemo game;

	// 创建GtFramework
	GtFramework framework;
	GtFrameworkInitParam param;
	param.hInst = hInstance;
	param.width = 640;
	param.height = 360;
	param.windowName = "GtGameDemo";
	// 把game app的指针传给param
	param.app = &game;

	framework.Init(param);

	// 进入GtFramework主循环
	framework.Run();

	// 关闭GtFramework
	framework.Shutdown();

	return 0;
}
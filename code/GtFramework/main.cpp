#include "stableheader.h"
#include "GtFramework.h"
#include "GtGameDemo.h"
//

// win32�����main����
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	char* lpCmdLine,
	int       nCmdShow)
{
	// �������GameApp
	GtGameDemo game;

	// ����GtFramework
	GtFramework framework;
	GtFrameworkInitParam param;
	param.hInst = hInstance;
	param.width = 640;
	param.height = 360;
	param.windowName = "GtGameDemo";
	// ��game app��ָ�봫��param
	param.app = &game;

	framework.Init(param);

	// ����GtFramework��ѭ��
	framework.Run();

	// �ر�GtFramework
	framework.Shutdown();

	return 0;
}
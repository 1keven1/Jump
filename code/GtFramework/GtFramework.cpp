#include "stableheader.h"
#include "GtFramework.h"
#include "GtPresenter.h"
#include "GtFrameworkApp.h"

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//	int wmId, wmEvent;
	//	PAINTSTRUCT ps;
	//	HDC hdc;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

GtRenderContext g_context;
GtLogger* g_logger = NULL;

GtFramework::GtFramework(void) :m_hWnd(NULL),
m_app(NULL)
{
}

GtFramework::~GtFramework(void)
{
}

bool GtFramework::Init(const GtFrameworkInitParam& createParam)
{
	g_logger = &m_logger;

	GtLog("//////////////////////////////////");
	GtLog("GtFramework 创建窗口...");
	GtLog("//////////////////////////////////");
	// 创建窗口
	InnerCreateWindow(createParam);

	// 创建渲染上下文
	g_context.width = createParam.width;
	g_context.height = createParam.height;
	g_context.bpp = sizeof(uint32);
	g_context.buffer = new uint32[g_context.width * g_context.height];
	g_context.zbuffer = new uint8[g_context.width * g_context.height];
	g_context.timer = new GtTimer();
	g_context.timer->Init();
	g_context.painter = new GtPainter();
	g_context.inputer = new SrInputManager();
	g_context.inputer->Init(m_hWnd);

	GtLog("GtFramework 创建presenter...");
	// 创建presenter
	GtPresenterParam param;
	param.width = createParam.width;
	param.height = createParam.height;
	param.bpp = g_context.bpp;
	param.hWnd = m_hWnd;

	m_presenter.Init(param);

	GtLog("GtFramework 创建游戏实例");
	// 创建app
	m_app = createParam.app;
	if (m_app)
	{
		m_app->OnInit(m_hWnd);
	}

	return true;
}

bool GtFramework::Run()
{
	// 程序主循环
	for (;;)
	{
		MSG msg;
		//HACCEL hAccelTable;

		// 有消息就处理消息
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message != WM_QUIT)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// 如果遇到WM_QUIT消息，退出主循环，程序退出
				break;
			}
		}
		else
		{
			// 没有消息，执行程序帧循环
			Update();
		}
	}
	return true;
}

bool GtFramework::Shutdown()
{
	GtLog("//////////////////////////////////");
	GtLog("GtFramework 关闭窗口实例");
	if (m_app)
	{
		m_app->OnShutdown();
	}

	g_context.inputer->Destroy();
	// 释放渲染上下文的屏幕buffer
	delete[] g_context.buffer;
	delete[]g_context.zbuffer;
	delete g_context.timer;
	delete g_context.painter;
	delete g_context.inputer;

	GtLog("GtFramework 关闭presenter");
	// 关闭presenter
	m_presenter.Shutdown();

	GtLog("GtFramework 退出程序");
	GtLog("//////////////////////////////////");
	return true;
}

bool GtFramework::Update()
{
	g_context.inputer->Update();
	g_context.timer->Update();
	float fElapsedTime = g_context.timer->getElapsedTime();
	if (m_app)
	{
		m_app->OnUpdate(fElapsedTime);
	}

	g_context.painter->Flush();
	m_presenter.Swap();
	return true;
}

bool GtFramework::InnerCreateWindow(const GtFrameworkInitParam& createParam)
{
	// 注册窗口类
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = createParam.hInst;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszClassName = "GtFramework Window Class";

	wcex.hIcon = NULL;
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);

	// 创建窗口
	m_hWnd = CreateWindow("GtFramework Window Class", createParam.windowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, createParam.width, createParam.height, NULL, NULL, createParam.hInst, NULL);
	//侦听鼠标位置
	g_context.hwnd = m_hWnd;

	// 调整尺寸
	RECT realRect;
	GetClientRect(m_hWnd, &realRect);

	int width = realRect.right - realRect.left;
	int height = realRect.bottom - realRect.top;
	width = createParam.width * 2 - width;
	height = createParam.height * 2 - height;

	MoveWindow(m_hWnd, GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2, width, height, FALSE);

	if (!m_hWnd)
	{
		return false;
	}

	// 显示窗口
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	return true;
}

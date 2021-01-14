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
	GtLog("GtFramework ��������...");
	GtLog("//////////////////////////////////");
	// ��������
	InnerCreateWindow(createParam);

	// ������Ⱦ������
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

	GtLog("GtFramework ����presenter...");
	// ����presenter
	GtPresenterParam param;
	param.width = createParam.width;
	param.height = createParam.height;
	param.bpp = g_context.bpp;
	param.hWnd = m_hWnd;

	m_presenter.Init(param);

	GtLog("GtFramework ������Ϸʵ��");
	// ����app
	m_app = createParam.app;
	if (m_app)
	{
		m_app->OnInit(m_hWnd);
	}

	return true;
}

bool GtFramework::Run()
{
	// ������ѭ��
	for (;;)
	{
		MSG msg;
		//HACCEL hAccelTable;

		// ����Ϣ�ʹ�����Ϣ
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message != WM_QUIT)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				// �������WM_QUIT��Ϣ���˳���ѭ���������˳�
				break;
			}
		}
		else
		{
			// û����Ϣ��ִ�г���֡ѭ��
			Update();
		}
	}
	return true;
}

bool GtFramework::Shutdown()
{
	GtLog("//////////////////////////////////");
	GtLog("GtFramework �رմ���ʵ��");
	if (m_app)
	{
		m_app->OnShutdown();
	}

	g_context.inputer->Destroy();
	// �ͷ���Ⱦ�����ĵ���Ļbuffer
	delete[] g_context.buffer;
	delete[]g_context.zbuffer;
	delete g_context.timer;
	delete g_context.painter;
	delete g_context.inputer;

	GtLog("GtFramework �ر�presenter");
	// �ر�presenter
	m_presenter.Shutdown();

	GtLog("GtFramework �˳�����");
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
	// ע�ᴰ����
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

	// ��������
	m_hWnd = CreateWindow("GtFramework Window Class", createParam.windowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, createParam.width, createParam.height, NULL, NULL, createParam.hInst, NULL);
	//�������λ��
	g_context.hwnd = m_hWnd;

	// �����ߴ�
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

	// ��ʾ����
	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	return true;
}

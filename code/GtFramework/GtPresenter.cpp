#include "stableheader.h"
#include "GtPresenter.h"

// d3d引入
#include "d3d9.h"
#pragma comment(lib, "d3d9.lib")

GtPresenter::GtPresenter(void)
{
}


GtPresenter::~GtPresenter(void)
{
}

bool GtPresenter::Init(const GtPresenterParam& initParam)
{
	//////////////////////////////////////////////////////////////////////////
	// create d3d device for Show Soft Buffer
	if (NULL == (m_d3d9 = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	// bpp 32 XRGB
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.EnableAutoDepthStencil = FALSE;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	d3dpp.BackBufferWidth = initParam.width;
	d3dpp.BackBufferHeight = initParam.height;

	// Create the D3DDevice
	if (FAILED(m_d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, initParam.hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_hwDevice)))
	{
		MessageBox(initParam.hWnd, "无法创建DX设备", "", MB_OK);
		return false;
	}

	// 关闭Z BUFFER
	m_hwDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	m_hwDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// 创建离屏buffer
	IDirect3DSurface9* bbSurf;
	m_hwDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bbSurf);
	D3DSURFACE_DESC bbDesc;
	bbSurf->GetDesc(&bbDesc);
	m_hwDevice->CreateOffscreenPlainSurface(initParam.width, initParam.height,
		bbDesc.Format,
		D3DPOOL_DEFAULT,
		&m_drawSurface, NULL);
	bbSurf->Release();
}

bool GtPresenter::Swap()
{
	D3DLOCKED_RECT lockinfo;
	memset(&lockinfo, 0, sizeof(lockinfo));

	HRESULT res = m_drawSurface->LockRect(&lockinfo, NULL, D3DLOCK_DISCARD);
	if (res != S_OK)
	{
		// FATAL ERROR
		return false;
	}
	
	memcpy(lockinfo.pBits, g_context.buffer, g_context.width * g_context.height * g_context.bpp);
	m_drawSurface->UnlockRect();


	IDirect3DSurface9* bbSurf;
	m_hwDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &bbSurf);
	m_hwDevice->StretchRect(m_drawSurface, NULL, bbSurf, NULL, D3DTEXF_NONE);
	m_hwDevice->Present(NULL, NULL, NULL, NULL);
	bbSurf->Release();

	return true;
}

bool GtPresenter::Shutdown()
{
	if (m_drawSurface)
	{
		m_drawSurface->Release();
	}

	if (m_hwDevice)
	{
		m_hwDevice->Release();
	}

	if (m_d3d9)
	{
		m_d3d9->Release();
	}

	return true;
}

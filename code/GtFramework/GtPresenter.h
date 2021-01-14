/**
  @file GtPresenter.h

  @brief 将内存中的颜色拷贝到显存中的拷贝器

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef GtPresenter_h__
#define GtPresenter_h__

#include "prerequisite.h" ///< 引入全局前提

struct GtPresenterParam
{
	HWND hWnd;
	int width;
	int height;
	int bpp;
};

class GtPresenter
{
public:
	GtPresenter(void);
	~GtPresenter(void);

	bool Init(const GtPresenterParam& initParam);
	bool Swap();
	bool Shutdown();

private:
	// DX硬件对象
	struct IDirect3D9* m_d3d9;
	struct IDirect3DDevice9* m_hwDevice; 
	struct IDirect3DSurface9* m_drawSurface;
};

#endif



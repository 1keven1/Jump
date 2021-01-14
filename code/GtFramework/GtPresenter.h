/**
  @file GtPresenter.h

  @brief ���ڴ��е���ɫ�������Դ��еĿ�����

  @author Kaiming

  ������־ history
  ver:1.0

 */

#ifndef GtPresenter_h__
#define GtPresenter_h__

#include "prerequisite.h" ///< ����ȫ��ǰ��

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
	// DXӲ������
	struct IDirect3D9* m_d3d9;
	struct IDirect3DDevice9* m_hwDevice; 
	struct IDirect3DSurface9* m_drawSurface;
};

#endif



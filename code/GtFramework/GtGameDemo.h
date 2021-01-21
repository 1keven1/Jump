#ifndef GtGameDemo_h__
#define GtGameDemo_h__
#include "GtFrameworkApp.h"
#include "GtPlayer.h"
#include "Rock.h"
#include <vector>

class GtBitmap;

enum EGameState
{
	eGS_Menu,
	eGS_Help,
	eGS_About,
	eGS_Play,
	eGS_Gameover,
};
class GtGameDemo :public GtFrameworkAppBase, public IInputEventListener
{
public:
	GtGameDemo(void);
	~GtGameDemo(void);
	/**
	  @brief 当Framwork初始化时被调用，在函数内部处理app需要的初始化
	  @remark 初始化操作例如：创建一些管理器
	  @return void
	 */
	virtual void OnInit(HWND h);
	/**
	  @brief Framework每一帧调用一次
	  @return void
	  @param float fElapsedTime
	 */
	virtual void OnUpdate(float fElapsedTime);
	/**
	  @brief 当Framework退出时调用，在函数内部处理app需要的清除操作
	  @remark 清除操作例如：存档，摧毁动态内存对象，等等
	 */
	virtual void OnShutdown();
	virtual bool OnInputEvent(const SInputEvent& event);
	void BeiJingGunDong(GtBitmap* bg, float2 pos, float2 pos2, float speed, float* t, float fElapsedTime);//背景图，屏幕相对坐标（锚点左上角），滚动速度
	void ChangeScore(int k);
	void ShowScore();
	void UpdateClient();

	HWND hWnd;
	RECT window;
	int2 clientSize;

	GtPlayer* m_player;
	Rock* rock;
	GtBitmap farScene;
	GtBitmap road;
	GtBitmap* startscene;
	GtBitmap* Aboutscene;
	GtBitmap* Helpscene;
	GtBitmap* overscene;
	std::vector<Rock*> rocks;
	int score;
	GtBitmap* number[10];

};
extern EGameState g_m_state;

#endif // GtGameDemo_h__


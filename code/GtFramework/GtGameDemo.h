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
	  @brief ��Framwork��ʼ��ʱ�����ã��ں����ڲ�����app��Ҫ�ĳ�ʼ��
	  @remark ��ʼ���������磺����һЩ������
	  @return void
	 */
	virtual void OnInit(HWND h);
	/**
	  @brief Frameworkÿһ֡����һ��
	  @return void
	  @param float fElapsedTime
	 */
	virtual void OnUpdate(float fElapsedTime);
	/**
	  @brief ��Framework�˳�ʱ���ã��ں����ڲ�����app��Ҫ���������
	  @remark ����������磺�浵���ݻٶ�̬�ڴ���󣬵ȵ�
	 */
	virtual void OnShutdown();
	virtual bool OnInputEvent(const SInputEvent& event);
	void BeiJingGunDong(GtBitmap* bg, float2 pos, float2 pos2, float speed, float* t, float fElapsedTime);//����ͼ����Ļ������꣨ê�����Ͻǣ��������ٶ�
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


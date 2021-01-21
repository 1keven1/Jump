#ifndef GtPlayer_h__
#define GtPlayer_h__
#include "GtActor.h"
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"winmm.lib")

class GtPlayer :
	public GtActor
{
public:
	GtPlayer(const std::string& name);
	~GtPlayer(void);
	virtual void Restart();
private:
	virtual void OnInit();
	virtual void OnUpdate(float fElapsedTime);
	virtual void OnDestroy();
	virtual void OnKey(const SInputEvent& event);
private:
	GtBitmap* m_run;
	GtBitmap* m_jump;

	GtBitmap* m_currDrawer;

	bool bJump;
	float2 m_jumpForce;
	float2 m_gravity;

};


#endif // GtPlayer_h__


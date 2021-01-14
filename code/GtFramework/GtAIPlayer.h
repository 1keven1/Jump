#ifndef GtAIPlayer_h__
#define GtAIPlayer_h__

#include "gtactor.h"
class GtAIPlayer :
	public GtActor
{
public:
	GtAIPlayer(const std::string& name);
	~GtAIPlayer(void);

private:
	virtual void OnInit();
	virtual void OnUpdate(float fElapsedTime);
	virtual void OnDestroy();
	virtual void OnKey(const SInputEvent& event) {}
	void ChangeState();

private:
	GtBitmap* m_rest;
	GtBitmap* m_run;
	GtBitmap* m_run1;

	GtBitmap* m_currDrawer;

	float2 m_gravity;
	float2 m_movedir;
	float2 m_preMoveDir;
	float m_speed;

	float m_runtime;
	float m_resttime;
	int2 m_repeat;
};

#endif // GtAIPlayer_h__


#include "stableheader.h"
#include "GtAIPlayer.h"




GtAIPlayer::GtAIPlayer(const std::string& name) :GtActor(name)
{
	m_movedir.zero();
	m_preMoveDir.zero();
	m_repeat = int2(1, 1);

	m_currDrawer = NULL;
	m_run = NULL;
	m_run1 = NULL;
	m_rest = NULL;
	m_gravity = float2(0, 80);
	m_speed = 200;

	m_runtime = 0;
	m_resttime = 0;

}


GtAIPlayer::~GtAIPlayer(void)
{
}

void GtAIPlayer::OnInit()
{
	m_rest = g_context.painter->LoadTexture("rest.bmp");
	m_run = g_context.painter->LoadTexture("run.bmp");
	m_run1 = g_context.painter->LoadTexture("run1.bmp");

	m_preMoveDir = float2(1, 0);
	SetPos(float2(300, 200));
	SetWidth(m_rest->GetWidth());
	SetHeight(m_rest->GetHeight());
	SetAnchor(eAA_Bottom);
}

void GtAIPlayer::OnUpdate(float fElapsedTime)
{

	if (m_currDrawer)  //ÏÈ»æÖÆ
	{
		g_context.painter->DrawBitmap(m_currDrawer, m_pos.x - m_currDrawer->GetWidth()/ 2,
			m_bbox.lt.y, m_currDrawer->GetWidth(), m_currDrawer->GetHeight(), 2, eBm_AlphaTest, int2(m_repeat.x, 1));
	}
	g_context.painter->DrawBBox(m_bbox, 0xff00ff00, 5);



	Move(m_gravity * fElapsedTime);

	if (m_movedir.length() > 0.0001f)
	{
		if (m_movedir.x < 0)
			m_repeat.x = -1;
		else
			m_repeat.x = 1;

		m_runtime += fElapsedTime;
		Move(m_movedir * fElapsedTime * m_speed);

		if ((int)(g_context.timer->getTime() * 5) % 2 == 0)
		{
			m_currDrawer = m_run;
		}
		else
		{
			m_currDrawer = m_run1;
		}
	}
	else
	{
		m_resttime += fElapsedTime;
		m_currDrawer = m_rest;
	}

	if (m_pos.x > g_context.width - m_width / 2.f)
	{
		m_pos.x = g_context.width - m_width / 2.f;
	}
	if (m_pos.x < m_width / 2.f)
	{
		m_pos.x = m_width / 2.f;
	}
	float anchordis = 0;
	if (m_anchor == eAA_Bottom)
	{
		anchordis = m_height / 2.f;
	}
	else if (m_anchor == eAA_Top)
	{
		anchordis = -m_height / 2.f;
	}
	if (m_pos.y > g_context.height - m_height / 2.f + anchordis)
	{
		m_pos.y = g_context.height - m_height / 2.f + anchordis;
	}
	if (m_pos.y < m_height / 2.f + anchordis)
	{
		m_pos.y = m_height / 2.f + anchordis;
	}
	ChangeState();
}

void GtAIPlayer::OnDestroy()
{

}


void GtAIPlayer::ChangeState()
{
	if (m_runtime > 3)
	{
		m_preMoveDir = m_movedir;
		m_movedir.zero();
		m_runtime = 0;
	}
	if (m_resttime > 0.5)
	{
		m_movedir = m_preMoveDir;
		m_resttime = 0;
	}
	if (m_pos.x >= g_context.width - m_width / 2.f)
	{
		m_movedir.set(-1, 0);
	}
	if (m_pos.x <= m_width / 2.f)
	{
		m_movedir.set(1, 0);

	}
}

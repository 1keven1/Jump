#include "stableheader.h"
#include "GtPlayer.h"




GtPlayer::GtPlayer(const std::string& name) :GtActor(name), bJump(false)
{
	m_currDrawer = NULL;
	m_jumpForce.zero();
	m_gravity.set(0, 170);
}


GtPlayer::~GtPlayer(void)
{
}

void GtPlayer::Restart()
{
	SetPos(float2(100, 200));
}

void GtPlayer::OnInit()
{
	m_run = g_context.painter->LoadTexture("Sans.bmp");
	m_jump = g_context.painter->LoadTexture("Jump.bmp");
	m_currDrawer = m_run;
	mciSendString(TEXT("open Jump.wav alias jump"), NULL, 0, NULL);

	SetPos(float2(100, 200));
	SetWidth(50);
	SetHeight(m_run->GetHeight());
	SetAnchor(eAA_Bottom);
}

void GtPlayer::OnUpdate(float fElapsedTime)
{
	if (m_currDrawer)
	{
		g_context.painter->DrawBitmap(m_currDrawer, m_pos.x - m_currDrawer->GetWidth() / 2,
			m_bbox.lt.y, m_currDrawer->GetWidth(), m_currDrawer->GetHeight(), 2, eBm_AlphaTest, int2(1, 1));
	}
	//g_context.painter->DrawBBox(m_bbox, 0xff00ff00, 5);

	//jump
	if (m_jumpForce.length() > 0.0001f)
	{
		m_jumpForce.y += fElapsedTime * 1000;
		if (m_jumpForce.y > 0)
		{
			m_jumpForce.y = 0;
		}

		Move(m_jumpForce * fElapsedTime);
	}

	Move(m_gravity * fElapsedTime);
	float anchordis = 0;
	if (m_anchor == eAA_Bottom)
	{
		anchordis = m_height / 2.f;
	}
	else if (m_anchor == eAA_Top)
	{
		anchordis = -m_height / 2.f;
	}
	if (m_pos.y > g_context.height - m_height / 2.f + anchordis - ((1 - 0.8) * g_context.height))
	{
		m_pos.y = g_context.height - m_height / 2.f + anchordis - ((1 - 0.8) * g_context.height);
		if (bJump)
		{
			m_currDrawer = m_run;
			bJump = false;
		}
	}
}

void GtPlayer::OnDestroy()
{
	mciSendString(TEXT("jump fail"), NULL, 0, NULL);

}

void GtPlayer::OnKey(const SInputEvent& event)
{
	switch (event.keyId)
	{
	case  eKI_Space:
	{
		if (event.state == eIS_Pressed)
		{
			if (!bJump)
			{
				m_jumpForce.set(0, -650);
				m_currDrawer = m_jump;
				bJump = true;
				mciSendString(TEXT("play jump from 0"), NULL, 0, NULL);

			}
		}
		break;
	}
	}
}

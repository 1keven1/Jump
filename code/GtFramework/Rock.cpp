#include "stableheader.h"
#include "Rock.h"
#include <time.h>

Rock::Rock() :GtActor("Rock")
{
	rock = NULL;
	speed = 0;
	srand(time(NULL));
	//GtLog("An rock has been created");
}

Rock::~Rock()
{
}

void Rock::OnInit()
{
	random = rand() % 2;
	switch (random)
	{
	case 0:
		rock = g_context.painter->LoadTexture("Rock1.bmp");
		SetPos(float2((float)g_context.width, 0.8 * g_context.height));
		speed = 0.3;
		break;
	case 1:
		rock = g_context.painter->LoadTexture("Bird.bmp");
		SetPos(float2((float)g_context.width, 0.6 * g_context.height));
		speed = 0.3;
		break;
	default:
		break;
	}
	SetWidth(32);
	SetHeight(32);
	SetAnchor(eAA_Bottom);
	bScore = false;
}

void Rock::OnUpdate(float fElapsedTime)
{
	g_context.painter->DrawBitmap(rock, m_pos.x - rock->GetWidth() / 2,
		m_bbox.lt.y, 32, 32, 2, eBm_AlphaTest, int2(1, 1));
	//g_context.painter->DrawBBox(m_bbox, 0xff00ff00, 5);

	Move(float2((-1)*speed * g_context.width * fElapsedTime, 0));
}

void Rock::OnDestroy()
{
	g_context.inputer->RemoveListener(this);
	//GtLog("Rock has been destroied");
}

void Rock::OnKey(const SInputEvent& event)
{
}

void Rock::Restart()
{
	OnInit();
}

bool Rock::CanScore(GtActor* p)
{
	if (bScore)return false;
	else 
	{
		if (GetBBox().rb.x < p->GetBBox().lt.x)
		{
			bScore = true;
			return true;
		}
	}
	return false;
}

bool Rock::BeenHit(GtActor* p)
{
	if ((m_bbox.lt.x > p->GetBBox().rb.x) || (m_bbox.lt.y > p->GetBBox().rb.y)
		|| (m_bbox.rb.x < p->GetBBox().lt.x) || (m_bbox.rb.y < p->GetBBox().lt.y))
		return false;
	else return true;
}

bool Rock::OutOfScreen()
{
	if (GetBBox().rb.x < 0)
	{
		return true;
	}
	else return false;
}


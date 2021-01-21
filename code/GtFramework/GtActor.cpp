#include "stableheader.h"
#include "GtActor.h"



GtActor::GtActor(const std::string& name) :m_name(name),
m_bbox(int2(0, 0), int2(0, 0)),
m_pos(0, 0),
m_width(0),
m_height(0),
m_anchor(eAA_Center)
{

}


GtActor::~GtActor(void)
{
}

void GtActor::Move(const float2& dir)
{
	m_pos = m_pos + dir;
}

void GtActor::Init()
{
	OnInit();
	g_context.inputer->AddListener(this);
}

void GtActor::Update(float fElapsedTime)
{
	//update boundingbox
	int left = m_pos.x - m_width / 2.f;
	int right = m_pos.x + m_width / 2.f;

	int top = m_pos.y - m_height / 2.f;
	int bottom = m_pos.y + m_height / 2.f;

	if (m_anchor == eAA_Top)
	{
		top += m_height / 2.0f;
		bottom += m_height / 2.f;
	}
	else if (m_anchor == eAA_Bottom)
	{
		top -= m_height / 2.f;
		bottom -= m_height / 2.f;
	}

	m_bbox.lt = int2(left, top);
	m_bbox.rb = int2(right, bottom);
	OnUpdate(fElapsedTime);
}

void GtActor::Destroy()
{
	OnDestroy();
}

bool GtActor::OnInputEvent(const SInputEvent& event)
{
	OnKey(event);
	return false;
}

bbox GtActor::GetBBox()
{
	return m_bbox;
}

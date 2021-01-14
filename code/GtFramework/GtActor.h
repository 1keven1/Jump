#ifndef GtActor_h__
#define GtActor_h__
#include "prerequisite.h"

enum EActorAnchor
{
	eAA_Center,
	eAA_Top,
	eAA_Bottom,
};
class GtActor : public IInputEventListener
{
public:
	GtActor(const std::string& name);
	virtual ~GtActor(void);

	void SetPos(const float2& pos) { m_pos = pos; }
	void Move(const float2& dir);

	void SetWidth(float width) { m_width = width; }
	void SetHeight(float height) { m_height = height; }
	void SetAnchor(EActorAnchor anchor) { m_anchor = anchor; }

	void Init();
	void Update(float fElapsedTime);
	void Destroy();
	virtual bool OnInputEvent(const SInputEvent& event);
	bbox GetBBox();
	virtual void Restart() = 0;

protected:
	virtual void OnInit() = 0;
	virtual void OnUpdate(float fElapsedTime) = 0;
	virtual void OnDestroy() = 0;
	virtual void OnKey(const SInputEvent& event) = 0;

protected:
	float2 m_pos;
	float m_width;
	float m_height;
	bbox m_bbox;

	std::string m_name;
	EActorAnchor m_anchor;

};

#endif // GtActor_h__


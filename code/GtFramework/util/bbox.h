/**
  @file bbox.h

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef bbox_h__
#define bbox_h__

class bbox
{
public:
	bbox() :lt(int2(0, 0)), rb(int2(0, 0)) {}
	bbox(const int2& LT, const int2& RB) :lt(LT), rb(RB) {}
	~bbox() {}

	bool insect(const bbox& other)
	{
		////check the bbox is contact with the other bbox
		// axis x
		if (lt.x >= other.rb.x || rb.x <= other.lt.x) return false;

		// axis y
		if (lt.y >= other.rb.y || rb.y <= other.lt.y) return false;

		return true;
	}

	float width()
	{
		return rb.x - lt.x;
	}

	float height()
	{
		return rb.y - lt.y;
	}

	bool valid()
	{
		if (lt.x > rb.x || lt.y > rb.y) return false;
		return true;
	}

public:
	int2 lt;
	int2 rb;
};

#endif
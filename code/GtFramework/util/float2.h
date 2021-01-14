/**
  @file float2.h

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef float2_h__
#define float2_h__

const float INIT_POS_X_FLOAT2 = 0;
const float INIT_POS_Y_FLOAT2 = 0;

class float2
{
public:
	float2(float x, float y) :x(x), y(y) {}
	float2(void) :x(INIT_POS_X_FLOAT2), y(INIT_POS_Y_FLOAT2) {}
	~float2(void) {}
	float2(const float2& another) :x(another.x), y(another.y) {}

	float2& operator = (const float2& another)
	{
		x = another.x;
		y = another.y;
		return *this;
	}

	static float2 Add(const float2& op1, const float2& op2)
	{
		return float2(op1.x + op2.x, op1.y + op2.y);
	}
	static float2 Sub(const float2& op1, const float2& op2)
	{
		return float2(op1.x - op2.x, op1.y - op2.y);
	}
	static float Dot(const float2& op1, const float2& op2)
	{
		return (op1.x * op2.x + op1.y * op2.y);
	}
	static float Cross(const float2& op1, const float2& op2)
	{
		return (op1.x * op2.y - op2.x * op1.y);
	}
	inline float length() const
	{
		return sqrt(x * x + y * y);
	}
	inline float lengthsq() const
	{
		return x * x + y * y;
	}
	inline float2& normalized()
	{
		float len = length();
		x /= len;
		y /= len;
		return *this;
	}
	inline void zero()
	{
		memset(this, 0, sizeof(float2));
	}
	inline void set(float nx, float ny)
	{
		x = nx;
		y = ny;
	}

public:
	float x;
	float y;
};

static inline float2 operator + (const float2& lhs, const float2& rhs)
{
	return float2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static inline float2 operator - (const float2& lhs, const float2& rhs)
{
	return float2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static inline float operator * (const float2& lhs, const float2& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}

static inline float2 operator * (const float2& lhs, float value)
{
	return float2(lhs.x * value, lhs.y * value);
}

static inline float operator % (const float2& lhs, const float2& rhs)
{
	return (lhs.x * rhs.y - rhs.x * lhs.y);
}

#endif


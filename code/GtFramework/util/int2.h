/**
  @file int2.h

  @author 廖晟

  更改日志 history
  ver:1.0
  ver:1.1 整理到GtFramework中 
 */

#ifndef int2_h__
#define int2_h__

const int INIT_POS_X = 0;
const int INIT_POS_Y = 0;

class int2
{
public:
	int2(int x, int y) :x(x), y(y) {}
	int2(void) :x(INIT_POS_X), y(INIT_POS_Y) {}
	~int2(void) {}
	int2(const int2& another) :x(another.x), y(another.y) {}

	int2& operator = (const int2& another)
	{
		x = another.x;
		y = another.y;
		return *this;
	}

	static int2 Add(const int2& op1, const int2& op2)
	{
		return int2(op1.x + op2.x, op1.y + op2.y);
	}
	static int2 Sub(const int2& op1, const int2& op2)
	{
		return int2(op1.x - op2.x, op1.y - op2.y);
	}
	static int Dot(const int2& op1, const int2& op2)
	{
		return (op1.x * op2.x + op1.y * op2.y);
	}
	static int Cross(const int2& op1, const int2& op2)
	{
		return (op1.x * op2.y - op2.x * op1.y);
	}

public:
	int x;
	int y;
};

static inline int2 operator + (const int2& lhs, const int2& rhs)
{
	return int2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static inline int2 operator - (const int2& lhs, const int2& rhs)
{
	return int2(lhs.x + rhs.x, lhs.y + rhs.y);
}

static inline int operator * (const int2& lhs, const int2& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}

static inline int operator % (const int2& lhs, const int2& rhs)
{
	return (lhs.x * rhs.y - rhs.x * lhs.y);
}

#endif


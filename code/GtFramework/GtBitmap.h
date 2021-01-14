#ifndef GtBitmap_h__
#define GtBitmap_h__

class GtBitmap
{
public:
	GtBitmap();
	GtBitmap(const std::string& name);
	~GtBitmap(void);

	uint32 getColor(const float2& texcoord) const
	{
		if (!m_data)
		{
			return 0;
		}

		// 取得实际坐标
		float x = texcoord.x * m_width;
		float y = texcoord.y * m_height;

		// 取整
		int ix = (int)(x);
		int iy = (int)(y);

		return getColor(int2(ix, iy));
	}

	uint32 getColor(const int2& texcoord) const
	{
		if (!m_data)
		{
			return 0;
		}



		// 回转一下，保证x和y在范围内
		int x = texcoord.x;
		int y = texcoord.y;

		x %= m_width;
		y %= m_height;

		// BMP默认是逆序的
		y = m_height - 1 - y;

		return m_data[x + y * m_width];
	}

	const uint32 GetWidth() const { return m_width; }
	const uint32 GetHeight() const { return m_height; }
	const uint32* GetData() const { return m_data; }


private:
	uint32 m_width;
	uint32 m_height;
	uint32 m_bpp;
	uint32* m_data;
};


#endif // GtBitmap_h__



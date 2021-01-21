#include "stableheader.h"
#include "GtPainter.h"
#include "GtBitmap.h"

void GtPEBitmap::Draw()
{
	if (m_bmp) //如果m_bmp不为空
	{
		int address = 0;
		switch (m_blendMode)
		{
		case eBm_Direct:
		{
			for (int iy = 0; iy < m_height; ++iy)  //对要绘制的图片进行扫描
			{
				//clip y
				if (iy + m_y < 0)
				{
					continue;
				}
				else if (iy + m_y >= g_context.height)
					break;

				//每行的buffer起始地址
				address = m_x + (iy + m_y) * g_context.width; //得到的address获取的是在整个界面的地址
				for (int ix = 0; ix < m_width; ++ix)
				{
					//clip x 如果超出了画面范围，则裁剪。。。。
					if (ix + m_x < 0)
					{
						address++; //将起始位置向后移
						continue;
					}
					else if (ix + m_x >= g_context.width)
						break;

					//防止地址越界
					if (address >= 0 && address < g_context.width * g_context.height)
					{
						//z order的检测
						uint8* depth = g_context.zbuffer + address; // zbuffer是一个指针，加上偏移量即为对应数组元素的位置

						//如果没有被覆盖
						if (*depth < m_zOrder) //若当前画面的zbuffer值小于图片的z值（m_zOrder）z轴向外。。。
						{
							uint32* colorbuffer = g_context.buffer + address;//取得buffer数组在当前位置点的地址
							//m_repeat为在绘制时水平方向、垂直方向重复绘制的次数~
							//然后把其转成纹理坐标：0.0-1.0*repeat
							uint32 color = m_bmp->getColor(float2(ix * m_repeat.x / (float)m_width, iy * m_repeat.y / (float)m_height));
							//直接写入颜色和新的zOrder
							*colorbuffer = color; // 将前面的颜色覆盖到后面的颜色上，即冲刷掉后面的颜色
							*depth = m_zOrder;
						}
					}
					//处理完一个元素，往后移动
					++address;
				}
			}
		}
		break;

		//alpaha
		case eBm_AlphaBlend:
		{
			for (int iy = 0; iy < m_height; ++iy)
			{
				//clip y
				if (iy + m_y < 0)
				{
					continue;
				}
				else if (iy + m_y >= g_context.height)
					break;

				//每行的buffer起始地址
				address = m_x + (iy + m_y) * g_context.width; //得到的address获取的是在整个界面的地址
				for (int ix = 0; ix < m_width; ++ix)
				{
					//clip x 如果超出了画面范围，则裁剪。。。。
					if (ix + m_x < 0)
					{
						address++; //将起始位置向后移
						continue;
					}
					else if (ix + m_x >= g_context.width)
						break;

					//防止地址越界
					if (address >= 0 && address < g_context.width * g_context.height)
					{
						//z order的检测
						uint8* depth = g_context.zbuffer + address; // zbuffer是一个指针，加上偏移量即为对应数组元素的位置

						//如果没有被覆盖
						if (*depth < m_zOrder) //若当前画面的zbuffer值小于图片的z值（m_zOrder）z轴向外。。。
						{
							uint32* colorbuffer = g_context.buffer + address;
							uint32 color = m_bmp->getColor(float2(ix * m_repeat.x / (float)m_width, iy * m_repeat.y / (float)m_height));
							uint8 alpha = GtGetAlpha(color);

							//利用alpha值来混合原有的颜色和现有的颜色
							*colorbuffer = GtColorMulUint8(*colorbuffer, 255 - alpha) + GtColorMulUint8(color, alpha);
						}
					}
					address++;
				}
			}
		}
		break;
		case eBm_AlphaTest:
		{
			for (int iy = 0; iy < m_height; ++iy)
			{
				//clip y
				if (iy + m_y < 0)
				{
					continue;
				}
				else if (iy + m_y >= g_context.height)
					break;

				//每行的buffer起始地址
				address = m_x + (iy + m_y) * g_context.width; //得到的address获取的是在整个界面的地址
				for (int ix = 0; ix < m_width; ++ix)
				{
					//clip x 如果超出了画面范围，则裁剪。。。。
					if (ix + m_x < 0)
					{
						address++; //将起始位置向后移
						continue;
					}
					else if (ix + m_x >= g_context.width)
						break;

					//防止地址越界
					if (address >= 0 && address < g_context.width * g_context.height)
					{
						//z order的检测
						uint8* depth = g_context.zbuffer + address; // zbuffer是一个指针，加上偏移量即为对应数组元素的位置

						//如果没有被覆盖
						if (*depth < m_zOrder) //若当前画面的zbuffer值小于图片的z值（m_zOrder）z轴向外。。。
						{
							uint32 color = m_bmp->getColor(float2(ix * m_repeat.x / (float)m_width, iy * m_repeat.y / (float)m_height));
							uint8 alpha = GtGetAlpha(color);

							if (alpha > 10)
							{
								uint32* colorbuffer = g_context.buffer + address;

								//通过alpha检测，写入新的颜色和zorder
								*colorbuffer = color;
								*depth = m_zOrder;
							}
						}
					}
					address++;
				}
			}
		}
		break;
		default:
			break;
		}
	}
}

void GtPEBBox::Draw()
{
	if (m_bbox.lt.x < 0) //过界，重定位包围盒的起始位置
	{
		m_bbox.lt.x = 0;
	}
	else if (m_bbox.rb.x >= g_context.width)
	{
		m_bbox.rb.x = g_context.width - 1;
	}
	if (m_bbox.lt.y < 0)
	{
		m_bbox.lt.y = 0;
	}
	else if (m_bbox.rb.y >= g_context.height)
	{
		m_bbox.rb.y = g_context.height - 1;
	}
	if (!m_bbox.valid()) //若包围盒不合法
	{
		return;
	}

	//前期处理完毕
	//进入正式绘制过程
	//如何绘制呢？？？？
	//先绘制第一行和最后一行，再绘制左边一行和右边一行
	//draw the top line
	int address = m_bbox.lt.y * g_context.width + m_bbox.lt.x;
	for (uint32 i = 0; i <= m_bbox.width(); ++i)
	{
		uint8* depth = g_context.zbuffer + address;
		if (*depth < m_zOrder)
		{
			g_context.buffer[address] = m_color;
			*depth = m_zOrder;
		}
		++address;
	}

	//draw the bottom line
	address = m_bbox.rb.y * g_context.width + m_bbox.lt.x;
	for (uint32 i = 0; i <= m_bbox.width(); ++i)
	{
		uint8* depth = g_context.zbuffer + address;
		if (*depth < m_zOrder)
		{
			g_context.buffer[address] = m_color;
			*depth = m_zOrder;
		}
		++address;
	}
	//draw left v line
	address = (m_bbox.lt.y + 1) * g_context.width + m_bbox.lt.x;
	for (uint32 i = 0; i <= m_bbox.height() - 1; ++i)
	{
		uint8* depth = g_context.zbuffer + address;
		if (*depth < m_zOrder)
		{
			g_context.buffer[address] = m_color;
			*depth = m_zOrder;
		}
		address += g_context.width;
	}

	//draw the right v line
	address = (m_bbox.lt.y + 1) * g_context.width + m_bbox.rb.x;
	for (uint32 i = 0; i <= m_bbox.height() - 1; ++i)
	{
		uint8* depth = g_context.zbuffer + address;
		if (*depth < m_zOrder)
		{
			g_context.buffer[address] = m_color;
			*depth = m_zOrder;
		}
		address += g_context.width;
	}
}
GtPainter::GtPainter(void)
{
	m_mapBitmaps.clear();
}


GtPainter::~GtPainter(void)
{
	GtBitmapLibrary::iterator it = m_mapBitmaps.begin();
	for (; it != m_mapBitmaps.end(); ++it)
	{
		delete it->second;
	}
	m_mapBitmaps.clear();
}

void GtPainter::DrawBitmap(GtBitmap* bmp, int x, int y, int w, int h, int zOrder, EGtBlendMode blendMode, int2& repeat /* = int2 */)
{
	GtPEBitmap* bitmap = new GtPEBitmap(bmp, x, y, w, h, zOrder, blendMode, repeat);
	switch (blendMode)
	{
	case eBm_Direct:
	case eBm_AlphaTest:
		m_opaquePEs.push_back(bitmap);
		break;
	case eBm_AlphaBlend:
		m_transpPEs.push_back(bitmap);
		break;
	default:
		delete bitmap;
	}
}
void GtPainter::DrawBBox(const bbox& bbox, uint32 color, int zOrder)
{
	GtPEBBox* peBBox = new GtPEBBox(bbox, color, zOrder);
	m_opaquePEs.push_back(peBBox);
}



//绘制元素的排序结构
struct GtPESortStruct
{
	GtPESortStruct(GtPaintElement* pe) :m_pe(pe) {}
	GtPaintElement* m_pe;

	bool operator < (const GtPESortStruct& other)
	{
		if (other.m_pe->m_zOrder < m_pe->m_zOrder)
		{
			return true;
		}
		return false;
	}
};

typedef std::list<GtPESortStruct> GtPESortlist;

void GtPainter::Flush()
{
	//1、对不透明绘制元素进行从近到远的排序
	//a 填充排序队列结构
	GtPESortlist list;
	for (uint32 i = 0; i < m_opaquePEs.size(); ++i)
	{
		list.push_back(GtPESortStruct(m_opaquePEs[i]));
	}
	//b stl利用operater < 排序
	list.sort();

	//2、按照排序结果绘制不透明元素
	GtPESortlist::iterator it = list.begin();
	for (; it != list.end(); ++it)
	{
		it->m_pe->Draw();
	}

	//3、对透明元素进行从近到远的排序
	//  a 清空排序队列，填充排序队列
	list.clear();
	for (uint32 i = 0; i < m_transpPEs.size(); ++i)
	{
		list.push_back(GtPESortStruct(m_transpPEs[i]));
	}
	//b stl用operator < 排序
	list.sort();

	//4、按照排序队列的逆序，绘制透明元素
	GtPESortlist::reverse_iterator itr = list.rbegin();
	for (; itr != list.rend(); ++itr)
	{
		itr->m_pe->Draw();
	}
	//5、清空不透明元素队列
	for (uint32 i = 0; i < m_opaquePEs.size(); ++i)
	{
		delete m_opaquePEs[i];
	}
	m_opaquePEs.clear();
	GtPaintElements(m_opaquePEs).swap(m_opaquePEs);
	//6、清空透明元素队列
	for (uint32 i = 0; i < m_transpPEs.size(); ++i)
	{
		delete m_transpPEs[i];
	}
	m_transpPEs.clear();
	GtPaintElements(m_transpPEs).swap(m_transpPEs);
}

GtBitmap* GtPainter::LoadTexture(const std::string rel_filename)
{
	GtBitmapLibrary::iterator it = m_mapBitmaps.find(rel_filename);

	if (it != m_mapBitmaps.end())
	{
		return it->second; //second代表对应的Bitmap
	}
	else
	{
		GtBitmap* bitmap = new GtBitmap(rel_filename);
		if (!bitmap->GetData())
		{
			delete bitmap;
			return NULL;
		}

		m_mapBitmaps.insert(GtBitmapLibrary::value_type(rel_filename, bitmap));

		return bitmap;
	}
}
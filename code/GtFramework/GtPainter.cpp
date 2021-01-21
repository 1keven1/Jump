#include "stableheader.h"
#include "GtPainter.h"
#include "GtBitmap.h"

void GtPEBitmap::Draw()
{
	if (m_bmp) //���m_bmp��Ϊ��
	{
		int address = 0;
		switch (m_blendMode)
		{
		case eBm_Direct:
		{
			for (int iy = 0; iy < m_height; ++iy)  //��Ҫ���Ƶ�ͼƬ����ɨ��
			{
				//clip y
				if (iy + m_y < 0)
				{
					continue;
				}
				else if (iy + m_y >= g_context.height)
					break;

				//ÿ�е�buffer��ʼ��ַ
				address = m_x + (iy + m_y) * g_context.width; //�õ���address��ȡ��������������ĵ�ַ
				for (int ix = 0; ix < m_width; ++ix)
				{
					//clip x ��������˻��淶Χ����ü���������
					if (ix + m_x < 0)
					{
						address++; //����ʼλ�������
						continue;
					}
					else if (ix + m_x >= g_context.width)
						break;

					//��ֹ��ַԽ��
					if (address >= 0 && address < g_context.width * g_context.height)
					{
						//z order�ļ��
						uint8* depth = g_context.zbuffer + address; // zbuffer��һ��ָ�룬����ƫ������Ϊ��Ӧ����Ԫ�ص�λ��

						//���û�б�����
						if (*depth < m_zOrder) //����ǰ�����zbufferֵС��ͼƬ��zֵ��m_zOrder��z�����⡣����
						{
							uint32* colorbuffer = g_context.buffer + address;//ȡ��buffer�����ڵ�ǰλ�õ�ĵ�ַ
							//m_repeatΪ�ڻ���ʱˮƽ���򡢴�ֱ�����ظ����ƵĴ���~
							//Ȼ�����ת���������꣺0.0-1.0*repeat
							uint32 color = m_bmp->getColor(float2(ix * m_repeat.x / (float)m_width, iy * m_repeat.y / (float)m_height));
							//ֱ��д����ɫ���µ�zOrder
							*colorbuffer = color; // ��ǰ�����ɫ���ǵ��������ɫ�ϣ�����ˢ���������ɫ
							*depth = m_zOrder;
						}
					}
					//������һ��Ԫ�أ������ƶ�
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

				//ÿ�е�buffer��ʼ��ַ
				address = m_x + (iy + m_y) * g_context.width; //�õ���address��ȡ��������������ĵ�ַ
				for (int ix = 0; ix < m_width; ++ix)
				{
					//clip x ��������˻��淶Χ����ü���������
					if (ix + m_x < 0)
					{
						address++; //����ʼλ�������
						continue;
					}
					else if (ix + m_x >= g_context.width)
						break;

					//��ֹ��ַԽ��
					if (address >= 0 && address < g_context.width * g_context.height)
					{
						//z order�ļ��
						uint8* depth = g_context.zbuffer + address; // zbuffer��һ��ָ�룬����ƫ������Ϊ��Ӧ����Ԫ�ص�λ��

						//���û�б�����
						if (*depth < m_zOrder) //����ǰ�����zbufferֵС��ͼƬ��zֵ��m_zOrder��z�����⡣����
						{
							uint32* colorbuffer = g_context.buffer + address;
							uint32 color = m_bmp->getColor(float2(ix * m_repeat.x / (float)m_width, iy * m_repeat.y / (float)m_height));
							uint8 alpha = GtGetAlpha(color);

							//����alphaֵ�����ԭ�е���ɫ�����е���ɫ
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

				//ÿ�е�buffer��ʼ��ַ
				address = m_x + (iy + m_y) * g_context.width; //�õ���address��ȡ��������������ĵ�ַ
				for (int ix = 0; ix < m_width; ++ix)
				{
					//clip x ��������˻��淶Χ����ü���������
					if (ix + m_x < 0)
					{
						address++; //����ʼλ�������
						continue;
					}
					else if (ix + m_x >= g_context.width)
						break;

					//��ֹ��ַԽ��
					if (address >= 0 && address < g_context.width * g_context.height)
					{
						//z order�ļ��
						uint8* depth = g_context.zbuffer + address; // zbuffer��һ��ָ�룬����ƫ������Ϊ��Ӧ����Ԫ�ص�λ��

						//���û�б�����
						if (*depth < m_zOrder) //����ǰ�����zbufferֵС��ͼƬ��zֵ��m_zOrder��z�����⡣����
						{
							uint32 color = m_bmp->getColor(float2(ix * m_repeat.x / (float)m_width, iy * m_repeat.y / (float)m_height));
							uint8 alpha = GtGetAlpha(color);

							if (alpha > 10)
							{
								uint32* colorbuffer = g_context.buffer + address;

								//ͨ��alpha��⣬д���µ���ɫ��zorder
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
	if (m_bbox.lt.x < 0) //���磬�ض�λ��Χ�е���ʼλ��
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
	if (!m_bbox.valid()) //����Χ�в��Ϸ�
	{
		return;
	}

	//ǰ�ڴ������
	//������ʽ���ƹ���
	//��λ����أ�������
	//�Ȼ��Ƶ�һ�к����һ�У��ٻ������һ�к��ұ�һ��
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



//����Ԫ�ص�����ṹ
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
	//1���Բ�͸������Ԫ�ؽ��дӽ���Զ������
	//a ���������нṹ
	GtPESortlist list;
	for (uint32 i = 0; i < m_opaquePEs.size(); ++i)
	{
		list.push_back(GtPESortStruct(m_opaquePEs[i]));
	}
	//b stl����operater < ����
	list.sort();

	//2���������������Ʋ�͸��Ԫ��
	GtPESortlist::iterator it = list.begin();
	for (; it != list.end(); ++it)
	{
		it->m_pe->Draw();
	}

	//3����͸��Ԫ�ؽ��дӽ���Զ������
	//  a ���������У�����������
	list.clear();
	for (uint32 i = 0; i < m_transpPEs.size(); ++i)
	{
		list.push_back(GtPESortStruct(m_transpPEs[i]));
	}
	//b stl��operator < ����
	list.sort();

	//4������������е����򣬻���͸��Ԫ��
	GtPESortlist::reverse_iterator itr = list.rbegin();
	for (; itr != list.rend(); ++itr)
	{
		itr->m_pe->Draw();
	}
	//5����ղ�͸��Ԫ�ض���
	for (uint32 i = 0; i < m_opaquePEs.size(); ++i)
	{
		delete m_opaquePEs[i];
	}
	m_opaquePEs.clear();
	GtPaintElements(m_opaquePEs).swap(m_opaquePEs);
	//6�����͸��Ԫ�ض���
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
		return it->second; //second�����Ӧ��Bitmap
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
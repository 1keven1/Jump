/**
	@file GtPainter.h
	@brief GtFramework ��ͼ����
	@author
	������־ history
	ver:1.0
*/
#ifndef GtPainter_h_
#define GtPainter_h_
#include "prerequisite.h"
#include "GtBitmap.h"

typedef std::map <std::string, GtBitmap*> GtBitmapLibrary;

enum EGtBlendMode
{
	eBm_Direct,
	eBm_AlphaTest,
	eBm_AlphaBlend,
};
/**
	@brief Gt��ͼԪ�ػ���
	@remark �����࣬��Ҫ����Ļ�ͼԪ�ؼ̳�
*/
struct GtPaintElement
{
	GtPaintElement(int zOrder) :m_zOrder(zOrder) {} //����zOrder����Ԫ��
	virtual ~GtPaintElement() {}
	virtual void Draw() = 0;

	int m_zOrder;
};
typedef std::vector<GtPaintElement*> GtPaintElements;

/**
	@brief Gt��ͼԪ�أ�λͼ
	@remark ͨ��Ҫ���Ƶ�x,y,w,h,��zOrder��blendmode������
*/
class GtPEBitmap : public GtPaintElement
{
public:
	GtPEBitmap(GtBitmap* bmp, int x, int y, int w, int h, int zOrder, EGtBlendMode blendMode, int2& repeat) :GtPaintElement(zOrder),
		m_bmp(bmp), m_x(x), m_y(y), m_repeat(repeat), m_width(w), m_height(h), m_blendMode(blendMode)
	{};
	virtual ~GtPEBitmap() {}
	virtual void Draw();
private:
	/**
	@brief ����λͼ
	@return void
	@param GtBitmap* bmp ���Ƶ�λͼָ��
	@param int x ���Ƶ���������x
	@param int y ���Ƶ���������y
	@param int w ���ƵĿ��
	@param int h  ���Ƶĸ߶�
	@param int zOrder z���꣬�Լ��ƶ�
	@param EGtBlendMode blendMode ���ģʽ
*/
	GtBitmap* m_bmp;
	int m_x; //���Ƶ����Ͻǵ��x
	int m_y; //���Ƶ����Ͻǵ�y
	int m_width;
	int m_height;
	int2 m_repeat;
	int m_blendMode;
};

class GtPEBBox :public GtPaintElement
{
public:
	GtPEBBox(const bbox& bbox, uint32 color, int zOrder) :GtPaintElement(zOrder),
		m_bbox(bbox), m_color(color) {};
	virtual ~GtPEBBox() {}
	virtual void Draw();
private:
	bbox m_bbox;
	uint32 m_color;
};
/**
	@brief Gt��ͼ��
	@remark �����ṩDrawXXX�ӿ�
	flushʱ�����Ż���������������У�һ����͸�����У�һ��͸������
*/
class GtPainter
{
public:
	GtPainter(void);
	~GtPainter(void);


	void DrawBitmap(GtBitmap* bmp, int x, int y, int w, int h, int zOrder, EGtBlendMode blendMode, int2& repeat = int2(1, 1));

	void DrawBBox(const bbox& bbox, uint32 color, int zOrder);

	GtBitmap* LoadTexture(const std::string rel_filename);

	/**
		@brief ʵ�ʻ��Ƶ���
		@return void
	*/
	void Flush();

private:
	GtPaintElements m_opaquePEs;	 //��͸��Ԫ�ػ��ƶ���
	GtPaintElements m_transpPEs;		 //͸��Ԫ�ػ��ƶ���
	GtBitmapLibrary m_mapBitmaps;
};

#endif

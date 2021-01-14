/**
	@file GtPainter.h
	@brief GtFramework 绘图器类
	@author
	更改日志 history
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
	@brief Gt绘图元素基类
	@remark 抽象类，需要具体的绘图元素继承
*/
struct GtPaintElement
{
	GtPaintElement(int zOrder) :m_zOrder(zOrder) {} //根据zOrder绘制元素
	virtual ~GtPaintElement() {}
	virtual void Draw() = 0;

	int m_zOrder;
};
typedef std::vector<GtPaintElement*> GtPaintElements;

/**
	@brief Gt绘图元素：位图
	@remark 通过要绘制的x,y,w,h,和zOrder，blendmode来创立
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
	@brief 绘制位图
	@return void
	@param GtBitmap* bmp 绘制的位图指针
	@param int x 绘制的左上坐标x
	@param int y 绘制的左上坐标y
	@param int w 绘制的宽度
	@param int h  绘制的高度
	@param int zOrder z坐标，自己制定
	@param EGtBlendMode blendMode 混合模式
*/
	GtBitmap* m_bmp;
	int m_x; //绘制的左上角点的x
	int m_y; //绘制的左上角的y
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
	@brief Gt绘图器
	@remark 对外提供DrawXXX接口
	flush时按照优化排序绘制两个队列，一个不透明队列，一个透明队列
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
		@brief 实际绘制调用
		@return void
	*/
	void Flush();

private:
	GtPaintElements m_opaquePEs;	 //不透明元素绘制队列
	GtPaintElements m_transpPEs;		 //透明元素绘制队列
	GtBitmapLibrary m_mapBitmaps;
};

#endif

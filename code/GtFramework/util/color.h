/**
  @file color.h

  @author Kaiming

  更改日志 history
  ver:1.0

 */

#ifndef color_h__
#define color_h__

static inline uint32 GtColorMulFloat(uint32& color1, float ratio)
{
	return ((int)(((color1 & 0xFF000000) >> 24)* ratio) << 24 |
		(int)(((color1 & 0x00FF0000) >> 16)* ratio) << 16 |
		(int)(((color1 & 0x0000FF00) >> 8)* ratio) << 8 |
		(int)(((color1 & 0x000000FF) >> 0)* ratio) << 0
		);
}

static inline uint32 GtColorMulUint8(uint32& color1, uint8 ratio)
{
	return ((((color1 & 0xFF000000) >> 24)* ratio / 255) << 24 |
		(((color1 & 0x00FF0000) >> 16)* ratio / 255) << 16 |
		(((color1 & 0x0000FF00) >> 8)* ratio / 255) << 8 |
		(((color1 & 0x000000FF) >> 0)* ratio / 255) << 0
		);
}

static inline uint8 GtGetAlpha(uint32 color)
{
	return ((color & 0xff000000) >> 24);
}

#endif
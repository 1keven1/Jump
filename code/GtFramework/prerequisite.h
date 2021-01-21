/**
  @file prerequisite.h

  @brief ȫ��ǰ��

  @author Kaiming

  ������־ history
  ver:1.0

 */

#ifndef prerequisite_h__
#define prerequisite_h__

 // windows libraryͷ�ļ�
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <iostream>
// stlͷ�ļ�
#include <vector>
#include <string>
#include <list>
#include <map>


// other stuff
typedef unsigned char uint8;
typedef unsigned int uint32;
typedef int int32;



class GtPainter;
class SrInputManager;
class GtTimer;
/**
 @brief ��Ⱦ������
 */
struct GtRenderContext
{
	int width;		///< ���ڿ��
	int height;		///< ���ڸ߶�
	int bpp;		///< �����ֽ���(4byte)
	uint32* buffer; ///< ���������׵�ַ
	uint8* zbuffer;

	GtPainter* painter;
	SrInputManager* inputer;
	GtTimer* timer;

	//�������λ��
	HWND hwnd;
};
extern GtRenderContext g_context;

inline std::string& getMediaPath()
{
	static bool first = true;
	static std::string path;
	if (first)
	{
		first = false;

		char buffer[MAX_PATH];
		char* strLastSlash = NULL;
		GetModuleFileName(NULL, buffer, MAX_PATH);
		buffer[MAX_PATH - 1] = 0;

		strLastSlash = strrchr(buffer, '\\');
		if (strLastSlash)
		{
			*(strLastSlash + 1) = '\0';
		}

		path = buffer;
	}

	return path;
}
static inline float GtRandomFloat(float min, float max)
{
	float f01 = (float)(rand() % 1000000) / (float)1000000;
	return (min + f01 * (max - min));
}

static inline int GtRandomInt(int min, int max)
{
	int f01 = rand() % (max - min);
	return min + f01;
}


#include "util/int2.h"
#include "util/float2.h"
#include "util/color.h"
#include "util/bbox.h"
#include "util/input.h"
#include "util/timer.h"

#endif
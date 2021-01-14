#include "stableheader.h"
#include "GtBitmap.h"



GtBitmap::GtBitmap()
{
}

GtBitmap::GtBitmap(const std::string& name) :m_width(0), m_height(0), m_bpp(0), m_data(0)
{
	//	UINT32 m_size;
	//	UINT32* temp;
	char* start;
	GtFile bitmapfile(name);
	bitmapfile.Open();
	if (bitmapfile.IsOpen())
	{
		start = bitmapfile.Data();
		//获得文件头
		tagBITMAPFILEHEADER* header = (tagBITMAPFILEHEADER*)start;
		tagBITMAPINFO* info = (tagBITMAPINFO*)((char*)start + sizeof(tagBITMAPFILEHEADER));

		//基本数据读取
		m_width = info->bmiHeader.biWidth;
		m_height = info->bmiHeader.biHeight;
		m_bpp = info->bmiHeader.biBitCount;

		GtLog("打开[%s] width: %d | height: %d | bpp: %d | offset: %d | size: %d kb", name.c_str(),
			info->bmiHeader.biWidth,
			info->bmiHeader.biHeight,
			info->bmiHeader.biBitCount,
			header->bfOffBits,
			header->bfSize / 1024);


		//复制数据
		m_data = new UINT32[m_width * m_height];
		UINT8* colorStart = (UINT8*)(start + header->bfOffBits);


		if (m_bpp == 32)//32位纹理直接拷贝
		{
			//memcpy(m_data, colorStart, 4 * m_width * m_height);
			
			for ( uint32 i=0; i<m_width*m_height; ++i )
			{
					m_data[i] = (colorStart[i*4+0]<<0) | (colorStart[i*4+1]<<8) |
						(colorStart[i*4+2]<<16) | (colorStart[i*4+3]<<24);
			}

		}
		else if (m_bpp == 24)//24位纹理逐位拷贝  //存储的时候是GBR的存储方法
		{
			for (uint32 i = 0; i < m_width * m_height; ++i)
			{
				m_data[i] = 0xff << 24 | (colorStart[i * 3 + 0] << 0) |
					(colorStart[i * 3 + 1] << 8) |
					(colorStart[i * 3 + 2] << 16);
			}
		}
		else
		{
			delete[]m_data;
			m_data = NULL;
		}
	}
}


GtBitmap::~GtBitmap(void)
{
	delete[]m_data;
}

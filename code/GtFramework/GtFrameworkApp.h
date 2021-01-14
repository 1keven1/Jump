/**
  @file GtFrameworkApp.h

  @brief GtFramework��Ϸ���, App����
  @author Kaiming

  ������־ history
  ver:1.0

 */

#ifndef GtFrameworkApp_h__
#define GtFrameworkApp_h__

#include "prerequisite.h"
#include "GtFramework.h"

 /**
  GtFramework App���
  */
struct GtFrameworkAppBase
{
	virtual ~GtFrameworkAppBase() {}


	/**
	  @brief ��Framwork��ʼ��ʱ�����ã��ں����ڲ�����app��Ҫ�ĳ�ʼ��
	  @remark ��ʼ���������磺����һЩ������
	  @return void
	 */
	virtual void OnInit(HWND h) = 0;
	/**
	  @brief Frameworkÿһ֡����һ��
	  @return void
	  @param float fElapsedTime
	 */
	virtual void OnUpdate(float fElapsedTime) = 0;
	/**
	  @brief ��Framework�˳�ʱ���ã��ں����ڲ�����app��Ҫ���������
	  @remark ����������磺�浵���ݻٶ�̬�ڴ���󣬵ȵ�
	  @return void
	 */
	virtual void OnShutdown() = 0;
};

#endif
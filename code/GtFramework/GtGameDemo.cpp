#include "stableheader.h"
#include "GtGameDemo.h"
#include "GtPlayer.h"
#include<windows.h>
#include<Mmsystem.h>
#include <time.h>
#pragma comment(lib,"winmm.lib")


EGameState g_m_state;
float texX, texY;
float2 mult;
float t1 = 0; float t2 = 0;
float timer = 0;
bool bCreated = false;
float delta;
GtGameDemo::GtGameDemo(void) :farScene("Far.bmp"), road("Road.bmp"), window()
{
	g_m_state = eGS_Menu;
	//����α���������
	srand(time(NULL));
}

GtGameDemo::~GtGameDemo(void)
{
}

void GtGameDemo::OnInit(HWND h)
{
	hWnd = h;
	UpdateClient();
	switch (g_m_state)
	{
		//������
	case eGS_Menu:
		g_context.inputer->AddListener(this);
		startscene = g_context.painter->LoadTexture("Start.bmp");
		//���ڽ���
	case eGS_About:
		Aboutscene = g_context.painter->LoadTexture("About.bmp");
		//��������
	case eGS_Help:
		Helpscene = g_context.painter->LoadTexture("Help.bmp");
		//�������
	case eGS_Play:
		m_player = new GtPlayer("mainActor");
		m_player->Init();
		score = 0;
		timer = 0;
		//��������0-9
		{
			number[0] = g_context.painter->LoadTexture("0.bmp");
			number[1] = g_context.painter->LoadTexture("1.bmp");
			number[2] = g_context.painter->LoadTexture("2.bmp");
			number[3] = g_context.painter->LoadTexture("3.bmp");
			number[4] = g_context.painter->LoadTexture("4.bmp");
			number[5] = g_context.painter->LoadTexture("5.bmp");
			number[6] = g_context.painter->LoadTexture("6.bmp");
			number[7] = g_context.painter->LoadTexture("7.bmp");
			number[8] = g_context.painter->LoadTexture("8.bmp");
			number[9] = g_context.painter->LoadTexture("9.bmp");

		}
		//������Ƶ
		{
			mciSendString(TEXT("open Fail.wav alias fail"), NULL, 0, NULL);
			mciSendString(TEXT("open Music.mp3 alias bgm"), NULL, 0, NULL);
			mciSendString(TEXT("open correct01.mp3 alias click"), NULL, 0, NULL);
			mciSendString(TEXT("open Coin.mp3 alias coin"), NULL, 0, NULL);
		}
		//GameOver����
	case eGS_Gameover:
		g_context.inputer->AddListener(this);
		overscene = g_context.painter->LoadTexture("GameOver.bmp");
	}
}

void GtGameDemo::OnUpdate(float fElapsedTime)
{
	UpdateClient();
	switch (g_m_state)
	{
		//������
	case eGS_Menu:
		memset(g_context.buffer, 0x23, g_context.width * g_context.height * g_context.bpp);
		memset(g_context.zbuffer, 0x0, g_context.width * g_context.height);
		g_context.painter->DrawBitmap(startscene, 0, 0, g_context.width, g_context.height, 1, eBm_Direct, int2(1, 1));
		break;
		//�������
	case eGS_Play:
		memset(g_context.buffer, 0xff000000, g_context.width * g_context.height * g_context.bpp);
		memset(g_context.zbuffer, 0x0, g_context.width * g_context.height);
		//��������
		BeiJingGunDong(&farScene, float2(0.0f, 0.1f), float2(1.0f, 0.8f), 0.03f, &t1, fElapsedTime);
		BeiJingGunDong(&road, float2(0.0f, 0.8f), float2(1.0f, 1.0f), 0.3f, &t2, fElapsedTime);
		ShowScore();
		if (m_player) m_player->Update(fElapsedTime);
		//�ж��ϰ���
		for (int i = 0; i < rocks.size(); i++)
		{
			if (rocks[i])
			{
				//�Ƿ��뿪��Ļ
				if (rocks[i]->OutOfScreen())
				{
					rocks[i]->Destroy();
					delete rocks[i];
					rocks.erase(rocks.begin() + i);
				}
				else
				{
					rocks[i]->Update(fElapsedTime);
					//����Ƿ��ܵ÷�
					if (rocks[i]->CanScore(m_player))
					{
						//GtLog("��üӷ�");
						mciSendString(TEXT("play coin from 0"), NULL, 0, NULL);

						ChangeScore(1);
					}
					//����Ƿ�ײ��ʯͷ
					if (rocks[i]->BeenHit(m_player))
					{
						//GtLog("Hit");
						g_m_state = eGS_Gameover;
						mciSendString(TEXT("stop bgm"), NULL, 0, NULL);
						mciSendString(TEXT("play fail from 0"), NULL, 0, NULL);
					}
				}
			}
		}
		//��ʱ
		timer += fElapsedTime;
		delta = (rand() % 10) / (float)10;
		//�������ʯͷ
		if ((int)timer % 2 == 0)
		{
			if (delta < timer - (int)timer)
			{
				if (!bCreated)
				{
					//GtLog("%f", timer);
					rock = new Rock();
					rock->Init();
					rocks.push_back(rock);
					bCreated = true;
				}
			}
		}
		else if (bCreated) bCreated = false;
		break;
		//���ڽ���
	case eGS_About:
		memset(g_context.buffer, 0x23, g_context.width * g_context.height * g_context.bpp);
		memset(g_context.zbuffer, 0x0, g_context.width * g_context.height);
		g_context.painter->DrawBitmap(Aboutscene, 0, 0, g_context.width, g_context.height, 1, eBm_Direct, int2(1, 1));
		break;
		//��������
	case eGS_Help:
		memset(g_context.buffer, 0x23, g_context.width * g_context.height * g_context.bpp);
		memset(g_context.zbuffer, 0x0, g_context.width * g_context.height);
		g_context.painter->DrawBitmap(Helpscene, 0, 0, g_context.width, g_context.height, 1, eBm_Direct, int2(1, 1));
		break;
		//GameOver����
	case eGS_Gameover:
		memset(g_context.buffer, 0x23, g_context.width * g_context.height * g_context.bpp);
		memset(g_context.zbuffer, 0x0, g_context.width * g_context.height);
		g_context.painter->DrawBitmap(overscene, 0, 0, g_context.width, g_context.height, 1, eBm_Direct, int2(1, 1));
		ShowScore();
		break;
	}

}
//�ر���Ϸ����
void GtGameDemo::OnShutdown()
{
	g_context.inputer->RemoveListener(this);
	//ɾ������ʵ��
	m_player->Destroy();
	delete m_player;
	delete rock;
	for (int i = 0; i < rocks.size(); i++) rocks[i]->Destroy();
	rocks.clear();
	//�ر�������Ƶ
	mciSendString(TEXT("close fail"), NULL, 0, NULL);
	mciSendString(TEXT("close coin"), NULL, 0, NULL);
	mciSendString(TEXT("close bgm"), NULL, 0, NULL);
	mciSendString(TEXT("close click"), NULL, 0, NULL);
}
//�����¼�
bool GtGameDemo::OnInputEvent(const SInputEvent& event)
{
	switch (g_m_state)
	{
		//������
	case eGS_Menu:
		switch (event.keyId)
		{
			//������
		case eKI_Mouse1:
		{
			if (event.state == eIS_Pressed)
			{
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(g_context.hwnd, &pt);
				//��ʼ��ť
				if (pt.y > (19 * mult.y) && pt.y < (36 * mult.y) && pt.x>(95 * mult.x) && pt.x < (161 * mult.x))
				{
					if (m_player) m_player->Init();
					rocks.clear();
					score = 0;
					timer = 0;
					GtLog("��ʼ��Ϸ");
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					g_m_state = eGS_Play;
					mciSendString(TEXT("play bgm from 0 repeat"), NULL, 0, NULL);
				}
				//���ڰ�ť
				if (pt.y > (6 * mult.y) && pt.y < (30 * mult.y) && pt.x>(6 * mult.x) && pt.x < (30 * mult.x))
				{
					GtLog("������Ϸ");
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					g_m_state = eGS_About;
				}
				//������ť
				if (pt.y > (6 * mult.y) && pt.y < (30 * mult.y) && pt.x>(226 * mult.x) && pt.x < (250 * mult.x))
				{
					GtLog("����");
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					g_m_state = eGS_Help;
				}
				//�˳���ť
				if (pt.y > (48 * mult.y) && pt.y < (65 * mult.y) && pt.x>(95 * mult.x) && pt.x < (161 * mult.x))
				{
					GtLog("������˳�!");
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					exit(1);
				}
			}
			break;
		}
		default:
			break;
		}
		break;
		//���ڽ���Ͱ�������
	case eGS_About:
	case eGS_Help:
		switch (event.keyId)
		{
			//������
		case eKI_Mouse1:
		{
			if (event.state == eIS_Pressed)
			{
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(g_context.hwnd, &pt);
				//���ذ�ť
				if (pt.y > (6 * mult.y) && pt.y < (30 * mult.y) && pt.x>(6 * mult.x) && pt.x < (30 * mult.x))
				{
					GtLog("����");
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					g_m_state = eGS_Menu;
				}
			}
			break;
		}
		}
		break;
		//�������
	case eGS_Play:
		switch (event.keyId)
		{
			//��ESC
		case eKI_Escape:
		{
			GtLog("����Ŀ¼");
			mciSendString(TEXT("stop bgm"), NULL, 0, NULL);
			g_m_state = eGS_Menu;
			break;
		}
		}
		break;
		//GameOver����
	case eGS_Gameover:
		switch (event.keyId)
		{
			//������
		case eKI_Mouse1:
			if (event.state == eIS_Pressed)
			{
				POINT pt;
				GetCursorPos(&pt);
				ScreenToClient(g_context.hwnd, &pt);
				//������¿�ʼ��ť
				if (pt.y > (72 * mult.y) && pt.y < (89 * mult.y) && pt.x>(31 * mult.x) && pt.x < (121 * mult.x))
				{
					GtLog("���¿�ʼ");
					mciSendString(TEXT("stop fail"), NULL, 0, NULL);
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					mciSendString(TEXT("play bgm from 0 repeat"), NULL, 0, NULL);
					m_player->Restart();
					rocks.clear();
					timer = 0;
					score = 0;
					g_m_state = eGS_Play;
				}
				//����˳���ť
				if (pt.y > (72 * mult.y) && pt.y < (89 * mult.y) && pt.x>(152 * mult.x) && pt.x < (206 * mult.x))
				{
					GtLog("����Ŀ¼");
					mciSendString(TEXT("play click from 0"), NULL, 0, NULL);
					mciSendString(TEXT("stop fail"), NULL, 0, NULL);
					g_m_state = eGS_Menu;
				}
			}
			break;
		}
	}
	return false;
}
//������������
void GtGameDemo::BeiJingGunDong(GtBitmap* bg, float2 pos1, float2 pos2, float speed, float* t, float fElapsedTime)
{
	int2 k(0, 0);
	for (uint32 iy = (pos1.y * g_context.height); iy < (pos2.y * g_context.height); ++iy)
	{
		k.y++;
		for (uint32 ix = (pos1.x * g_context.width); ix < (pos2.x * g_context.width); ++ix)
		{
			k.x++;
			uint32 address = (iy * g_context.width + ix);
			if (address > 0 && address < g_context.width * g_context.height)
			{
				texX = k.x / ((float)bg->GetWidth() * mult.x);
				texY = k.y / ((float)bg->GetHeight() * mult.y);
				g_context.buffer[address] = bg->getColor(float2(texX + *t, texY));
			}
		}
	}
	*t += speed * fElapsedTime;
}
//���ķ���
void GtGameDemo::ChangeScore(int k)
{
	score += k;
	//GtLog("Score: %d", score);
}
//��ʾ����
void GtGameDemo::ShowScore()
{
	int2 pos(0, 0);
	int size = 0;
	switch (g_m_state)
	{
		//�������
	case eGS_Play:
	{
		pos = int2(10, 10);
		size = 16;
		g_context.painter->DrawBitmap(number[(score % 100) / 10], pos.x, pos.y, size, size, 5, eBm_Direct, int2(1, 1));
		g_context.painter->DrawBitmap(number[score % 10], pos.x + size, pos.y, size, size, 5, eBm_Direct, int2(1, 1));
		break;
	}
	//GameOver����
	case eGS_Gameover:
	{
		pos = int2(330, 120);
		size = 35;
		g_context.painter->DrawBitmap(number[(score % 100) / 10], pos.x, pos.y, size, size, 5, eBm_Direct, int2(1, 1));
		g_context.painter->DrawBitmap(number[score % 10], pos.x + size, pos.y, size, size, 5, eBm_Direct, int2(1, 1));
		break;
	}
	}

}
//���´�����Ϣ
void GtGameDemo::UpdateClient()
{
	if (hWnd) GetClientRect(hWnd, &window);
	clientSize.x = window.right - window.left;
	clientSize.y = window.bottom - window.top;
	mult.x = (float)clientSize.x / (float)256;
	mult.y = (float)clientSize.y / (float)144;
}

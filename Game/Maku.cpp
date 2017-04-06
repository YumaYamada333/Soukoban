//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Maku.cpp
//!
//! @brief  幕処理のソースファイル
//!
//! @date   2017/01/15
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//ヘッダインクルード========================================
#include "Maku.h"
#include "GameMain.h"
#include "Player.h"
#include "Stage.h"

//グローバル変数の定義======================================

//関数の定義==============================================
//コンストラクタ
Maku::Maku()
	: m_maku_posx (0)
	, m_maku_posy (0 - MAKU_HEIGHT)
	, m_maku_grpx(0)
	, m_maku_grpy(0)
	, m_maku_width(MAKU_WIDTH)
	, m_maku_height(MAKU_HEIGHT)
	, m_maku_spdx(0)
	, m_maku_spdy(MAKU_SPEED)
	, m_makumove_count(0)
	, m_makumove_flag(false)
	, m_maku_state(NEXT)
{

}

//デストラクタ
Maku::~Maku()
{

}


//幕の移動開始
void Maku::Maku_SetMove()
{
	m_makumove_flag = true;
}

//幕の移動とフロアチェンジ
void Maku::Maku_Move()
{
	if (m_makumove_flag)
	{
		if (m_maku_posy < 0 
			|| m_makumove_count >= MAKU_TIME)
		{
			m_maku_posy += m_maku_spdy;
		}
		if (m_maku_posy == 0 && m_makumove_count < MAKU_TIME)
		{
			if (m_makumove_count == 0)
			{
				switch (m_maku_state)
				{
				case NEXT:
					//フロア変更
					g_mapinit = 0;
					g_floor_num++;
					g_player.SetPos(PLAYER_START_POSX, PLAYER_START_POSY);
					g_player.SetDigCount(INIT_DIG_COUNT);
					break;
				case START:
					//シーン変更
					g_NextScene = PLAY;
					g_init = 0;
					break;
				case FINISH:
					//シーン変更
					g_NextScene = CLEAR;
					g_init = 0;
					break;
				}
			}

			m_makumove_count++;
		}

		if (m_maku_posy >= SCREEN_HEIGHT)
		{
			m_maku_posy = 0 - MAKU_HEIGHT;
			m_makumove_flag = false;
			m_makumove_count = 0;
		}
	}
}

//幕の描画
void Maku::Maku_Draw()
{
	switch (m_maku_state)
	{
	case NEXT:
		DrawRectTexture(m_maku_posx, m_maku_posy, m_maku_grpx, m_maku_grpy, m_maku_width, m_maku_height, g_grpMaku);
		break;
	case START:
		DrawRectTexture(m_maku_posx, m_maku_posy, m_maku_grpx, m_maku_grpy, m_maku_width, m_maku_height, g_grpStartMaku);
		break;
	case FINISH:
		DrawRectTexture(m_maku_posx, m_maku_posy, m_maku_grpx, m_maku_grpy, m_maku_width, m_maku_height, g_grpFinishMaku);
		break;
	}
}

//幕の変更
void Maku::Maku_Change(int type)
{
	m_maku_state = type;
}

//幕の移動状態を取得
bool Maku::Maku_GetFlag()
{
	return m_makumove_flag;
}
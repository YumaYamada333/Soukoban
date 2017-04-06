//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Carrot.cpp
//!
//! @brief  にんじん処理のソースファイル
//!
//! @date   2017/01/16
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//ヘッダインクルード========================================
#include "Carrot.h"
#include "Player.h"
#include "Stage.h"
#include "Gamemain.h"

//定数
const int CARROT_DIG_BONUS = 10;

//関数の定義==============================================
//コンストラクタ
Carrot::Carrot()
	:m_carrot_posx (0)
	, m_carrot_posy(0)
	, m_carrot_grpx(CARROT_WIDTH)
	, m_carrot_grpy(0)
	, m_carrot_width(CARROT_WIDTH)
	, m_carrot_height(CARROT_HEIGHT)
	, m_carrot_state(false)
{

}

//デストラクタ
Carrot::~Carrot()
{

}

//ニンジンのセット
void Carrot::Carrot_Set()
{
	m_carrot_posx = (rand() % (MAP_WIDTH_MAX - 2) + 1) * CHIP_SIZE;
	m_carrot_posy = (rand() % (MAP_HEIGHT_MAX - 2) + 1) * CHIP_SIZE;
	m_carrot_state = true;
}

//ニンジンとプレイヤーの当たり処理
void Carrot::Carrot_Collision_Player(Player* player)
{
	int f_carrot_X = m_carrot_posx + m_carrot_width / 2;
	int f_carrot_Y = m_carrot_posy + m_carrot_height / 2;

	if (m_carrot_state)
	{
		if (f_carrot_X > player->GetPlayerX()
			&& f_carrot_X < player->GetPlayerX() + PLAYER_WIDTH
			&& f_carrot_Y > player->GetPlayerY()
			&& f_carrot_Y < player->GetPlayerY() + PLAYER_HEIGHT)
		{
			player->AddDigCount(CARROT_DIG_BONUS);
			m_carrot_state = false;
		}
	}
}

//ニンジンの描画
void Carrot::Carrot_Draw()
{
	if (m_carrot_state)
	{
		DrawRectTexture(m_carrot_posx, m_carrot_posy,
			m_carrot_grpx, m_carrot_grpy, m_carrot_width, m_carrot_height, g_BoxImage);
	}
}
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  プレイヤー処理のソースファイル
//!
//! @date   2016/11/28
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//ヘッダインクルード========================================
#include "Stage.h"
#include "StageBlock.h"
#include "Player.h"
#include "Box.h"
#include "Carrot.h"
#include "GameMain.h"

//グローバル変数の定義======================================

//関数の定義==============================================
//コンストラクタ
Player::Player()
	: m_player_posx(PLAYER_START_POSX)
	, m_player_posy(PLAYER_START_POSY)
	, m_player_grpx(PLAYER_GRPX)
	, m_player_grpy(PLAYER_GRPY)
	, m_player_width(PLAYER_WIDTH)
	, m_player_height(PLAYER_HEIGHT)
	, m_player_spdx(0.0f)
	, m_player_spdy(0.0f)
	, m_playermove_count(0)
	, m_playeratk_count(0)
	, m_player_vec(P_UP)
	, m_player_state(P_NORMAL)
	, m_player_blocknum_x(PLAYER_START_POSX / MAP_WIDTH_MAX)
	, m_player_blocknum_y(PLAYER_START_POSY / MAP_HEIGHT_MAX)
	, m_front_block_type (BRANK)
	, m_dig_count (INIT_DIG_COUNT)
	, m_anime_count (0)
{

}

//デストラクタ
Player::~Player()
{
	
}

//プレイヤーの移動
void Player::Player_Move()
{
	//方向キーでスピード変化
	if (g_key.Right && !(g_key.Left) && !(g_key.Up) && !(g_key.Down) 
		&& m_player_state == P_NORMAL)
	{
		m_player_vec = P_RIGHT;
		m_player_grpx = 64;
		if (Player_Check_Block(m_player_vec))
		{
			m_player_spdx = PLAYER_SPEED;
			m_player_state = P_MOVE;
		}
	}
	if (g_key.Left && !(g_key.Right) && !(g_key.Up) && !(g_key.Down) && 
		m_player_state == P_NORMAL)
	{
		m_player_vec = P_LEFT;
		m_player_grpx = 96;
		if (Player_Check_Block(m_player_vec))
		{
			m_player_spdx = -PLAYER_SPEED;
			m_player_state = P_MOVE;
		}
	}
	if (g_key.Down && !(g_key.Left) && !(g_key.Up) && !(g_key.Right) && 
		m_player_state == P_NORMAL)
	{
		m_player_vec = P_DOWN;
		m_player_grpx = 0;
		if (Player_Check_Block(m_player_vec))
		{
			m_player_spdy = PLAYER_SPEED;
			m_player_state = P_MOVE;
		}
	}
	if (g_key.Up && !(g_key.Left) && !(g_key.Right) && !(g_key.Down) && 
		m_player_state == P_NORMAL)
	{
		m_player_vec = P_UP;
		m_player_grpx = 32;
		if (Player_Check_Block(m_player_vec))
		{
			m_player_spdy = -PLAYER_SPEED;
			m_player_state = P_MOVE;
		}
	}

	//移動中にカウント
	if (m_player_state == P_MOVE)
	{
		m_playermove_count++;

		//座標変更
		m_player_posx += (int)m_player_spdx;
		m_player_posy += (int)m_player_spdy;
	}

	//1マス移動しきったらカウントを0に
	if (m_playermove_count >= CHIP_SIZE / (int)PLAYER_SPEED)
	{
		m_playermove_count = 0;

		//停止
		m_player_spdx = 0.0f;
		m_player_spdy = 0.0f;
		m_player_state = P_NORMAL;

		//いる場所を更新
		Check_BlockNum();
	}
}

//プレイヤーの攻撃
void Player::Attack()
{

	//プレイヤーのいるブロック更新
	Check_BlockNum();

	if (m_player_state == P_NORMAL && g_keyTracker->pressed.Z)
	{
		if (GetDigCount() > 0)
		{
			Check_FrontBlockType();
			switch (m_player_vec)
			{
			case P_UP:
				m_player_posy = m_player_posy - m_player_height / 2;
				break;
			case P_DOWN:
				m_player_posy = m_player_posy + m_player_height / 2;
				break;
			case P_LEFT:
				m_player_posx = m_player_posx - m_player_width / 2;
				break;
			case P_RIGHT:
				m_player_posx = m_player_posx + m_player_width / 2;
				break;
			}
			//前が壁ならダメージを与える
			if (m_front_block_type == SAND_BLOCK || m_front_block_type == HARD_BLOCK)
			{
				switch (m_player_vec)
				{
				case P_UP:
					g_block[m_player_blocknum_y - 1][m_player_blocknum_x].Damage();
					break;
				case P_DOWN:
					g_block[m_player_blocknum_y + 1][m_player_blocknum_x].Damage();
					break;
				case P_LEFT:
					g_block[m_player_blocknum_y][m_player_blocknum_x - 1].Damage();
					break;
				case P_RIGHT:
					g_block[m_player_blocknum_y][m_player_blocknum_x + 1].Damage();
					break;
				}
				ReduceDigCount();
			}
			m_player_state = P_ATTACK;
		}
	}

	//攻撃中にカウント
	if (m_player_state == P_ATTACK)
	{
		m_playeratk_count++;
	}

	//攻撃が終わったらカウントを0に
	if (m_playeratk_count >= PLAYER_ATK_COUNT)
	{
		m_playeratk_count = 0;

		//座標をもどす
		switch (m_player_vec)
		{
		case P_UP:
			m_player_posy = m_player_posy + m_player_height / 2;
			break;
		case P_DOWN:
			m_player_posy = m_player_posy - m_player_height / 2;
			break;
		case P_LEFT:
			m_player_posx = m_player_posx + m_player_width / 2;
			break;
		case P_RIGHT:
			m_player_posx = m_player_posx - m_player_width / 2;
			break;
		}

		//停止
		m_player_state = P_NORMAL;
	}
}

//プレイヤーの描画
void Player::Player_Draw()
{
	m_anime_count++;
	if (m_anime_count > 60)
	{
		m_anime_count = 0;
	}

	switch (m_player_state)
	{
	case P_NORMAL:
	case P_MOVE:
		if (m_anime_count < 30)
		{
			m_player_grpy = 0;
		}
		else
		{
			m_player_grpy = 32;
		}
		break;
	case P_ATTACK:
		m_player_grpy = 64;
		break;
	}

	//プレイヤー
	DrawRectTexture(m_player_posx, m_player_posy,
		m_player_grpx, m_player_grpy, m_player_width, m_player_height, g_grpMogura);

	//穴掘り回数
	DrawNum(600, 220, m_dig_count);
}

//プレイヤーの進む先が移動可能か判断,箱なら押す
bool Player::Player_Check_Block(int vec)
{
	//プレイヤーのいるブロックを判定
	Check_BlockNum();

	//調べたブロックの型
	int next_block_type;
	int block_num;

	//ブロックを調べる(前方2マス)
	Check_FrontBlockType();
	switch (vec)
	{
	case P_LEFT:
		next_block_type = g_block[m_player_blocknum_y][m_player_blocknum_x - 2].Get_StageBlockType();
		break;
	case P_RIGHT:
		next_block_type = g_block[m_player_blocknum_y][m_player_blocknum_x + 2].Get_StageBlockType();
		break;
	case P_UP:
		next_block_type = g_block[m_player_blocknum_y - 2][m_player_blocknum_x].Get_StageBlockType();
		break;
	case P_DOWN:
		next_block_type = g_block[m_player_blocknum_y + 2][m_player_blocknum_x].Get_StageBlockType();
		break;
	}

	//調べたブロックにより処理
	switch (m_front_block_type)
	{
	case BRANK:
		return true;
		break;
	case GOAL:
		return true;
		break;
	case BOX:
		switch (next_block_type)
		{
		case BOX:
		case SAND_BLOCK:
		case HARD_BLOCK:
		case SUPER_BLOCK:
			return false;
			break;
			//箱を押す
		default:
			//押している箱を調べる
			for (block_num = 0; block_num < BOX_MAX_NUM; block_num++)
			{
				if (vec == P_LEFT)
				{
					if (g_box[block_num].Box_Search(m_player_blocknum_x - 1, m_player_blocknum_y))
					{
						break;
					}
				}
				if (vec == P_RIGHT)
				{
					if (g_box[block_num].Box_Search(m_player_blocknum_x + 1, m_player_blocknum_y))
					{
						break;
					}
				}
				if (vec == P_UP)
				{
					if (g_box[block_num].Box_Search(m_player_blocknum_x, m_player_blocknum_y - 1))
					{
						break;
					}
				}
				if (vec == P_DOWN)
				{
					if (g_box[block_num].Box_Search(m_player_blocknum_x, m_player_blocknum_y + 1))
					{
						break;
					}
				}
			}
			//見つかったら移動準備
			if (block_num < BOX_MAX_NUM)
			{
				g_box[block_num].Box_Set_Move(vec);
			}
			return true;
			break;
		}
		break;
	case SAND_BLOCK:
	case HARD_BLOCK:
	case SUPER_BLOCK:
		return false;
		break;
	default:
		return false;
		break;
	}
}

//初期位置に設定
void Player::SetPos(int x, int y)
{
	m_player_posx = x;
	m_player_posy = y;
}

//プレイヤーの穴掘り回数を設定
void Player::SetDigCount(int num)
{
	m_dig_count = num;
}

//プレイヤーの穴掘り回数を取得
int Player::GetDigCount()
{
	return m_dig_count;
}

//プレイヤーの穴掘り回数を増やす
void Player::AddDigCount(int num)
{
	m_dig_count += num;
}

//プレイヤーの穴掘り回数を減らす
void Player::ReduceDigCount()
{
	if (m_dig_count > 0)
	{
		m_dig_count--;
	}
}

//プレイヤーのいるブロックの番号を登録
void Player::Check_BlockNum()
{
	m_player_blocknum_x = (m_player_posx + m_player_width / 2) / CHIP_SIZE;
	m_player_blocknum_y = (m_player_posy + m_player_height / 2) / CHIP_SIZE;
}

//プレイヤーの前のブロックの型を登録
void Player::Check_FrontBlockType()
{
	switch (m_player_vec)
	{
	case P_UP:
		m_front_block_type = g_block[m_player_blocknum_y - 1][m_player_blocknum_x].Get_StageBlockType();
		break;
	case P_DOWN:
		m_front_block_type = g_block[m_player_blocknum_y + 1][m_player_blocknum_x].Get_StageBlockType();
		break;
	case P_LEFT:
		m_front_block_type = g_block[m_player_blocknum_y][m_player_blocknum_x - 1].Get_StageBlockType();
		break;
	case P_RIGHT:
		m_front_block_type = g_block[m_player_blocknum_y][m_player_blocknum_x + 1].Get_StageBlockType();
		break;
	}
}

//プレイヤーのX座標を取得
int Player::GetPlayerX()
{
	return m_player_posx;
}

//プレイヤーのY座標を取得
int Player::GetPlayerY()
{
	return m_player_posy;
}
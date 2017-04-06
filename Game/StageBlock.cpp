//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   StageBlock.cpp
//!
//! @brief  ステージブロックのソースファイル
//!
//! @date   2016/11/11
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//ヘッダの読み込み
#include "StageBlock.h"
#include "Stage.h"
#include "Gamemain.h"

//グローバル変数の定義======================================

//関数の定義==============================================
//コンストラクタ
StageBlock::StageBlock()
{
	m_block_posx = 0;
	m_block_posy = 0;
	m_block_grpx = 0;
	m_block_grpy = 0;
	m_block_width = BLOCK_WIDTH;
	m_block_height = BLOCK_HEIGHT;
	m_block_state = TRUE;
	m_block_type = BRANK;
}

//デストラクタ
StageBlock::~StageBlock()
{
	/*delete m_player_handle;*/
}

//ブロックの設置
void StageBlock::StageBlock_Set(int i, int j)
{
	m_block_type = g_map[i][j];
	m_block_grpx = (m_block_type % 10) * CHIP_SIZE;
	m_block_grpy = (m_block_type / 10) * CHIP_SIZE;
	m_block_posx = CHIP_SIZE * j;
	m_block_posy = CHIP_SIZE * i;

	if (m_block_type == SAND_BLOCK)
	{
		m_block_durability = SAND_BLOCK_DUR;
	}
	else
	{
		m_block_durability = HARD_BLOCK_DUR;
	}
}

//ブロックの描画
void StageBlock::StageBlock_Draw()
{
	switch (m_block_type)
	{
	case BRANK:
	case BOX:
		break;
	default:
		DrawRectTexture(m_block_posx, m_block_posy,
			m_block_grpx, m_block_grpy, m_block_width, m_block_height, g_BlockImage);
		break;
	}
}

//ブロックの種類を取得
int StageBlock::Get_StageBlockType()
{
	return m_block_type;
}

//ブロックの種類を変更
void StageBlock::StageBlock_Type_Set(int type)
{
	m_block_type = type;
}

//ブロックの破壊
void StageBlock::Break()
{
	if (m_block_durability <= 0)
	{
		StageBlock_Type_Set(BRANK);
	}
}

//ブロックにダメージ
void StageBlock::Damage()
{
	m_block_durability--;
}

//耐久力
void StageBlock::SetDur(int dur)
{
	m_block_durability = dur;
}
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   StageBlock.cpp
//!
//! @brief  ステージブロックのヘッダファイル
//!
//! @date   2016/11/11
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

//定数の定義================================================
#define BLOCK_WIDTH (32)
#define BLOCK_HEIGHT (32)
#define SAND_BLOCK_DUR (1)
#define HARD_BLOCK_DUR (3)

//グローバル変数の定義======================================

//クラスの定義==============================================
class StageBlock
{
private:
	/*Texture* m_player_handle;*/
	int m_block_posx, m_block_posy;
	int m_block_width, m_block_height;
	int m_block_grpx, m_block_grpy;
	bool m_block_state;
	int m_block_type;
	int m_block_durability;

public:
	StageBlock();
	~StageBlock();
	void StageBlock_Set(int i, int j);		//ブロックの設置
	void StageBlock_Draw();					//ブロックの描画
	int Get_StageBlockType();				//ブロックのタイプを返す
	void StageBlock_Type_Set(int type);		//ブロックのタイプを変更
	void Break();
	void Damage();
	void SetDur(int dur);
};

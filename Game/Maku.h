//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Maku.h
//!
//! @brief  幕処理のヘッダファイル
//!
//! @date   2017/01/15
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//定数の定義================================================
#define MAKU_GRPX (640)
#define MAKU_GRPY (480)
#define MAKU_WIDTH (640)
#define MAKU_HEIGHT (480) 
#define MAKU_SPEED (8)
#define MAKU_TIME (60)

enum MAKU_TYPE
{
	NEXT,
	START,
	FINISH,
};

//クラスの定義==============================================
class Maku
{
private:
	int m_maku_posx, m_maku_posy;
	int m_maku_width, m_maku_height;
	int m_maku_grpx, m_maku_grpy;
	int m_maku_spdx, m_maku_spdy;
	int m_maku_state;
	int m_makumove_count;
	bool m_makumove_flag;

public:
	Maku();
	~Maku();
	void Maku_SetMove();
	void Maku_Move();
	void Maku_Draw();
	void Maku_Change(int);
	bool Maku_GetFlag();
};
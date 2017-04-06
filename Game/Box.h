//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Box.h
//!
//! @brief  箱処理のヘッダファイル
//!
//! @date   2016/11/28
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

//定数の定義================================================
#define BOX_GRPX (0)
#define BOX_GRPY (0)
#define BOX_WIDTH (32)
#define BOX_HEIGHT (32) 
#define BOX_SPEED (2.0f)
const int BOX_DIG_BONUS = 3;
const int BOX_TIME_BONUS = 15;
const int BOX_NUM = (6);

//クラスの定義==============================================
class Box
{
private:
	int m_box_posx, m_box_posy;
	int m_box_width, m_box_height;
	int m_box_grpx, m_box_grpy;
	float m_box_spdx, m_box_spdy;
	bool m_box_state;
	int m_boxmove_count;
	bool m_boxmove_flag;
	int m_box_blocknum_x, m_box_blocknum_y;
	bool m_box_goal_flag;
	
public:
	Box();
	~Box();
	void Box_Set(int box_num);
	void Box_Set_Move(int player_vec);
	void Box_Move();
	void Box_Draw();
	void Box_Reset();
	bool Box_Search(int x, int y);
};
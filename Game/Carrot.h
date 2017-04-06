//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Carrot.h
//!
//! @brief  にんじん処理のヘッダファイル
//!
//! @date   2016/11/28
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
class Player;

//定数の定義================================================
#define CARROT_GRPX (0)
#define CARROT_GRPY (0)
#define CARROT_WIDTH (32)
#define CARROT_HEIGHT (32) 


//クラスの定義==============================================
class Carrot
{
private:
	int m_carrot_posx, m_carrot_posy;
	int m_carrot_width, m_carrot_height;
	int m_carrot_grpx, m_carrot_grpy;
	bool m_carrot_state;

public:
	Carrot();
	~Carrot();
	void Carrot_Set();
	void Carrot_Collision_Player(Player*);
	void Carrot_Draw();

};
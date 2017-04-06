//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  �v���C���[�����̃w�b�_�t�@�C��
//!
//! @date   2016/11/07
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

//�N���X�̌Ăяo��
class Texture;

//�萔�̒�`================================================
#define PLAYER_WIDTH (32)
#define PLAYER_HEIGHT (32)
#define PLAYER_GRPX (32)
#define PLAYER_GRPY (0)
#define PLAYER_START_POSX (32 * 7)
#define PLAYER_START_POSY (32 * 13)
#define PLAYER_SPEED (2.0f)
#define PLAYER_SPEED (2.0f)
#define PLAYER_ATK_COUNT (30)
#define INIT_DIG_COUNT (30)

enum PLAYER_VEC
{
	P_UP,
	P_DOWN,
	P_LEFT,
	P_RIGHT,
};

enum PLAYER_STATE
{
	P_NORMAL,
	P_MOVE,
	P_ATTACK,
};

//�O���[�o���ϐ��̒�`======================================

//�N���X�̒�`==============================================
class Player
{
private:
	int m_player_posx, m_player_posy;
	int m_player_width, m_player_height;
	int m_player_grpx, m_player_grpy;
	float m_player_spdx, m_player_spdy;
	int m_player_vec;
	int m_player_state;
	int m_playermove_count;
	int m_playeratk_count;
	int m_player_blocknum_x, m_player_blocknum_y;
	int m_front_block_type;
	int m_dig_count;
	int m_anime_count;

public:
	Player();
	~Player();
	void Player_Move();
	void Player_Draw();
	void Attack();
	bool Player_Check_Block(int vec);	//�v���C���[�̐i�ރu���b�N���ړ��\������
	void SetPos(int x,int y);
	void SetDigCount(int num);
	int GetDigCount();
	void AddDigCount(int num);
	void ReduceDigCount();
	int GetPlayerX();
	int GetPlayerY();

private:
	void Check_BlockNum();
	void Check_FrontBlockType();
};

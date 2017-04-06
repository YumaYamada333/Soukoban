//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.cpp
//!
//! @brief  �v���C���[�����̃\�[�X�t�@�C��
//!
//! @date   2016/11/28
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//�w�b�_�C���N���[�h========================================
#include "Stage.h"
#include "StageBlock.h"
#include "Player.h"
#include "Box.h"
#include "Carrot.h"
#include "GameMain.h"

//�O���[�o���ϐ��̒�`======================================

//�֐��̒�`==============================================
//�R���X�g���N�^
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

//�f�X�g���N�^
Player::~Player()
{
	
}

//�v���C���[�̈ړ�
void Player::Player_Move()
{
	//�����L�[�ŃX�s�[�h�ω�
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

	//�ړ����ɃJ�E���g
	if (m_player_state == P_MOVE)
	{
		m_playermove_count++;

		//���W�ύX
		m_player_posx += (int)m_player_spdx;
		m_player_posy += (int)m_player_spdy;
	}

	//1�}�X�ړ�����������J�E���g��0��
	if (m_playermove_count >= CHIP_SIZE / (int)PLAYER_SPEED)
	{
		m_playermove_count = 0;

		//��~
		m_player_spdx = 0.0f;
		m_player_spdy = 0.0f;
		m_player_state = P_NORMAL;

		//����ꏊ���X�V
		Check_BlockNum();
	}
}

//�v���C���[�̍U��
void Player::Attack()
{

	//�v���C���[�̂���u���b�N�X�V
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
			//�O���ǂȂ�_���[�W��^����
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

	//�U�����ɃJ�E���g
	if (m_player_state == P_ATTACK)
	{
		m_playeratk_count++;
	}

	//�U�����I�������J�E���g��0��
	if (m_playeratk_count >= PLAYER_ATK_COUNT)
	{
		m_playeratk_count = 0;

		//���W�����ǂ�
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

		//��~
		m_player_state = P_NORMAL;
	}
}

//�v���C���[�̕`��
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

	//�v���C���[
	DrawRectTexture(m_player_posx, m_player_posy,
		m_player_grpx, m_player_grpy, m_player_width, m_player_height, g_grpMogura);

	//���@���
	DrawNum(600, 220, m_dig_count);
}

//�v���C���[�̐i�ސ悪�ړ��\�����f,���Ȃ牟��
bool Player::Player_Check_Block(int vec)
{
	//�v���C���[�̂���u���b�N�𔻒�
	Check_BlockNum();

	//���ׂ��u���b�N�̌^
	int next_block_type;
	int block_num;

	//�u���b�N�𒲂ׂ�(�O��2�}�X)
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

	//���ׂ��u���b�N�ɂ�菈��
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
			//��������
		default:
			//�����Ă��锠�𒲂ׂ�
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
			//����������ړ�����
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

//�����ʒu�ɐݒ�
void Player::SetPos(int x, int y)
{
	m_player_posx = x;
	m_player_posy = y;
}

//�v���C���[�̌��@��񐔂�ݒ�
void Player::SetDigCount(int num)
{
	m_dig_count = num;
}

//�v���C���[�̌��@��񐔂��擾
int Player::GetDigCount()
{
	return m_dig_count;
}

//�v���C���[�̌��@��񐔂𑝂₷
void Player::AddDigCount(int num)
{
	m_dig_count += num;
}

//�v���C���[�̌��@��񐔂����炷
void Player::ReduceDigCount()
{
	if (m_dig_count > 0)
	{
		m_dig_count--;
	}
}

//�v���C���[�̂���u���b�N�̔ԍ���o�^
void Player::Check_BlockNum()
{
	m_player_blocknum_x = (m_player_posx + m_player_width / 2) / CHIP_SIZE;
	m_player_blocknum_y = (m_player_posy + m_player_height / 2) / CHIP_SIZE;
}

//�v���C���[�̑O�̃u���b�N�̌^��o�^
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

//�v���C���[��X���W���擾
int Player::GetPlayerX()
{
	return m_player_posx;
}

//�v���C���[��Y���W���擾
int Player::GetPlayerY()
{
	return m_player_posy;
}
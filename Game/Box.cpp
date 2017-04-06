//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Box.cpp
//!
//! @brief  �������̃\�[�X�t�@�C��
//!
//! @date   2016/11/28
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

//�w�b�_�C���N���[�h========================================
#include "Box.h"
#include "Stage.h"
#include "StageBlock.h"
#include "Player.h"
#include "Gamemain.h"

//�֐��̒�`==============================================
//�R���X�g���N�^
Box::Box()
	:m_box_posx(-32)
	,m_box_posy (0)
	,m_box_grpx (BOX_GRPX)
	,m_box_grpy (BOX_GRPY)
	,m_box_width (BOX_WIDTH)
	,m_box_height (BOX_HEIGHT)
	,m_box_spdx (0.0f)
	,m_box_spdy (0.0f)
	,m_box_state (false)
	,m_boxmove_count (0)
	,m_boxmove_flag(false)
	,m_box_blocknum_x (0)
	,m_box_blocknum_y (0)
	,m_box_goal_flag (false)
{
}

//�f�X�g���N�^
Box::~Box()
{

}

//���̐ݒu
void Box::Box_Set(int box_num)
{
	//�{�b�N�X��u���ʒu�������_���擾(�[������)
	int y = (rand() % (MAP_HEIGHT_MAX - 5)) + 2;
	int x = (rand() % (MAP_WIDTH_MAX - 5)) + 2;

	//�}�b�v�`�b�v�ɂ���ĕύX
	if (g_block[y][x].Get_StageBlockType() != GOAL && g_block[y][x].Get_StageBlockType() != BOX)
	{
		m_box_posx = CHIP_SIZE * x;
		m_box_posy = CHIP_SIZE * y;
		m_box_state = true;

		g_block[y][x].StageBlock_Type_Set(BOX);
		g_block[y][x].SetDur(HARD_BLOCK_DUR);
	}
	else if (g_block[y][x].Get_StageBlockType() == BOX)
	{
		Box_Set(box_num);
	}
	else
	{
		m_box_state = false;
		m_box_posx = 0;
		m_box_posy = 0;
		m_box_goal_flag = true;
		g_block[y][x].StageBlock_Type_Set(BRANK);
	}
}

//���̑��x,�t���O�ݒ�A���̈ʒu�̈ړ�����
void Box::Box_Set_Move(int player_vec)
{
	m_box_blocknum_x = (m_box_posx + m_box_width / 2) / CHIP_SIZE;
	m_box_blocknum_y = (m_box_posy + m_box_height / 2) / CHIP_SIZE;

	if (m_box_state)
	{
		g_block[m_box_blocknum_y][m_box_blocknum_x].StageBlock_Type_Set(BRANK);

		m_boxmove_flag = true;

		switch (player_vec)
		{
		case P_UP:
			m_box_spdy = -BOX_SPEED;
			break;
		case P_DOWN:
			m_box_spdy = BOX_SPEED;
			break;
		case P_LEFT:
			m_box_spdx = -BOX_SPEED;
			break;
		case P_RIGHT:
			m_box_spdx = BOX_SPEED;
			break;
		}
	}
}

//���̈ړ�
void Box::Box_Move()
{
	if (m_box_state)
	{
		//�ړ����ɃJ�E���g
		if (m_boxmove_flag)
		{
			m_boxmove_count++;

			//���W�ύX
			m_box_posx += (int)m_box_spdx;
			m_box_posy += (int)m_box_spdy;
		}

		//1�}�X�ړ�����������J�E���g��0��
		if (m_boxmove_count >= CHIP_SIZE / (int)BOX_SPEED)
		{
			m_boxmove_count = 0;

			//���̍Đݒ�
			Box_Reset();

			//��~
			m_box_spdx = 0.0f;
			m_box_spdy = 0.0f;
			m_boxmove_flag = false;
		}
	}
}

//��������ꏊ���Đݒ�A�S�[���Ȃ�S�[������
void Box::Box_Reset()
{
	m_box_blocknum_x = (m_box_posx + m_box_width / 2) / CHIP_SIZE;
	m_box_blocknum_y = (m_box_posy + m_box_height / 2) / CHIP_SIZE;

	if (m_box_state)
	{
		if (g_block[m_box_blocknum_y][m_box_blocknum_x].Get_StageBlockType() != GOAL)
		{
			g_block[m_box_blocknum_y][m_box_blocknum_x].StageBlock_Type_Set(BOX);
			g_block[m_box_blocknum_y][m_box_blocknum_x].SetDur(HARD_BLOCK_DUR);
		}
		else
		{
			g_block[m_box_blocknum_y][m_box_blocknum_x].StageBlock_Type_Set(BRANK);
			m_box_state = false;
			m_box_posx = 0;
			m_box_posy = 0;
			m_box_goal_flag = true;
			//g_player.AddDigCount(BOX_DIG_BONUS);
			g_time += BOX_TIME_BONUS;
		}
	}
}

//���̕`��
void Box::Box_Draw()
{
	if (m_box_state)
	{
		DrawRectTexture(m_box_posx, m_box_posy,
			m_box_grpx, m_box_grpy, m_box_width, m_box_height, g_BoxImage);
	}
}

//���̒���
bool Box::Box_Search(int x, int y)
{
	m_box_blocknum_x = (m_box_posx + m_box_width / 2) / CHIP_SIZE;
	m_box_blocknum_y = (m_box_posy + m_box_height / 2) / CHIP_SIZE;

	if (m_box_blocknum_x == x && m_box_blocknum_y == y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
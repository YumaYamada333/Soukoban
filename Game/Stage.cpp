//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.cpp
//!
//! @brief  �X�e�[�W�����̃\�[�X�t�@�C��
//!
//! @date   2016/11/04
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//�w�b�_�̓ǂݍ���
#include "Stage.h"
#include "Box.h"
#include "Carrot.h"
#include "Player.h"
#include "StageBlock.h"
#include "Gamemain.h"

//�O���[�o���ϐ��̒�`=====================================================
Texture* g_blockimage;
StageBlock g_block[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
int g_map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
int g_map_w, g_map_h;
int g_stagenum;
int g_mapinit;
float g_startpos_x, g_startpos_y;
int g_miss, g_misscount;
int g_box_count = 0;
int g_goal_count = 0;
int g_hard_count = 0;
int g_box_num = 0;

//�v���g�^�C�v
void Goal_Set();

// �֐��̒�` ==============================================================

//------------------------------------------
// �X�e�[�W�̏�����
//------------------------------------------
void Stage_Initialize()
{
	int i, j;

	g_blockimage = new Texture(L"Resources\\Images\\PongImage.png");

	//�}�b�v�̏�����
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 20; j++)
		{
			g_map[i][j] = 0;
		}
	}

	//�}�b�v�̑傫��������
	g_map_w = g_map_h = 0;

	//�v���C���[�̃X�^�[�g�n�_������
	g_startpos_x = g_startpos_y = 0;

	g_mapinit = 0;
}

//------------------------------------------
// �X�e�[�W�̍X�V
//------------------------------------------
void Stage_Update()
{
	//�X�e�[�W�̃Z�b�g(�X�e�[�W���߂Ɉ��)
	if (g_mapinit == 0)
	{
		//�u���b�N�̃����_���z�u
		Rand_Set_Stage();

		//�S�[����z�u
		for (int i = 0; i < BOX_NUM; i++)
		{
			Goal_Set();
		}

		//�j���W����ݒu
		for (int i = 0; i < CARROT_NUM; i++)
		{
			g_carrot[i].Carrot_Set();
		}

		//�u���b�N��ݒu
		Block_Set();
		
		//����ݒu
		for (int i = 0; i < BOX_NUM; i++)
		{
			g_box[i].Box_Set(i);
		}
		g_mapinit = 1;
		g_clear_flag = false;
	}

	for (int i = 0; i < MAP_HEIGHT_MAX; i++)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; j++)
		{
			//�u���b�N�̔j�󔻒�
			g_block[i][j].Break();
		}
	}
}

//------------------------------------------
// �X�e�[�W�u���b�N�̕`��
//------------------------------------------
void Stage_Draw()
{
	int i, j;

	//�}�b�v�̕\��
	for (i = 0; i < MAP_HEIGHT_MAX; i++)
	{
		for (j = 0; j < MAP_WIDTH_MAX; j++)
		{
			switch (g_block[i][j].Get_StageBlockType())
			{
			case BRANK:  //brank
				break;
			default:
				g_block[i][j].StageBlock_Draw();
				break;
			}
		}
	}
}

//---------------------------------------
//�}�b�v�̃����_������
//---------------------------------------
void Rand_Set_Stage()
{
	g_hard_count = 0;

	//�}�b�v�f�[�^��ݒ�(�O�g�͕�)
	for (int i = 0; i < MAP_HEIGHT_MAX; i++)
	{
		for (int j = 0; j < MAP_WIDTH_MAX;j++)
		{
			if (i == 0 || i == 14 || j == 0 || j == 14)
			{
				g_map[i][j] = 3;
			}
			else if (i == 1 || i == 13 || j == 1 || j == 13)
			{
				g_map[i][j] = rand() % 2;
			}
			else
			{
				g_map[i][j] = rand() % 3;
			}
		}
	}

	g_map[PLAYER_START_POSY / 32][PLAYER_START_POSX / 32] = BRANK;
}

//------------------------------------------
// �u���b�N�̔z�u
//------------------------------------------
void Block_Set()
{
	int i, j;
	for (i = 0; i < MAP_HEIGHT_MAX; i++)
	{
		for (j = 0; j < MAP_WIDTH_MAX; j++)
		{
			g_block[i][j].StageBlock_Set(i,j);
		}
	}
}

//------------------------------------------
// �S�[���̔z�u
//------------------------------------------
void Goal_Set()
{
	int goal_x = rand() % (MAP_WIDTH_MAX - 2) + 1;
	int goal_y = rand() % (MAP_HEIGHT_MAX - 2) + 1;
	if (g_map[goal_y][goal_x] != GOAL)
	{
		g_map[goal_y][goal_x] = GOAL;
	}
	else
	{
		Goal_Set();
	}
}

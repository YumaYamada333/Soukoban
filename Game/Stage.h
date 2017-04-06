//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.cpp
//!
//! @brief  �X�e�[�W�����̃w�b�_�t�@�C��
//!
//! @date   2016/11/04
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once

// �萔�̒�`===============================================================
//�}�b�v�̑傫��(�`�b�v�̐�)
#define MAP_WIDTH_MAX (15)
#define MAP_HEIGHT_MAX (15)
//�e�u���b�N�̍ő吔
#define HARD_BLOCK_MAX_NUM (100)
//�u���b�N�^�C�v�̐�
#define BLOCK_TYPE_MAX (6)

enum StageNum
{
	STAGE1,
};

enum BLOCK_TYPE
{
	BRANK,
	SAND_BLOCK,
	HARD_BLOCK,
	SUPER_BLOCK,
	BOX,
	GOAL,
};

//�N���X�̌Ăяo��==========================================
class StageBlock;

//�O���[�o���ϐ��̒�`======================================
extern int g_map_w, g_map_h;
extern int g_map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern StageBlock g_block[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern int g_mapinit;
//extern int g_box_count;
//extern int g_goal_count;
//extern int g_hard_count;

//�֐��̐錾===============================================================
// �X�e�[�W�̏�����
void Stage_Initialize();

//�X�e�[�W�̍X�V
void Stage_Update();

//�}�b�v�̃����_������(�O�g����)
void Rand_Set_Stage();

// �u���b�N�̔z�u
void Block_Set();

// �X�e�[�W�u���b�N�̕`��
void Stage_Draw();
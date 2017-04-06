//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   StageBlock.cpp
//!
//! @brief  �X�e�[�W�u���b�N�̃w�b�_�t�@�C��
//!
//! @date   2016/11/11
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

//�萔�̒�`================================================
#define BLOCK_WIDTH (32)
#define BLOCK_HEIGHT (32)
#define SAND_BLOCK_DUR (1)
#define HARD_BLOCK_DUR (3)

//�O���[�o���ϐ��̒�`======================================

//�N���X�̒�`==============================================
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
	void StageBlock_Set(int i, int j);		//�u���b�N�̐ݒu
	void StageBlock_Draw();					//�u���b�N�̕`��
	int Get_StageBlockType();				//�u���b�N�̃^�C�v��Ԃ�
	void StageBlock_Type_Set(int type);		//�u���b�N�̃^�C�v��ύX
	void Break();
	void Damage();
	void SetDur(int dur);
};

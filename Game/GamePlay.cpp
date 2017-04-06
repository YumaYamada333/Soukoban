//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  �Q�[���v���C�����̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GamePlay.h"
#include "Stage.h"
#include "StageBlock.h"
#include "Box.h"
#include "Maku.h"
#include "Player.h"
#include "Carrot.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

//�O���[�o���ϐ��������������������������������������������������������������|
//Maku g_maku;
int g_count;

//�֐��̒�`�����������������������������������������������������������������|
//----------------------------------------------------------------------
//! @brief �v���C�R���X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Play::Play()
{

}

//----------------------------------------------------------------------
//! @brief �v���C�f�X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Play::~Play()
{

}

//----------------------------------------------------------------------
//! @brief �Q�[���v���C����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Play::Update()
{
	//�V�[���̍ŏ��Ɉ�񂾂��s������������
	if (g_init == 0)
	{
		g_init = 1;
		g_time = START_TIME;
		g_floor_num = 1;
		g_count = 0;

		Stage_Initialize();

		g_player.SetPos(PLAYER_START_POSX, PLAYER_START_POSY);
		g_player.SetDigCount(INIT_DIG_COUNT);

		ADX2Le::Play(CRI_CUESHEET_0__CUE_ID_0);
	}	//�V�[���̍ŏ��Ɉ�񂾂��s���������I��



	//���͌n����/////////////////////////// //
	// if(g_keyTracker->pressed.Space)//�g���K�[����
	// if(g_key.Right)//��������
	// ttp://directxtk.codeplex.com/wikipage?title=Keyboard�@���Q�l

	//�X�e�[�W�̍X�V
	Stage_Update();

	//���̏���
	for (int i = 0; i < BOX_MAX_NUM; i++)
	{
		g_box[i].Box_Move();
	}

	//�v���C���[�̏���
	g_player.Player_Move();
	g_player.Attack();

	//�j���W���̔���
	for (int i = 0; i < CARROT_NUM; i++)
	{
		g_carrot[i].Carrot_Collision_Player(&g_player);
	}

	//�^�C���̏���
	if (g_maku.Maku_GetFlag() == false)
	{
		int border = 60 - ((g_floor_num / 15)*10);
		if (border < 30)
		{
			border = 30;
		}

		g_count++;
		if (g_count > border)
		{
			g_time--;
			g_count = 0;
		}
		if (g_time < 0)
		{
			g_time = 0;
		}
	}

	//���^�C�A����
	if (g_keyTracker->pressed.Space)
	{
		g_time -= PENALTY_TIME;
		if (g_time > 0)
		{
			g_maku.Maku_Change(NEXT);
			g_player.SetDigCount(INIT_DIG_COUNT);
		}
		else
		{
			g_time = 0;
			g_maku.Maku_Change(FINISH);
		}

		g_maku.Maku_SetMove();
	}

	//�N���A����
	if (CheckClear())
	{
		if (g_clear_flag == false)
		{
			g_time += g_player.GetDigCount() * BONUS_SCALE;
			g_clear_flag = true;
		}
		g_maku.Maku_Change(NEXT);
		g_maku.Maku_SetMove();
		//g_NextScene = CLEAR;
	}

	//�I������
	if(g_time <= 0)
	{
		g_maku.Maku_Change(FINISH);
		g_maku.Maku_SetMove();
	}

	g_maku.Maku_Move();
}

//----------------------------------------------------------------------
//! @brief �Q�[���v���C�`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Play::Render()
{
	wchar_t buf[256];

	//�w�i
	DrawRectTexture(0, 0, 0, 0, 640, 480, g_grpBack);

	//�j���W��
	for (int i = 0; i < CARROT_NUM; i++)
	{
		g_carrot[i].Carrot_Draw();
	}

	//�u���b�N
	Stage_Draw();

	//��
	for (int i = 0; i < BOX_MAX_NUM; i++)
	{
		g_box[i].Box_Draw();
	}

	//�v���C��
	g_player.Player_Draw();

	//�^�C��
	DrawNum(600, 100, g_time);

	//�t���A
	DrawNum(600, 340, g_floor_num);

	/*swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));*/

	//��
	g_maku.Maku_Draw();

}

//----------------------------------------------------------------------
//! @brief �N���A����������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
bool Play::CheckClear()
{
	for (int i = 0; i < MAP_HEIGHT_MAX; i++)
	{
		for (int j = 0; j < MAP_WIDTH_MAX; j++)
		{
			if (g_block[i][j].Get_StageBlockType() == GOAL)
			{
				return false;
			}
		}
	}
	return true;
}
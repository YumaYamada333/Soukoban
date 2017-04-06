//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma comment(lib, "cri_ware_pcx86_LE_import.lib")

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#define _GAMEMAIN_
#include "Player.h"
#include "GameMain.h"
#include "GameBase.h"
#include "GamePlay.h"
#include "GameTitle.h"
#include "GameClear.h"
#include "GameOver.h"
#include "GameLogo.h"
#include "Stage.h"
#include "Box.h"
#include "Maku.h"
#include "Carrot.h"
#include <ctime>
using namespace DirectX::SimpleMath;
using namespace DirectX;

// �v���g�^�C�v�錾 ====================================================

// �O���[�o���ϐ��̒�` ====================================================
Player g_player;
Box g_box[BOX_MAX_NUM];
Carrot g_carrot[CARROT_NUM];
Maku g_maku;
Texture *g_BlockImage;
Texture *g_BoxImage;
Texture *g_grpBack;
Texture *g_grpMaku;
Texture *g_grpStartMaku;
Texture *g_grpFinishMaku;
Texture *g_grpResult;
Texture *g_grpMogura;
Texture *g_grpTitle;
Texture *g_grpResultNum;
GameBase* base;
int g_time;
int g_floor_num;
bool g_clear_flag;
int g_highscore;

// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	srand((unsigned int)time(nullptr));

	//�X�e�[�W�̏�����
	
	
	//�@�摜�̓ǂݍ��� 
	g_grpHandle = new Texture(L"Resources\\Images\\logo.png");
	g_PongImage = new Texture(L"Resources\\Images\\PongImage.png");
	g_grpBack = new Texture(L"Resources\\Images\\back.png");
	g_grpMaku = new Texture(L"Resources\\Images\\makukan.png");
	g_grpStartMaku = new Texture(L"Resources\\Images\\startmaku.png");
	g_grpFinishMaku = new Texture(L"Resources\\Images\\finishmaku.png");
	g_BlockImage = new Texture(L"Resources\\Images\\block.png");
	g_BoxImage = new Texture(L"Resources\\Images\\boximage.png");
	g_grpResult = new Texture(L"Resources\\Images\\result.png");
	g_grpMogura = new Texture(L"Resources\\Images\\mogura.png");
	g_grpTitle = new Texture(L"Resources\\Images\\title.png");
	g_grpResultNum = new Texture(L"Resources\\Images\\resultnum.png");

	//���̓ǂݍ���
	ADX2Le::Initialize("Resources\\Sounds\\demo.acf");
	ADX2Le::LoadAcb("Resources\\Sounds\\CueSheet_0.acb", "Resources\\Sounds\\CueSheet_0.awb");

	g_TimeCnt = 0;
	g_Time = 0;

	g_key_old = 0;

	base =new Logo();
	g_NextScene = g_scene;

	g_back_grpx = 0;

	g_time = START_TIME;
	g_floor_num = 1;
	g_clear_flag = false;
	g_highscore = 0;
}




//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//��
	ADX2Le::Update();

	//�V�[���Ǘ�
	if (g_NextScene != g_scene)
	{
		g_scene = g_NextScene;
		delete base;
		g_init = 0;


		//�V�[�����Ƃ̌Ăяo��
		switch (g_scene)
		{
		case LOGO:
			base = new Logo();
			break;

		case TITLE:
			base = new Title();
			break;

		case PLAY:
			base = new Play();
			break;

		case CLEAR:
			base = new Clear();
			break;

		case OVER:
			base = new Over();
			break;
		}
	}

	g_key_old = g_key_code;
	base->Update();
}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{

	base->Render();
	
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	ADX2Le::Finalize();
	delete base;
	delete g_grpHandle;
	delete g_PongImage;
	delete g_grpBack;
	delete g_grpMaku;
	delete g_BlockImage;
	delete g_BoxImage;
	delete g_grpResult;
	delete g_grpMogura;
	delete g_grpTitle;
	delete g_grpResultNum;
}


//----------------------------------------------------------------------
//! @brief ���l�`�揈��
//!
//! @param[in] xy���W�C���lw
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawNum(int x, int y, int n)
{
	int w = n;		//�v�Z�p
	int i = 0;		//������

	if (w == 0)
	{
		DrawRectTexture(x, y, 0, 48, 25, 32, g_PongImage);
		//DrawRectGraph(x, y, 0, 48, 25, 32, g_PongImage, TRUE, FALSE);
	}
	else
	{
		while (w)
		{
			DrawRectTexture(x - i * 25, y, (w % 10) * 25, 48, 25, 32, g_PongImage);
			/*DrawRectGraph(x - i * 25, y,
				(w % 10) * 25, 48, 25, 32, g_PongImage, TRUE, FALSE);*/
			w = w / 10;
			i++;
		}
	}

}

//----------------------------------------------------------------------
//! @brief ���l�`�揈��(�傫��)
//!
//! @param[in] xy���W�C���lw
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawResultNum(int x, int y, int n)
{
	//DrawNum(470, 138, 0, 0, 62, 99, g_resultnumimage, g_score);
	int w = n;  //��Ɨp
	int i = 0;  //������
	if (w == 0)
	{
		DrawRectTexture(x, y, 0 + (w % 10) * 62, 0 + (w % 10 / 5 * 99), 62, 99, g_grpResultNum);
	}

	while (w)
	{
		if (w % 10 < 5)
		{
			DrawRectTexture(x - i * 62, y, 
				0 + (w % 10) * 62, 0 + (w % 10 / 5 * 99), 
				62, 99, g_grpResultNum);
		}
		else if (w % 10 >= 5)
		{
			DrawRectTexture(x - i * 62, y, 
				0 + (w % 10) % 5 * 62, 0 + (w % 10 / 5 * 99), 
				62, 99, g_grpResultNum);
		}
		w = w / 10;
		i++;
	}

}

//----------------------------------------------------------------------
//! @brief �e�N�X�`���̕`��
//!
//! @param[in] xy���W�C�摜�̎n�_xy, �摜�̑傫��wh, �e�N�X�`��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle)
{
	//rect = { leftupX, leftupY, rightdownX, rightdownY };
	RECT rect = { tex_x, tex_y, tex_x + tex_w, tex_y + tex_h };

	//Draw(�e�N�X�`��, �ꏊ , �傫��, �F����, ��](���W�A��), ��]����Ƃ��̒��S���W , �g��{��)
	g_spriteBatch->Draw(handle->m_pTexture, Vector2((float)pos_x, (float)pos_y), &rect, 
							Colors::White, 0.0f, Vector2(0.0f, 0.0f), Vector2(1.0f, 1.0f));
}

//----------------------------------------------------------------------
//! @brief �����_���Ő������o��(int)
//!
//! @param[in]�@�ő�l + 1
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
int GetRand(int num)
{
	return rand() % num;
}






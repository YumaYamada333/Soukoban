//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.cpp
//!
//! @brief  �Q�[���N���A�����̃\�[�X�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "GameClear.h"
#include "Maku.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

int posy;
int R_count;

//----------------------------------------------------------------------
//! @brief �Q�[���N���A�R���X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Clear::Clear()
{

}

//----------------------------------------------------------------------
//! @brief �Q�[���N���A�f�X�g���N�^
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
Clear::~Clear()
{
}

//----------------------------------------------------------------------
//! @brief �Q�[���N���A����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Clear::Update()
{
	if (g_init == 0)
	{
		g_init = 1;
		R_count = 0;
		posy = 226;
		g_TimeCnt = 0;
		if (g_floor_num > g_highscore)
		{
			g_highscore = g_floor_num;
		}
		//PlaySoundMem(g_se, DX_PLAYTYPE_BACK);
	}


	if (g_keyTracker->pressed.Z)
	{
		g_maku.Maku_Change(START);
		g_maku.Maku_SetMove(); 
		//g_NextScene = TITLE;
	}

	g_maku.Maku_Move();
}

//----------------------------------------------------------------------
//! @brief �Q�[���N���A�`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void Clear::Render()
{
	wchar_t buf[256];
	R_count++;
	if (R_count > 90)
	{
		R_count = 0;
	}

	if (R_count < 30)
	{
		posy -= 1.0f;
	}
	else if (R_count >= 30 && R_count < 60)
	{
		posy += 1.0f;
	}


	DrawRectTexture(0, 0, 0, 0, 640, 480, g_grpResult);
	DrawRectTexture(430, posy, 0, 64, 32, 32, g_grpMogura);

	//�X�R�A
	DrawResultNum(340, 160, g_floor_num);

	//�n�C�X�R�A
	DrawResultNum(380, 280, g_highscore);

	//DrawFormatString(100, 0, g_RGB, "CLEAR");
	/*swprintf_s(buf, 256, L"CLEAR");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));*/

	g_maku.Maku_Draw();
}

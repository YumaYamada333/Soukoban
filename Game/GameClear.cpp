//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameClear.cpp
//!
//! @brief  ゲームクリア処理のソースファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真	
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameClear.h"
#include "Maku.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

int posy;
int R_count;

//----------------------------------------------------------------------
//! @brief ゲームクリアコンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Clear::Clear()
{

}

//----------------------------------------------------------------------
//! @brief ゲームクリアデストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Clear::~Clear()
{
}

//----------------------------------------------------------------------
//! @brief ゲームクリア処理
//!
//! @param[in] なし
//!
//! @return なし
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
//! @brief ゲームクリア描画処理
//!
//! @param[in] なし
//!
//! @return なし
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

	//スコア
	DrawResultNum(340, 160, g_floor_num);

	//ハイスコア
	DrawResultNum(380, 280, g_highscore);

	//DrawFormatString(100, 0, g_RGB, "CLEAR");
	/*swprintf_s(buf, 256, L"CLEAR");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));*/

	g_maku.Maku_Draw();
}

//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameTitle.cpp
//!
//! @brief  タイトル処理のソースファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "GameTitle.h"
#include "Maku.h"
using namespace DirectX::SimpleMath;
using namespace DirectX;

int grpx;
int grpy;
int posx;
int count;

//----------------------------------------------------------------------
//! @brief コンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Title::Title()
{

}

//----------------------------------------------------------------------
//! @brief デストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Title::~Title()
{

}

//----------------------------------------------------------------------
//! @brief タイトル処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Title::Update()
{
	if (g_init == 0)
	{
		g_init = 1;
		grpx = 0;
		grpy = 0;
		posx = 256;
		count = 0;
		g_maku.Maku_Change(START);
		//PlaySoundMem(g_se, DX_PLAYTYPE_BACK);
	}

	if (g_keyTracker->pressed.Z)
	{
		/*g_NextScene = PLAY;*/
		g_maku.Maku_SetMove();
	}

	g_maku.Maku_Move();
}

//----------------------------------------------------------------------
//! @brief タイトル描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Title::Render()
{
	wchar_t buf[256];
	count++;
	if (count >= 240)
	{
		count = 0;
	}

	if ((count / 30) % 2 == 0)
	{
		grpy = 0;
	}
	else
	{
		grpy = 32;
	}

	if (count < 120)
	{
		grpx = 64;
		posx += 1;
	}
	else
	{
		grpx = 96;
		posx -= 1;
	}

	DrawRectTexture(0, 0, 0, 0, 640, 480, g_grpTitle);
	DrawRectTexture(posx, 340, grpx, grpy, 32, 32, g_grpMogura);
	//DrawFormatString(100, 0, g_RGB, "TITLE");
	/*swprintf_s(buf, 256, L"TITLE");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));*/

	g_maku.Maku_Draw();

}
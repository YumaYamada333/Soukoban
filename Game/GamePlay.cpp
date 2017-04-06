//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.cpp
//!
//! @brief  ゲームプレイ処理のソースファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
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

//グローバル変数＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－
//Maku g_maku;
int g_count;

//関数の定義＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝－
//----------------------------------------------------------------------
//! @brief プレイコンストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::Play()
{

}

//----------------------------------------------------------------------
//! @brief プレイデストラクタ
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
Play::~Play()
{

}

//----------------------------------------------------------------------
//! @brief ゲームプレイ処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::Update()
{
	//シーンの最初に一回だけ行う初期化処理
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
	}	//シーンの最初に一回だけ行う初期化終了



	//入力系処理/////////////////////////// //
	// if(g_keyTracker->pressed.Space)//トリガー処理
	// if(g_key.Right)//おしっぱ
	// ttp://directxtk.codeplex.com/wikipage?title=Keyboard　を参考

	//ステージの更新
	Stage_Update();

	//箱の処理
	for (int i = 0; i < BOX_MAX_NUM; i++)
	{
		g_box[i].Box_Move();
	}

	//プレイヤーの処理
	g_player.Player_Move();
	g_player.Attack();

	//ニンジンの判定
	for (int i = 0; i < CARROT_NUM; i++)
	{
		g_carrot[i].Carrot_Collision_Player(&g_player);
	}

	//タイムの処理
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

	//リタイア判定
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

	//クリア判定
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

	//終了判定
	if(g_time <= 0)
	{
		g_maku.Maku_Change(FINISH);
		g_maku.Maku_SetMove();
	}

	g_maku.Maku_Move();
}

//----------------------------------------------------------------------
//! @brief ゲームプレイ描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void Play::Render()
{
	wchar_t buf[256];

	//背景
	DrawRectTexture(0, 0, 0, 0, 640, 480, g_grpBack);

	//ニンジン
	for (int i = 0; i < CARROT_NUM; i++)
	{
		g_carrot[i].Carrot_Draw();
	}

	//ブロック
	Stage_Draw();

	//箱
	for (int i = 0; i < BOX_MAX_NUM; i++)
	{
		g_box[i].Box_Draw();
	}

	//プレイヤ
	g_player.Player_Draw();

	//タイム
	DrawNum(600, 100, g_time);

	//フロア
	DrawNum(600, 340, g_floor_num);

	/*swprintf_s(buf, 256, L"PLAY");
	g_spriteFont->DrawString(g_spriteBatch.get(), buf, Vector2(100, 0));*/

	//幕
	g_maku.Maku_Draw();

}

//----------------------------------------------------------------------
//! @brief クリアしたか判定
//!
//! @param[in] なし
//!
//! @return なし
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
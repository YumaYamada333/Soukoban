//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   2016/11/04		
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once

#ifndef _GAMEMAIN_
#define EXTERN extern
#else
#define EXTERN
#endif

#include<windows.h>
#include<d3d11.h>
#include<SimpleMath.h>
#include"..\DirectXTK.h"
#include"..\Texture.h"
#include"..\ADX2Le.h"
#include"CueSheet_0.h"


class Player;
class Box;
class Maku;
class Carrot;

// 定数の定義 ==============================================================

// ゲームタイトル
#define GAME_TITLE "thousand"

// ゲーム画面
#define SCREEN_WIDTH  640    // 幅[pixel]
#define SCREEN_HEIGHT 480    // 高さ[pixel]
//１チップの大きさ
#define CHIP_SIZE (32)
//箱の最大数
#define BOX_MAX_NUM (6)
//ニンジンの数
const int CARROT_NUM = (5);
//初期タイム
const int START_TIME = 200;
//ボーナス倍率
const int BONUS_SCALE = 1;

//　構造体宣言
typedef struct tag_object
{
	Texture *handle;	//グラフィックハンドル 
	int grp_x;		//元画像のｘ座標 
	int grp_y;		//元画像のｙ座標 
	int grp_w;		//元画像の幅 
	int grp_h;		//元画像の高さ 
	float pos_x;	//座標x 
	float pos_y;	//座標y 
	float spd_x;	//速度x 
	float spd_y;	//速度y 
	int state;		//状態
}Object;			//オブジェクト用

//　列挙型宣言
enum SCENE
{
	LOGO,
	TITLE,
	PLAY,
	CLEAR,
	OVER
};

// グローバル変数の定義 ====================================================
//EXTERN HGRP g_grpHandle;		//　グラフィック
//EXTERN HGRP g_PongImage;		//　ポン画像

//EXTERN COLOR g_RGB;				//　文字色

//EXTERN HSND g_se;				//　効果音

EXTERN Texture *g_grpHandle;
EXTERN Texture *g_PongImage;


//EXTERN Object g_player;			//　プレイヤ

/*EXTERN Player g_player;	*/		//　プレイヤ
extern Player g_player;
extern Box g_box[BOX_MAX_NUM];
extern Carrot g_carrot[CARROT_NUM];
extern Maku g_maku;
extern Texture *g_BlockImage;
extern Texture *g_grpBack;
extern Texture *g_BoxImage;
extern Texture *g_grpMaku;
extern Texture *g_grpStartMaku;
extern Texture *g_grpFinishMaku;
extern Texture *g_grpResult;
extern Texture *g_grpMogura;
extern Texture *g_grpTitle;
extern Texture *g_grpResultNum;
extern int g_time;
extern int g_floor_num;
extern bool g_clear_flag;
extern int g_highscore;

EXTERN int g_key_code;			//キー情報
EXTERN int g_key_old;			//前フレームのキー情報

EXTERN int g_scene;				//シーン管理
EXTERN int g_NextScene;			//次のシーン
EXTERN int g_init;				//初期化管理

EXTERN int g_TimeCnt;			//時間カウンタ
EXTERN int g_Time;				//秒数

EXTERN int g_back_grpx;

EXTERN wchar_t buf[256];


// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);

//　数値描画処理
void DrawNum(int x, int y, int n);
void DrawResultNum(int x, int y, int n);


//テクスチャの描画
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle);

//ランダムゲット
int GetRand(int num);

//　各シーンの処理
//void GameLogo(void);
//void GameTitle(void);
//void GamePlay(void);
//void GameClear(void);
//void GameOver(void);
//
////　各シーンの描画処理
//void RenderLogo(void);
//void RenderTitle(void);
//void RenderPlay(void);
//void RenderClear(void);
//void RenderOver(void);




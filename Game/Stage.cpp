//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.cpp
//!
//! @brief  ステージ処理のソースファイル
//!
//! @date   2016/11/04
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//ヘッダの読み込み
#include "Stage.h"
#include "Box.h"
#include "Carrot.h"
#include "Player.h"
#include "StageBlock.h"
#include "Gamemain.h"

//グローバル変数の定義=====================================================
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

//プロトタイプ
void Goal_Set();

// 関数の定義 ==============================================================

//------------------------------------------
// ステージの初期化
//------------------------------------------
void Stage_Initialize()
{
	int i, j;

	g_blockimage = new Texture(L"Resources\\Images\\PongImage.png");

	//マップの初期化
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 20; j++)
		{
			g_map[i][j] = 0;
		}
	}

	//マップの大きさ初期化
	g_map_w = g_map_h = 0;

	//プレイヤーのスタート地点初期化
	g_startpos_x = g_startpos_y = 0;

	g_mapinit = 0;
}

//------------------------------------------
// ステージの更新
//------------------------------------------
void Stage_Update()
{
	//ステージのセット(ステージ初めに一回)
	if (g_mapinit == 0)
	{
		//ブロックのランダム配置
		Rand_Set_Stage();

		//ゴールを配置
		for (int i = 0; i < BOX_NUM; i++)
		{
			Goal_Set();
		}

		//ニンジンを設置
		for (int i = 0; i < CARROT_NUM; i++)
		{
			g_carrot[i].Carrot_Set();
		}

		//ブロックを設置
		Block_Set();
		
		//箱を設置
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
			//ブロックの破壊判定
			g_block[i][j].Break();
		}
	}
}

//------------------------------------------
// ステージブロックの描画
//------------------------------------------
void Stage_Draw()
{
	int i, j;

	//マップの表示
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
//マップのランダム生成
//---------------------------------------
void Rand_Set_Stage()
{
	g_hard_count = 0;

	//マップデータを設定(外枠は壁)
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
// ブロックの配置
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
// ゴールの配置
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

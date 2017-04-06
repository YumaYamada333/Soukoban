//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Stage.cpp
//!
//! @brief  ステージ処理のヘッダファイル
//!
//! @date   2016/11/04
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
// 多重インクルードの防止 ==================================================
#pragma once

// 定数の定義===============================================================
//マップの大きさ(チップの数)
#define MAP_WIDTH_MAX (15)
#define MAP_HEIGHT_MAX (15)
//各ブロックの最大数
#define HARD_BLOCK_MAX_NUM (100)
//ブロックタイプの数
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

//クラスの呼び出し==========================================
class StageBlock;

//グローバル変数の定義======================================
extern int g_map_w, g_map_h;
extern int g_map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern StageBlock g_block[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
extern int g_mapinit;
//extern int g_box_count;
//extern int g_goal_count;
//extern int g_hard_count;

//関数の宣言===============================================================
// ステージの初期化
void Stage_Initialize();

//ステージの更新
void Stage_Update();

//マップのランダム生成(外枠除く)
void Rand_Set_Stage();

// ブロックの配置
void Block_Set();

// ステージブロックの描画
void Stage_Draw();
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  プレイシーンのヘッダファイル
//!
//! @date   2016/12/12
//!
//! @author 山田唯真
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"

//定数
const int PENALTY_TIME = 60;

//クラス
class Play:public GameBase
{
private:

public:
	Play();
	~Play();
	void Update();
	void Render();
private:
	//プロトタイプ宣言
	bool CheckClear();
};

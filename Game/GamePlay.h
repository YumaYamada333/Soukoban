//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GamePlay.h
//!
//! @brief  �v���C�V�[���̃w�b�_�t�@�C��
//!
//! @date   2016/12/12
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once
#include "GameBase.h"

//�萔
const int PENALTY_TIME = 60;

//�N���X
class Play:public GameBase
{
private:

public:
	Play();
	~Play();
	void Update();
	void Render();
private:
	//�v���g�^�C�v�錾
	bool CheckClear();
};

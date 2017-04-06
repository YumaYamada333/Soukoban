//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameBase.h
//!
//! @brief  �Q�[���̊�{�̃w�b�_�t�@�C��
//!
//! @date   2016/12/16
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
#pragma once

class GameBase
{
public:
	virtual ~GameBase() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
};

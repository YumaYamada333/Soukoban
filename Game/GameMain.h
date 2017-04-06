//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   2016/11/04		
//!
//! @author �R�c�B�^
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
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

// �萔�̒�` ==============================================================

// �Q�[���^�C�g��
#define GAME_TITLE "thousand"

// �Q�[�����
#define SCREEN_WIDTH  640    // ��[pixel]
#define SCREEN_HEIGHT 480    // ����[pixel]
//�P�`�b�v�̑傫��
#define CHIP_SIZE (32)
//���̍ő吔
#define BOX_MAX_NUM (6)
//�j���W���̐�
const int CARROT_NUM = (5);
//�����^�C��
const int START_TIME = 200;
//�{�[�i�X�{��
const int BONUS_SCALE = 1;

//�@�\���̐錾
typedef struct tag_object
{
	Texture *handle;	//�O���t�B�b�N�n���h�� 
	int grp_x;		//���摜�̂����W 
	int grp_y;		//���摜�̂����W 
	int grp_w;		//���摜�̕� 
	int grp_h;		//���摜�̍��� 
	float pos_x;	//���Wx 
	float pos_y;	//���Wy 
	float spd_x;	//���xx 
	float spd_y;	//���xy 
	int state;		//���
}Object;			//�I�u�W�F�N�g�p

//�@�񋓌^�錾
enum SCENE
{
	LOGO,
	TITLE,
	PLAY,
	CLEAR,
	OVER
};

// �O���[�o���ϐ��̒�` ====================================================
//EXTERN HGRP g_grpHandle;		//�@�O���t�B�b�N
//EXTERN HGRP g_PongImage;		//�@�|���摜

//EXTERN COLOR g_RGB;				//�@�����F

//EXTERN HSND g_se;				//�@���ʉ�

EXTERN Texture *g_grpHandle;
EXTERN Texture *g_PongImage;


//EXTERN Object g_player;			//�@�v���C��

/*EXTERN Player g_player;	*/		//�@�v���C��
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

EXTERN int g_key_code;			//�L�[���
EXTERN int g_key_old;			//�O�t���[���̃L�[���

EXTERN int g_scene;				//�V�[���Ǘ�
EXTERN int g_NextScene;			//���̃V�[��
EXTERN int g_init;				//�������Ǘ�

EXTERN int g_TimeCnt;			//���ԃJ�E���^
EXTERN int g_Time;				//�b��

EXTERN int g_back_grpx;

EXTERN wchar_t buf[256];


// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);

//�@���l�`�揈��
void DrawNum(int x, int y, int n);
void DrawResultNum(int x, int y, int n);


//�e�N�X�`���̕`��
void DrawRectTexture(int pos_x, int pos_y, int tex_x, int tex_y, int tex_w, int tex_h, Texture* handle);

//�����_���Q�b�g
int GetRand(int num);

//�@�e�V�[���̏���
//void GameLogo(void);
//void GameTitle(void);
//void GamePlay(void);
//void GameClear(void);
//void GameOver(void);
//
////�@�e�V�[���̕`�揈��
//void RenderLogo(void);
//void RenderTitle(void);
//void RenderPlay(void);
//void RenderClear(void);
//void RenderOver(void);




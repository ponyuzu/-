/******************************************************************************
* �^�C�g��  :
* �t�@�C����:main.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/23
*******************************************************************************
* �X�V����:-2015/10/23 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _MAIN_H_
#define _MAIN_H_

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include <windows.h>
#include "d3dx9.h"		//�`��ɕK�v
#define DIRECTINPUT_VERSION (0x0800)//�x���Ώ�
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "model.h"
#include "dinput.h"//���͏����ɕK�v
#include "input.h"
#include "meshwall.h"
#include "shadow.h"
#include "explosion.h"
#include "box.h"
#include "tree.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "common.h"
#include "obstacl.h"
#include "acorn.h"
#include "enemy.h"
#include "result.h"
#include "selsect.h"
#include "stage.h"
#include "acorncnt.h"
#include "lifecnt.h"
#include "fade.h"
#include "sky.h"
#include "effect.h"
#include "selectarrow.h"
#include "goal.h"
#include "resultlogo.h"
#include "pause.h"

/*****************************************************************************
*���C�u�����̃����N
******************************************************************************/
#pragma comment(lib , "d3d9.lib")		//�`�揈���ɕK�v
#pragma comment(lib , "d3dx9.lib")	//��L�̊g�����C�u����
#pragma comment(lib , "dxguid.lib")	//directX�R���|�[�l���g�g�p�ɕK�v
#pragma comment(lib , "winmm.lib")	//�V�X�e�������l���ɕK�v
#pragma comment(lib , "dinput8.lib")	//���͏����ɕK�v

#pragma warning ( disable : 4996 )

/******************************************************************************
* �}�N����`
******************************************************************************/
#define SCREEN_WIDTH (1280.0f)		//��ʂ̉���
#define SCREEN_HEIGHT (720.0f)	//��ʂ̏c��
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )//���W�E�J���[�E�e�N�X�`��
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//���W�E�@���E�J���[�E�e�N�X�`��
#define TYOUTEN (4)				//���_�̐�

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 pos;
	float rwh;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_3D;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
LPDIRECT3DDEVICE9 GetDevice( void );
void SetMode( MODE mode );


/*���d�C���N���[�h�h�~*/
#endif
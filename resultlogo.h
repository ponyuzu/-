/******************************************************************************
* �^�C�g��  :
* �t�@�C����:select.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/02/01
*******************************************************************************
* �X�V����:-2016/02/01 �n糗M��
*           -v0.01 
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _RESULTLOGO_H_
#define _RESULTLOGO_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
#define RESULTLOGO_MAX (4)//�I�u�W�F�N�g�̐�

#define RESULTLOGO1_WIDTH (600)//���肠�̕�
#define RESULTLOGO1_HEIDHT (200)

#define RESULTLOGO2_WIDTH (700)//�˂����Ƃ̕�
#define RESULTLOGO2_HEIDHT (100)

#define RESULTLOGO3_WIDTH (700)//���[�ނ��[�΁[�̕�
#define RESULTLOGO3_HEIDHT (100)

#define RESULTLOGO4_WIDTH (700)//�܂��̕�
#define RESULTLOGO4_HEIDHT (100)

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffResultLogo;//���_�o�b�t�@

	D3DXVECTOR3 posResultLogo;		//�|���S���̒��S�_
	float widthResultLogo;			//�|���S�����S�_����̉���
	float heightResultLogo;			//�|���S�����S�_����̏c��

	bool LogoUse;		//�`�悷�邩�ǂ���

}RESULTLOGO;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitResultLogo( void );
void UninitResultLogo( void );
void UpdateResultLogo( void );
void DrawResultLogo( void );

#endif
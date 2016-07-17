/******************************************************************************
* �^�C�g��  :
* �t�@�C����:effect.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/02/01
*******************************************************************************
* �X�V����:-2016/02/01 �n糗M��
*           -v0.01 
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _EFFECT_H_
#define _EFFECT_H_

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �}�N����`
******************************************************************************/
#define EFFECT_MAX (100)		//�G�t�F�N�g�̐�
#define EFFECT_NUM_VTX (4)	//���_��
#define EFFECT_ALPHA (-0.01)	//���l�̕ύX

#define EFFECT_ACORN_WIDTH (20)		//�ǂ񂮂�G�t�F�N�g�̉���
#define EFFECT_ACORN_HEIGHT (20)	//�ǂ񂮂�G�t�F�N�g�̏c��

#define EFFECT_IN_WIDHT (70)	//�����G�t�F�N�g�̉���
#define EFFECT_IN_HEIGHT (70)	//�����G�t�F�N�g�̏c��

#define EFFECT_1UP_WIDHT (70)	//�P�t�o�G�t�F�N�g�̉���
#define EFFECT_1UP_HEIGHT (70)	//1UP�G�t�F�N�g�̏c��

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	EFFECT_NONE = 0,
	EFFECT_ACORN,
	EFFECT_IN,
	EFFECT_1UP

}EFFECTPATTARN;

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffEffect;//���_�o�b�t�@

	D3DXVECTOR3 posEffect;		//�ʒu���
	D3DXVECTOR3 rotEffect;		//��]���
	D3DXVECTOR3 sclEffect;		//�{�����

	float effectWidht;		//�G�t�F�N�g����
	float effectHeight;		//�G�t�F�N�g�c��

	float effectR;			//R
	float effectG;			//G
	float effectB;			//B
	float effectAlpha;		//���l

	bool effectUse;//�G�t�F�N�g�������Ă��邩�ǂ���

	EFFECTPATTARN effectPttrn;//�G�t�F�N�g�̎��

}EFFECT;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitEffect( void );
void UninitEffect( void );
void UpdateEffect( void );
void DrawEffect( void );
void SetEffect( D3DXVECTOR3 pos , EFFECTPATTARN pattarn );

#endif
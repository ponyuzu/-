/******************************************************************************
* �^�C�g��  :
* �t�@�C����:acorncnt.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _ACORNCNT_H_
#define _ACORNCNT_H_

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �}�N����`
******************************************************************************/
#define ACORNCNT_MAX (4)
#define ACORN_TEX_MAX (3)

#define ACORNCNT_WIDTH  (30.0)		//�|���S������
#define ACORNCNT_HEIGHT (50.0)		//�|���S���c��
#define ACORN_TEX_WIDTH (40.0)		//�e�N�X�`�����m�̉���

#define ACORN_TEX_HEIGHT (40.0)		//�ǂ񂮂�|���S���c��
#define ACORN_TEX_WIDTH  (40.0)		//�|���S������

#define ACORN_KAKERU_HEIGHT (20.0)		//������|���S���c��

#define ACORNCNT_PATTERN_WIDTH (1.0f / 10 )		//�P�t���[���̉���

#define ACORNCNT_DOWN_SPEED (30)		//�\�����鎞�̃X�s�[�h
#define ACORNCNT_UP_SPEED (-1)		//���܂����̃X�s�[�h
#define ACORNCNT_INDICATE_TIME (200)	//�\�����Ă�������
#define ACORNCNT_POSY (40.0f)		//�\���x���W

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	ACORN_NONE = 0,
	ACORN_DOWN,
	ACORN_IND,
	ACORN_UP

}ACORNIND;

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posAcornCnt;		//�|���S���̒��S�_
	float widthAcornCnt;			//�|���S�����S�_����̉���
	float heightAcornCnt;			//�|���S�����S�_����̏c��
	float posTexXAcornCnt;			//�e�N�X�`���̃|�W�V����

	ACORNIND acornInd;
	int cntIndTime;

}ACORNCNT;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitAcornCnt( void );
void UninitAcornCnt( void );
void UpdateAcornCnt( void );
void DrawAcornCnt( void );
ACORNCNT *GetAcornCnt( void );
void AddAcornCnt( int value );

#endif
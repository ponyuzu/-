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
#ifndef _LIFECNT_H_
#define _LIFECNT_H_

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �}�N����`
******************************************************************************/
#define LIFECNT_MAX (4)
#define LIFECNT_TEX_MAX (3)

#define LIFECNT_WIDTH  (40.0)		//�|���S������
#define LIFECNT_HEIGHT (60.0)		//�|���S���c��
#define LIFECNT_TEX_WIDTH (50.0)	//�|���S�����m�̋���

#define LIFECNT_TEX_HEIGHT (40.0)		//���ʂ��|���S���c��
#define LIFECNT_TEX_WIDTH  (40.0)		//���ʂ��|���S������

#define LIFECNT_KAKERU_HEIGHT (20.0)		//������|���S���c��

#define LIFECNT_PATTERN_WIDTH (1.0f / 10 )		//�P�t���[���̉���

#define LIFECNT_DOWN_SPEED (30)		//�\�����鎞�̃X�s�[�h
#define LIFECNT_UP_SPEED (-1)		//���܂����̃X�s�[�h
#define LIFECNT_INDICATE_TIME (200)	//�\�����Ă�������
#define LIFECNT_POSY (40.0f)		//�\���x���W

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	LIFE_NONE = 0,
	LIFE_DOWN,
	LIFE_IND,
	LIFE_UP

}LIFEIND;

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posLifeCnt;		//�|���S���̒��S�_
	float widthLifeCnt;			//�|���S�����S�_����̉���
	float heightLifeCnt;			//�|���S�����S�_����̏c��
	float posTexXLifeCnt;			//�e�N�X�`���̃|�W�V����

	LIFEIND lifeInd;
	int cntIndTime;

}LIFECNT;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitLifeCnt( void );
void UninitLifeCnt( void );
void UpdateLifeCnt( void );
void DrawLifeCnt( void );
LIFECNT *GetLifeCnt( void );
void AddLifeCnt( int value );

#endif
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:goal.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/27
*******************************************************************************
* �X�V����:-2015/10/27 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _GOAL_H_
#define _GOAL_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
//#define FIELD_USE_TEX ( true )//�e�N�X�`���̗L��
#define GOAL_SPEED (0.05f)//��]�X�s�[�h
#define GOAL_RADIUS (50)//���a

#define GOAL_MAX (3)//�G�l�~�[�̐�

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posGoal;
	D3DXVECTOR3 rotGoal;
	D3DXVECTOR3 sclGoal;

	bool useGoal;//goal���g���Ă邩�ǂ���

}GOAL;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
void InitGoal( void );
void UninitGoal( void );
void UpdateGoal( void );
void DrawGoal( void );
void SetGoal( D3DXVECTOR3 pos );
GOAL *GetGoal( void );


/*���d�C���N���[�h�h�~*/
#endif
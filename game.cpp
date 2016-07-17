/******************************************************************************
* �^�C�g��  :
* �t�@�C����:game.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "game.h"

/******************************************************************************
* �֐����FInitGame
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void InitGame( void )
{
	CAMERA *pCamera = GetCamera();

	//�J�����ʒu(�Q�[�������ʒu)
	pCamera -> posV = D3DXVECTOR3( 100 , 220 , -310 );//�ʒu
	pCamera -> posR = D3DXVECTOR3( 0 , 50 , -100 );//�����_

	InitWall();
	InitTree();
	InitField();
	InitObstacl();
	InitBox();
	InitEnemy();
	InitGoal();
	InitShadow();
	//InitEffect();
	InitModel();
	InitAcorn();
	InitStage();
	InitPause();

	SetStage();
}

/******************************************************************************
* �֐����FIninitGame
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitGame( void )
{
	UninitWall();
	UninitTree();
	UninitField();
	UninitObstacl();
	UninitModel();
	UninitAcorn();
	UninitEnemy();
	UninitGoal();
	UninitBox();
	UninitShadow();
	UninitPause();
	//UninitEffect();
}

/******************************************************************************
* �֐����FUpdateGame
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateGame( void )
{
	bool pPause = GetPause();

	//�o����������|�[�Y�J�nor����
	if( GetKeyboardTrigger( DIK_P ) )
	{
		if( pPause == false )
		{
			InitPause();//�������Ăяo��
			SetPause( true );
		}
		else
		{
			SetPause( false );
		}
	}

	if( !pPause )
	{
		UpdateWall();
		UpdateTree();
		UpdateField();
		UpdateObstacl();
		UpdateAcorn();
		UpdateEnemy();
		UpdateGoal();
		UpdateBox();
		//UpdateEffect();
		UpdateShadow();
		UpdateLifeCnt();
		UpdateModel();
		UpdateAcornCnt();
	}
	else
	{
		UpdatePause();
	}
}

/******************************************************************************
* �֐����FDrawGame
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawGame( void )
{
	//DrawWall();
	DrawTree();
	DrawField();
	DrawObstacl();
	DrawModel();
	DrawAcorn();
	DrawEnemy();
	DrawGoal();
	DrawBox();
	DrawShadow();
	DrawAcornCnt();
	DrawLifeCnt();
	DrawPause();
	//DrawEffect();
}
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:model.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/27
*******************************************************************************
* �X�V����:-2015/10/27 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPD3DXBUFFER g_pBuffMatModel = NULL;		//�}�e���A���̏��
LPDIRECT3DTEXTURE9 g_pTextureModel = NULL;
LPD3DXMESH g_pMeshModel;		//���b�V�����
DWORD g_numMatModel;			//�}�e���A���̐�
D3DXMATRIX g_mtxWorldModel;
MODEL g_Model;

int a=0;
bool b = false;

/******************************************************************************
* �֐����FInitModel
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f������������
******************************************************************************/
void InitModel( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXLoadMeshFromX( "data/MODEL/tanuki.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatModel,
						NULL,
						&g_numMatModel,
						&g_pMeshModel );

	g_Model.posModel   = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
	g_Model.rotModel   = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Model.sclModel   = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	g_Model.moveModel  = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Model.useJump    = false;
	g_Model.useGravity = false;
	g_Model.hitModel   = false;
	g_Model.useMove    = true;
	g_Model.death      = false;

	//�e���Z�b�g///////////////////////////////////////////////////////////////////////
	SetShadow( g_Model.posModel , SHADOW_PLAYER );

}

/******************************************************************************
* �֐����FUninitModel
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���I������
******************************************************************************/
void UninitModel( void )
{
	if( g_pMeshModel != NULL )
	{
		g_pMeshModel -> Release();
		g_pMeshModel = NULL;
	}

	if( g_pBuffMatModel !=NULL )
	{
		g_pBuffMatModel -> Release();
		g_pBuffMatModel = NULL;
	}
}

/******************************************************************************
* �֐����FUpdateModel
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F
******************************************************************************/
void UpdateModel( void )
{
	CAMERA *pCamera = GetCamera();
	SHADOW *pShadow = GetShadow();
	FIELD *pField = GetField();
	GOAL *pGoal = GetGoal();

	D3DXVECTOR3 posOld = g_Model.posModel;
	D3DXVECTOR3 dffrncRot;//�p�x�̍���

	bool OldDeath = g_Model.death;

	//���f���̈ړ�/////////////////////////////////////////////////////////////

	if( g_Model.useMove )
	{
		if( GetKeyboardPress( DIK_A ) )
		{
			if( GetKeyboardPress( DIK_W ) )
			{
				//�����Ɉړ�
				g_Model.moveModel.x += sinf( pCamera -> rot.y + D3DX_PI * -0.25f ) * MODEL_MOVE_SPEED;
				g_Model.moveModel.z += cosf( pCamera -> rot.y + D3DX_PI * -0.25f ) * MODEL_MOVE_SPEED;

				g_Model.goalRotModel.x = D3DX_PI * 0.75f + pCamera -> rot.y;//�������ړ������Ɍ�����
			}
			else if( GetKeyboardPress( DIK_S ))
			{
				//�����Ɉړ�
				g_Model.moveModel.x += sinf( pCamera -> rot.y + D3DX_PI * -0.75f ) * MODEL_MOVE_SPEED;
				g_Model.moveModel.z += cosf( pCamera -> rot.y + D3DX_PI * -0.75f ) * MODEL_MOVE_SPEED;

				g_Model.goalRotModel.x = D3DX_PI * 0.25f + pCamera -> rot.y;//�������ړ������Ɍ�����
				dffrncRot.x = g_Model.goalRotModel.x - g_Model.rotModel.x;//�����̌v�Z
			}
			else
			{
				//���Ɉړ�
				g_Model.moveModel.x += sinf( pCamera -> rot.y + D3DX_PI * -0.5f) * MODEL_MOVE_SPEED;
				g_Model.moveModel.z += cosf( pCamera -> rot.y + D3DX_PI * -0.5f) * MODEL_MOVE_SPEED;

				g_Model.goalRotModel.x = D3DX_PI * 0.5f + pCamera -> rot.y;//�������ړ������Ɍ�����
			}
			
		}

		else if( GetKeyboardPress( DIK_D ) )
		{
			if( GetKeyboardPress( DIK_W ) )
			{
				//�E���Ɉړ�
				g_Model.moveModel.x += sinf( pCamera -> rot.y + D3DX_PI * 0.25f ) * MODEL_MOVE_SPEED;
				g_Model.moveModel.z += cosf( pCamera -> rot.y + D3DX_PI * 0.25f ) * MODEL_MOVE_SPEED;

				g_Model.goalRotModel.x = D3DX_PI * -0.75f + pCamera -> rot.y;//�������ړ������Ɍ�����
			
			}
			else if( GetKeyboardPress( DIK_S ) )
			{
				//�E���Ɉړ�
				g_Model.moveModel.x += sinf( pCamera -> rot.y + D3DX_PI * 0.75f ) * MODEL_MOVE_SPEED;
				g_Model.moveModel.z += cosf( pCamera -> rot.y + D3DX_PI * 0.75f ) * MODEL_MOVE_SPEED;

				g_Model.goalRotModel.x = D3DX_PI * -0.25f + pCamera -> rot.y;//�������ړ������Ɍ�����
			}
			else
			{
				//�E�Ɉړ�
				g_Model.moveModel.x += sinf( pCamera -> rot.y + D3DX_PI * 0.5f ) * MODEL_MOVE_SPEED;
				g_Model.moveModel.z += cosf( pCamera -> rot.y + D3DX_PI * 0.5f ) * MODEL_MOVE_SPEED;

				g_Model.goalRotModel.x = D3DX_PI * -0.5f + pCamera -> rot.y;//�������ړ������Ɍ�����
			}
		}

		else if( GetKeyboardPress( DIK_W ) )
		{
			//���Ɉړ�
			g_Model.moveModel.x += sinf( pCamera -> rot.y ) * MODEL_MOVE_SPEED;
			g_Model.moveModel.z += cosf( pCamera -> rot.y ) * MODEL_MOVE_SPEED;

			g_Model.goalRotModel.x = D3DX_PI + pCamera -> rot.y;//�������ړ������Ɍ�����
		}

		else if( GetKeyboardPress( DIK_S ) )
		{
			//��O�Ɉړ�
			g_Model.moveModel.x -= sinf( pCamera -> rot.y ) * MODEL_MOVE_SPEED;
			g_Model.moveModel.z -= cosf( pCamera -> rot.y ) * MODEL_MOVE_SPEED;

			g_Model.goalRotModel.x = 0 + pCamera -> rot.y;//�������ړ������Ɍ�����
		}

		//�W�����v����/////////////////////////////////////////////////////////////////////
		if( GetKeyboardPress( DIK_SPACE ) )
		{
			if( g_Model.useJump == false )
			{
				g_Model.moveModel.y = JUMP_MOVE;
				g_Model.useJump = true;
				g_Model.useGravity = true;
			}
		}
	}



	//��]//////////////////////////////////////////////////////////////////////////

	//�����̌v�Z
	dffrncRot.x = g_Model.goalRotModel.x - g_Model.rotModel.x;

	//�����̕␳
	if( dffrncRot.x > D3DX_PI )
	{
		dffrncRot.x -= D3DX_PI * 2.0f;
	}
	else if( dffrncRot.x < -D3DX_PI )
	{
		dffrncRot.x += D3DX_PI * 2.0f;
	}

	//�ڕW�̕␳
	if( g_Model.goalRotModel.x > D3DX_PI )
	{
		g_Model.goalRotModel.x -= D3DX_PI * 2.0f;
	}
	else if( dffrncRot.x < -D3DX_PI )
	{
		g_Model.goalRotModel.x += D3DX_PI * 2.0f;
	}

	//���ݒn�̕␳
	if( g_Model.rotModel.x > D3DX_PI )
	{
		g_Model.rotModel.x -= D3DX_PI * 2.0f;
	}
	else if( g_Model.rotModel.x < -D3DX_PI )
	{
		g_Model.rotModel.x += D3DX_PI * 2.0f;
	}

	//�d�͌v�Z
	if( g_Model.useGravity == false )
	{
		g_Model.useJump = false;
		g_Model.moveModel.y = 0.0f;
	}
	else
	{
		g_Model.moveModel.y -= JUMP_GRAVITY;
		g_Model.useJump = true;
	}

	//�U��/////////////////////////////////////////////////////////////////////////
	/*if( GetKeyboardPress( DIK_B ) )
	{
			g_Model.rotModel.x++;
	}*/

	//�e���X�V///////////////////////////////////////////////////////////////////////
	pShadow ->posShadow.y = 0.5f;

	//���W�̑��///////////////////////////////////////////////////////////////////////
	g_Model.rotModel.x += dffrncRot.x * 0.25f;
	g_Model.posModel += g_Model.moveModel;
	g_Model.moveModel.x = ( 0.0 + g_Model.moveModel.x ) * 0.25f;
	g_Model.moveModel.z = ( 0.0 + g_Model.moveModel.z ) * 0.25f;


	//�����蔻��///////////////////////////////////////////////////////////////////////
	g_Model.useGravity = true;

	ACORN *pAcorn = GetAcorn();

	//box
	HitBoxModel();

	//obstacl
	HitObstaclModel();

	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		//��
		if( pField ->posField.z - FIELD_HEIGTH  * FIELD_Z / 2 < g_Model.posModel.z + g_Model.moveModel.z + 8 &&
			pField -> posField.z + FIELD_HEIGTH * FIELD_Z/ 2 > g_Model.posModel.z + g_Model.moveModel.z - 8 &&
			pField -> posField.x + FIELD_WIDHT  * FIELD_X/ 2 > g_Model.posModel.x + g_Model.moveModel.x - 8 &&
			pField -> posField.x - FIELD_WIDHT  * FIELD_X/ 2 < g_Model.posModel.x + g_Model.moveModel.x + 8 &&
 			pField -> posField.y > g_Model.posModel.y + g_Model.moveModel.y + 3  )
		{
			g_Model.useGravity = false;
		}
		pField++;
	}

	//��
	if( g_Model.posModel.x > 180 || g_Model.posModel.x < -180 || g_Model.posModel.z < -100)
	{
		g_Model.posModel.x = posOld.x;
		g_Model.posModel.z = posOld.z;
	}

	//acorn
	for( int cntAcorn = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		if( pAcorn ->acornUse == true )
		{
			if( ( pAcorn ->posAcorn.x - g_Model.posModel.x ) * ( pAcorn ->posAcorn.x - g_Model.posModel.x ) + 
				( pAcorn ->posAcorn.y - g_Model.posModel.y ) * ( pAcorn ->posAcorn.y - g_Model.posModel.y ) +
				( pAcorn ->posAcorn.z - g_Model.posModel.z ) * ( pAcorn ->posAcorn.z - g_Model.posModel.z ) <
				( ACORN_RADIUS        + MODEL_RADIUS       ) * ( ACORN_RADIUS        + MODEL_RADIUS       ) )
			{
				pAcorn ->acornUse = false;
				AddAcornCnt(1);//�ǂ񂮂�̐����f
			}
		}
		pAcorn++;
	}

	//goal/////////////////////////////////////////////////////////////////////
	if( pGoal ->useGoal == true )
	{
		if( ( pGoal ->posGoal.x - g_Model.posModel.x ) * ( pGoal ->posGoal.x - g_Model.posModel.x ) + 
			( pGoal ->posGoal.y - g_Model.posModel.y ) * ( pGoal ->posGoal.y - g_Model.posModel.y ) +
			( pGoal ->posGoal.z - g_Model.posModel.z ) * ( pGoal ->posGoal.z - g_Model.posModel.z ) <
			( GOAL_RADIUS        + MODEL_RADIUS       ) * ( GOAL_RADIUS        + MODEL_RADIUS       ) )
		{
			SetResultMode( RESULT_CREAL );
			SetFade( FADE_OUT , MODE_RESULT );
		}
	}


	//���S///////////////////////////////////////////////////////////////////////
	FADE *pFade = GetFade();

	//����
	if( g_Model.posModel.y < -20 )
	{
		g_Model.useMove = false;
	}

	//enemy
	HitEnemyModel();

	//�ʒu���Z�b�g
	if( g_Model.posModel.y < - 500 )
	{
		g_Model.death = true;
	}

	//���C�t���
	if( g_Model.death == true && OldDeath == false )
	{
		AddLifeCnt(-1);
	}
}


/******************************************************************************
* �֐����FDrawModel
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���̕`��
******************************************************************************/
void DrawModel( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	D3DXMatrixIdentity( &g_mtxWorldModel );

	D3DXMatrixScaling( &mtxScl , g_Model.sclModel.x , g_Model.sclModel.y , g_Model.sclModel.z );
	
	//�X�P�[���𔽉f
	D3DXMatrixMultiply( &g_mtxWorldModel , &g_mtxWorldModel , &mtxScl );

	D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Model.rotModel.x , g_Model.rotModel.y , g_Model.rotModel.z );

	//��]�̔��f
	D3DXMatrixMultiply( &g_mtxWorldModel , &g_mtxWorldModel , &mtxRot );

	D3DXMatrixTranslation( &mtxTrans , g_Model.posModel.x , g_Model.posModel.y , g_Model.posModel.z );

	//�ړ��̔��f
	D3DXMatrixMultiply( &g_mtxWorldModel , &g_mtxWorldModel , &mtxTrans );

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldModel );

	pDevice ->GetMaterial( &matDef );

	pMat = ( D3DXMATERIAL* )g_pBuffMatModel -> GetBufferPointer();
	for( int nCntMat = 0 ; nCntMat < (int) g_numMatModel ; nCntMat++ )
	{
		pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
		pDevice -> SetTexture( 0 , g_pTextureModel );
		g_pMeshModel ->DrawSubset( nCntMat );
	}

	//�}�e���A�������ɖ߂�
	pDevice -> SetMaterial( &matDef );
}

/******************************************************************************
* �֐����FGetModel
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
MODEL *GetModel( void )
{
	return &g_Model;
}

/******************************************************************************
* �֐����FHitBoxModel
* 
* ����  �F
* �߂�l�F
* ����  �F���Ƃ̓����蔻��
******************************************************************************/
void HitBoxModel( void )
{
	BOX *pBox = GetBox();

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		if( pBox -> boxUse == true )
		{
			//��ɏ��
			if( pBox -> setPosBox.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 4 &&
				pBox -> setPosBox.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 4 &&
				pBox -> setPosBox.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 4 &&
				pBox -> setPosBox.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 4 &&
				pBox -> setPosBox.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 3 &&
				pBox -> setPosBox.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 4  )
			{

				switch( pBox -> boxPattarn )
				{
				case BOX_NOMAL://�m�[�}�����������
					{
						g_Model.moveModel.y = JUMP_MOVE;
						g_Model.useJump = true;
						g_Model.useGravity = true;
						pBox -> boxUse = false;

						break;
					}
				case BOX_SPRING://�o�l�Ȃ�W�����v
					{
						g_Model.moveModel.y = JUMP_MOVE;
						g_Model.useJump = true;
						g_Model.useGravity = true;
						//pBox -> boxSpringHit = true;
						break;
					}
				}
			}

				//���ɓ�����
				if( pBox -> setPosBox.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 8 &&
					pBox -> setPosBox.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 8 &&
					pBox -> setPosBox.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 8 &&
					pBox -> setPosBox.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 8 &&
					pBox -> setPosBox.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 35 &&
					pBox -> setPosBox.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y +36  )
				{
					g_Model.moveModel.y = -g_Model.moveModel.y;
				}

				//���ʂɂԂ���
				//�E
				if( pBox -> setPosBox.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
					pBox -> setPosBox.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
					pBox -> setPosBox.x - BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 1 &&
					pBox -> setPosBox.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
					pBox -> setPosBox.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
					pBox -> setPosBox.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
				{
					g_Model.posModel.x = pBox -> setPosBox.x - BOX_WIDTH  / 2-15;
				}

				//��
				if( pBox -> setPosBox.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
					pBox -> setPosBox.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
					pBox -> setPosBox.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
					pBox -> setPosBox.x + BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 1 &&
					pBox -> setPosBox.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
					pBox -> setPosBox.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
				{
					g_Model.posModel.x = pBox -> setPosBox.x + BOX_WIDTH  / 2 + 15;
				}

				//��
				if( pBox -> setPosBox.z + BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 1 &&
					pBox -> setPosBox.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
					pBox -> setPosBox.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
					pBox -> setPosBox.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
					pBox -> setPosBox.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
					pBox -> setPosBox.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
				{
					g_Model.posModel.z = pBox -> setPosBox.z + BOX_HEIGHT / 2 + 15;
				}

				//��O
				if( pBox -> setPosBox.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
					pBox -> setPosBox.z - BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 1 &&
					pBox -> setPosBox.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
					pBox -> setPosBox.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
					pBox -> setPosBox.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
					pBox -> setPosBox.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
				{
					g_Model.posModel.z = pBox -> setPosBox.z - BOX_HEIGHT / 2 - 15;
				}
		}
		pBox += 6;
	}
}

/******************************************************************************
* �֐����FHitObstaclModel
* 
* ����  �F
* �߂�l�F
* ����  �F���Ƃ̓����蔻��
******************************************************************************/
void HitObstaclModel( void )
{
	OBSTACL *pObstacl = GetObstacl();

	for( int cntObs = 0 ; cntObs < OBSTACL_MAX ; cntObs++ )
	{
		if( pObstacl -> obstaclUse == true )
		{
			//��ɏ��
			if( pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 4 &&
				pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 4 &&
				pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 4 &&
				pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 4 &&
				pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 3 &&
				pObstacl -> setPosObstacl.y - OBSTACL_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 4  )
			{
				//�e�X�V
				//pShadow ->posShadow.y = pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 + 0.5f;

				g_Model.useGravity = false;
			}

			//���ɓ�����
			if( pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 8 &&
				pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 8 &&
				pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 8 &&
				pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 8 &&
				pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 35 &&
				pObstacl -> setPosObstacl.y - OBSTACL_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y +36  )
			{
				g_Model.moveModel.y = -g_Model.moveModel.y;
			}

			//���ʂɂԂ���
			//�E
			if( pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
				pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
				pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 1 &&
				pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
				pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pObstacl -> setPosObstacl.y - OBSTACL_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.posModel.x = pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2-15;
			}

			//��
			if( pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
				pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
				pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
				pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 1 &&
				pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pObstacl -> setPosObstacl.y - OBSTACL_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.posModel.x = pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 + 15;
			}

			//��
			if( pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 1 &&
				pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
				pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
				pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
				pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pObstacl -> setPosObstacl.y - OBSTACL_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.posModel.z = pObstacl -> setPosObstacl.z + OBSTACL_HEIGHT / 2 + 15;
			}

			//��O
			if( pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
				pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 1 &&
				pObstacl -> setPosObstacl.x + OBSTACL_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
				pObstacl -> setPosObstacl.x - OBSTACL_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
				pObstacl -> setPosObstacl.y + OBSTACL_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pObstacl -> setPosObstacl.y - OBSTACL_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.posModel.z = pObstacl -> setPosObstacl.z - OBSTACL_HEIGHT / 2 - 15;
			}
		}

		pObstacl += 6;
	}
}

/******************************************************************************
* �֐����FHitEnemyModel
* 
* ����  �F
* �߂�l�F
* ����  �F���Ƃ̓����蔻��
******************************************************************************/
void HitEnemyModel( void )
{
	ENEMY *pEnemy = GetEnemy();

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( pEnemy ->useEnemy == true )
		{
			//��ɏ��
			if( pEnemy -> posEnemy.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 8 &&
				pEnemy -> posEnemy.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 8 &&
				pEnemy -> posEnemy.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 8 &&
				pEnemy -> posEnemy.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 8 &&
				pEnemy -> posEnemy.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 3 &&
				pEnemy -> posEnemy.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 4  )
			{
			}

			//���ʂɂԂ���
			//�E
			if( pEnemy -> posEnemy.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
				pEnemy -> posEnemy.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
				pEnemy -> posEnemy.x - BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 1 &&
				pEnemy -> posEnemy.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
				pEnemy -> posEnemy.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pEnemy -> posEnemy.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.death = true;
				g_Model.useMove = false;
			}

			//��
			if( pEnemy -> posEnemy.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
				pEnemy -> posEnemy.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
				pEnemy -> posEnemy.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
				pEnemy -> posEnemy.x + BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 1 &&
				pEnemy -> posEnemy.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pEnemy -> posEnemy.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.death = true;
				g_Model.useMove = false;
			}

			//��
			if( pEnemy -> posEnemy.z + BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 1 &&
				pEnemy -> posEnemy.z + BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 15 &&
				pEnemy -> posEnemy.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
				pEnemy -> posEnemy.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
				pEnemy -> posEnemy.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pEnemy -> posEnemy.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.death = true;
				g_Model.useMove = false;
			}

			//��O
			if( pEnemy -> posEnemy.z - BOX_HEIGHT / 2 < g_Model.posModel.z + g_Model.moveModel.z + 15 &&
				pEnemy -> posEnemy.z - BOX_HEIGHT / 2 > g_Model.posModel.z + g_Model.moveModel.z - 1 &&
				pEnemy -> posEnemy.x + BOX_WIDTH  / 2 > g_Model.posModel.x + g_Model.moveModel.x - 15 &&
				pEnemy -> posEnemy.x - BOX_WIDTH  / 2 < g_Model.posModel.x + g_Model.moveModel.x + 15 &&
				pEnemy -> posEnemy.y + BOX_HEIGHT / 2 > g_Model.posModel.y + g_Model.moveModel.y + 4 &&
				pEnemy -> posEnemy.y - BOX_HEIGHT / 2 < g_Model.posModel.y + g_Model.moveModel.y + 38  )
			{
				g_Model.death = true;
				g_Model.useMove = false;
			}
		}
		pEnemy++;
	}
}
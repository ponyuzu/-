/******************************************************************************
* �^�C�g��  :
* �t�@�C����:goal.cpp
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
LPD3DXBUFFER g_pBuffMatGoal;//�}�e���A���̏��
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;
LPD3DXMESH g_pMeshGoal;		//���b�V�����
DWORD g_numMatGoal;			//�}�e���A���̐�
D3DXMATRIX g_mtxWorldGoal;
GOAL g_Goal[GOAL_MAX];

float g_rotY;

/******************************************************************************
* �֐����FInitGoal
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f������������
******************************************************************************/
void InitGoal( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	D3DXLoadMeshFromX( "data/MODEL/candy.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatGoal,
						NULL,
						&g_numMatGoal,
						&g_pMeshGoal );

	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		g_Goal[cntGoal].posGoal = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
		g_Goal[cntGoal].rotGoal = D3DXVECTOR3( 0.0f , 0.0f , 0.6f );
		g_Goal[cntGoal].sclGoal = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Goal[cntGoal].useGoal = false;
	}
	g_rotY =0.0f;
}

/******************************************************************************
* �֐����FUninitGoal
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���I������
******************************************************************************/
void UninitGoal( void )
{
	if( g_pMeshGoal != NULL )
	{
		g_pMeshGoal -> Release();
		g_pMeshGoal = NULL;
	}

	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		if( g_pBuffMatGoal !=NULL )
		{
			g_pBuffMatGoal -> Release();
			g_pBuffMatGoal = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateGoal
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F
******************************************************************************/
void UpdateGoal( void )
{
	//��]������
	g_Goal[0].rotGoal.x -= GOAL_SPEED;
	//������
	if( g_Goal[0].rotGoal.x > D3DX_PI * 2 )
	{
		g_Goal[0].rotGoal.x = 0;
	}

	//�ӂ�ӂ킳����
	g_rotY += GOAL_SPEED;
	//������
	g_Goal[0].posGoal.y += sinf( g_rotY ) / 2;
	if( g_rotY > D3DX_PI * 2 )
	{
		g_rotY = 0.0f;
	}
}


/******************************************************************************
* �֐����FDrawGoal
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���̕`��
******************************************************************************/
void DrawGoal( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		if( g_Goal[cntGoal].useGoal == true)
		{
				//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_mtxWorldGoal );

			D3DXMatrixScaling( &mtxScl , g_Goal[cntGoal].sclGoal.x , g_Goal[cntGoal].sclGoal.y , g_Goal[cntGoal].sclGoal.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldGoal , &g_mtxWorldGoal , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Goal[cntGoal].rotGoal.x , g_Goal[cntGoal].rotGoal.y , g_Goal[cntGoal].rotGoal.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldGoal , &g_mtxWorldGoal , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Goal[cntGoal].posGoal.x , g_Goal[cntGoal].posGoal.y , g_Goal[cntGoal].posGoal.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldGoal , &g_mtxWorldGoal , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldGoal );

			pDevice ->GetMaterial( &matDef );

			pMat = ( D3DXMATERIAL* )g_pBuffMatGoal -> GetBufferPointer();

			for( int nCntMat = 0 ; nCntMat < (int) g_numMatGoal ; nCntMat++ )
			{
				pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
				pDevice -> SetTexture( 0 , g_pTextureGoal );
				g_pMeshGoal ->DrawSubset( nCntMat );
			}

			//�}�e���A�������ɖ߂�
			pDevice -> SetMaterial( &matDef );
		}
	}
}

/******************************************************************************
* �֐����FSetGoal
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetGoal( D3DXVECTOR3 pos )
{
	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		if( g_Goal[cntGoal].useGoal == false )
		{
			g_Goal[cntGoal].posGoal = pos;
			g_Goal[cntGoal].useGoal = true;

			SetShadow( g_Goal[cntGoal].posGoal , SHADOW_GOAL );
			break;
		}
	}
}

/******************************************************************************
* �֐����FGetGoal
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
GOAL *GetGoal( void )
{
	return &g_Goal[0];
}
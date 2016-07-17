/******************************************************************************
* �^�C�g��  :
* �t�@�C����:enemy.cpp
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
LPD3DXBUFFER g_pBuffMatEnemy;//�}�e���A���̏��
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;
LPD3DXMESH g_pMeshEnemy;		//���b�V�����
DWORD g_numMatEnemy;			//�}�e���A���̐�
D3DXMATRIX g_mtxWorldEnemy;
ENEMY g_Enemy[ENEMY_MAX];

/******************************************************************************
* �֐����FInitEnemy
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f������������
******************************************************************************/
void InitEnemy( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	D3DXLoadMeshFromX( "data/MODEL/mouse.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatEnemy,
						NULL,
						&g_numMatEnemy,
						&g_pMeshEnemy );

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		g_Enemy[cntEnemy].posEnemy = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
		g_Enemy[cntEnemy].rotEnemy = D3DXVECTOR3( D3DX_PI / 2 , 0.0f , 0.0f );
		g_Enemy[cntEnemy].sclEnemy = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Enemy[cntEnemy].move     = false;
		g_Enemy[cntEnemy].useEnemy = false;
	}
}

/******************************************************************************
* �֐����FUninitEnemy
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���I������
******************************************************************************/
void UninitEnemy( void )
{
	if( g_pMeshEnemy != NULL )
	{
		g_pMeshEnemy -> Release();
		g_pMeshEnemy = NULL;
	}

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( g_pBuffMatEnemy !=NULL )
		{
			g_pBuffMatEnemy -> Release();
			g_pBuffMatEnemy = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateEnemy
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F
******************************************************************************/
void UpdateEnemy( void )
{
	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		//SetEffect( g_Enemy[cntEnemy].posEnemy , EFFECT_ACORN );

		//�ړ�//////////////////////////////////////////////////////////////////////////
		if( g_Enemy[cntEnemy].move == false )//���Ɉړ�
		{
			g_Enemy[cntEnemy].posEnemy.x -= ENEMY_SPEED;
			g_Enemy[cntEnemy].rotEnemy.x = D3DX_PI / 2;
		}
		else
		{
			g_Enemy[cntEnemy].posEnemy.x += ENEMY_SPEED;
			g_Enemy[cntEnemy].rotEnemy.x = -D3DX_PI / 2;
		}

		//��]//////////////////////////////////////////////////////////////////////////


		//�����蔻��///////////////////////////////////////////////////////////////////////
		//�E�ɓ�����
		if( g_Enemy[cntEnemy].posEnemy.x + 50 > FIELD_WIDHT )
		{
			g_Enemy[cntEnemy].move = false;
		}

		//���ɓ�����
		if( g_Enemy[cntEnemy].posEnemy.x - 50 < - FIELD_WIDHT )
		{
			g_Enemy[cntEnemy].move = true;
		}
	}

}


/******************************************************************************
* �֐����FDrawEnemy
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���̕`��
******************************************************************************/
void DrawEnemy( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( g_Enemy[cntEnemy].useEnemy == true)
		{
				//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_mtxWorldEnemy );

			D3DXMatrixScaling( &mtxScl , g_Enemy[cntEnemy].sclEnemy.x , g_Enemy[cntEnemy].sclEnemy.y , g_Enemy[cntEnemy].sclEnemy.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldEnemy , &g_mtxWorldEnemy , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Enemy[cntEnemy].rotEnemy.x , g_Enemy[cntEnemy].rotEnemy.y , g_Enemy[cntEnemy].rotEnemy.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldEnemy , &g_mtxWorldEnemy , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Enemy[cntEnemy].posEnemy.x , g_Enemy[cntEnemy].posEnemy.y , g_Enemy[cntEnemy].posEnemy.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldEnemy , &g_mtxWorldEnemy , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldEnemy );

			pDevice ->GetMaterial( &matDef );

			pMat = ( D3DXMATERIAL* )g_pBuffMatEnemy -> GetBufferPointer();

			for( int nCntMat = 0 ; nCntMat < (int) g_numMatEnemy ; nCntMat++ )
			{
				pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
				pDevice -> SetTexture( 0 , g_pTextureEnemy );
				g_pMeshEnemy ->DrawSubset( nCntMat );
			}

			//�}�e���A�������ɖ߂�
			pDevice -> SetMaterial( &matDef );
		}
	}
}

/******************************************************************************
* �֐����FSetEnemy
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetEnemy( D3DXVECTOR3 pos )
{
	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( g_Enemy[cntEnemy].useEnemy == false )
		{
			g_Enemy[cntEnemy].posEnemy = pos;
			g_Enemy[cntEnemy].useEnemy = true;

			SetShadow( g_Enemy[cntEnemy].posEnemy , SHADOW_ENEMY );
			break;
		}
	}
}

/******************************************************************************
* �֐����FGetEnemy
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
ENEMY *GetEnemy( void )
{
	return &g_Enemy[0];
}
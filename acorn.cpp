/******************************************************************************
* �^�C�g��  :
* �t�@�C����:acorn.cpp
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
LPD3DXBUFFER g_pBuffMatAcorn = NULL;		//�}�e���A���̏��
LPDIRECT3DTEXTURE9 g_pTextureAcorn = NULL;
LPD3DXMESH g_pMeshAcorn;		//���b�V�����
DWORD g_numMatAcorn;			//�}�e���A���̐�
D3DXMATRIX g_mtxWorldAcorn;
ACORN g_Acorn[ACORN_MAX];

/******************************************************************************
* �֐����FInitAcorn
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f������������
******************************************************************************/
void InitAcorn( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXLoadMeshFromX( "data/MODEL/donguri.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatAcorn,
						NULL,
						&g_numMatAcorn,
						&g_pMeshAcorn );

	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		g_Acorn[cntAcorn].posAcorn  = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
		g_Acorn[cntAcorn].rotAcorn  = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Acorn[cntAcorn].sclAcorn  = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Acorn[cntAcorn].moveY     = 0.0f;
		g_Acorn[cntAcorn].moveRot   = 0.0f;
		g_Acorn[cntAcorn].EffectTime= 0.0f;
		g_Acorn[cntAcorn].acornUse  = false;
		g_Acorn[cntAcorn].acornDraw = false;
	}
}

/******************************************************************************
* �֐����FUninitAcorn
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���I������
******************************************************************************/
void UninitAcorn( void )
{
	if( g_pMeshAcorn != NULL )
	{
		g_pMeshAcorn -> Release();
		g_pMeshAcorn = NULL;
	}

	if( g_pBuffMatAcorn !=NULL )
	{
		g_pBuffMatAcorn -> Release();
		g_pBuffMatAcorn = NULL;
	}
}

/******************************************************************************
* �֐����FUpdateAcorn
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F
******************************************************************************/
void UpdateAcorn( void )
{
	MODEL *pModel = GetModel();

	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		g_Acorn[cntAcorn].rotAcorn.x += ACORN_ROT_SPEED;

		//��]�̏�����
		if( g_Acorn[cntAcorn].rotAcorn.x >= D3DX_PI * 2 )
		{
			g_Acorn[cntAcorn].rotAcorn.x = 0.0f;
		}
		g_Acorn[cntAcorn].rotAcorn.z = ACOUNT_ROTZ;

		//�v���C���[�̎�������邭��
		if( g_Acorn[cntAcorn].acornDraw == true && g_Acorn[cntAcorn].acornUse == false )
		{
			//���W�v�Z
			g_Acorn[cntAcorn].moveY   += ACORN_MOVEY;
			g_Acorn[cntAcorn].moveRot += ACORN_MOVE_ROT;

			g_Acorn[cntAcorn].sclAcorn   = D3DXVECTOR3( 0.5f , 0.5f , 0.5f );
			g_Acorn[cntAcorn].posAcorn.y = pModel -> posModel.y + g_Acorn[cntAcorn].moveY;
			g_Acorn[cntAcorn].posAcorn.x = sinf(g_Acorn[cntAcorn].moveRot) * 20 + pModel -> posModel.x ;
			g_Acorn[cntAcorn].posAcorn.z = cosf(g_Acorn[cntAcorn].moveRot) * 20 + pModel -> posModel.z ;

			//�G�t�F�N�g�̃Z�b�g
			g_Acorn[cntAcorn].EffectTime++;
			//if( g_Acorn[cntAcorn].EffectTime % ACORN_EFFECT_TIME == 0 )
			{
				SetEffect( g_Acorn[cntAcorn].posAcorn , EFFECT_ACORN );
			}

			//�`��I��
			if( g_Acorn[cntAcorn].posAcorn.y - pModel -> posModel.y > 40 )
			{
				g_Acorn[cntAcorn].acornDraw = false;
			}
		}
	}
}


/******************************************************************************
* �֐����FDrawAcorn
* 
* ����  �F�Ȃ�
* �߂�l�F�Ȃ�
* ����  �F���f���̕`��
******************************************************************************/
void DrawAcorn( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		if( g_Acorn[cntAcorn].acornDraw == true )
		{
			D3DXMatrixIdentity( &g_mtxWorldAcorn );

			D3DXMatrixScaling( &mtxScl , g_Acorn[cntAcorn].sclAcorn.x , g_Acorn[cntAcorn].sclAcorn.y , g_Acorn[cntAcorn].sclAcorn.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldAcorn , &g_mtxWorldAcorn , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Acorn[cntAcorn].rotAcorn.x , g_Acorn[cntAcorn].rotAcorn.y , g_Acorn[cntAcorn].rotAcorn.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldAcorn , &g_mtxWorldAcorn , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Acorn[cntAcorn].posAcorn.x , g_Acorn[cntAcorn].posAcorn.y , g_Acorn[cntAcorn].posAcorn.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldAcorn , &g_mtxWorldAcorn , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldAcorn );

			pDevice ->GetMaterial( &matDef );

			pMat = ( D3DXMATERIAL* )g_pBuffMatAcorn -> GetBufferPointer();
			for( int nCntMat = 0 ; nCntMat < (int) g_numMatAcorn ; nCntMat++ )
			{
				pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
				pDevice -> SetTexture( 0 , g_pTextureAcorn );
				g_pMeshAcorn ->DrawSubset( nCntMat );
			}

			//�}�e���A�������ɖ߂�
			pDevice -> SetMaterial( &matDef );
		}

	}
}

/******************************************************************************
* �֐����FSetAcorn
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetAcorn( D3DXVECTOR3 pos )
{
	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		if( g_Acorn[cntAcorn].acornUse == false )
		{
			g_Acorn[cntAcorn].posAcorn = pos;
			g_Acorn[cntAcorn].acornUse = true;
			g_Acorn[cntAcorn].acornDraw = true;

			SetShadow( g_Acorn[cntAcorn].posAcorn , SHADOW_ACORN );
			break;
		}
	}
}

/******************************************************************************
* �֐����FGetAcorn
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
ACORN *GetAcorn( void )
{
	return &g_Acorn[0];
}
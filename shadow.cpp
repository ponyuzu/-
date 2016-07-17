/******************************************************************************
* �^�C�g��  :
* �t�@�C����:shadow.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/11/12
*******************************************************************************
* �X�V����:-2015/11/12 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
D3DXMATRIX g_mtxWorldShadow;

SHADOW g_Shadow[SHADOW_MAX];

int g_CntIdxShadow = 0;//�C���f�b�N�X�̃J�E���g

/******************************************************************************
* �֐����FInitShadow
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitShadow( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * SHADOW_NUM_VTX ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_3D ,
													D3DPOOL_MANAGED ,
													&g_Shadow[cntShadow].pVtxBuffShadow ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}


	g_pTextureShadow = NULL;

	//�e�N�X�`���ǂݍ���
	if( SHADOW_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/shadow000.jpg" , &g_pTextureShadow );
	}

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		VERTEX_3D *pVtx;
		g_Shadow[cntShadow].pVtxBuffShadow -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_Shadow[cntShadow].posShadow = D3DXVECTOR3( 0.0f , 0.5f , 0.0f );
		g_Shadow[cntShadow].rotShadow = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Shadow[cntShadow].sclShadow = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Shadow[cntShadow].shadowUse = false;
		g_Shadow[cntShadow].shadowHeight = 0.0f;
		g_Shadow[cntShadow].shadowWidth = 0.0f;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[1].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[2].pos = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[3].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );

		//���_�J���[�ݒ�
		pVtx[0].col     = D3DXCOLOR( 1.0f , 1.0f , 1.0f, 0.5f );
		pVtx[1].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[2].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[3].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );

		//�e�N�X�`��
		pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
		//�@��
		pVtx[0].nor     = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		g_Shadow[cntShadow].pVtxBuffShadow -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* �֐����FUninitShadow
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitShadow( void )
{
	if( g_pTextureShadow != NULL )
	{
		g_pTextureShadow -> Release();
		g_pTextureShadow = NULL;
	}

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		if( g_Shadow[cntShadow].pVtxBuffShadow !=NULL )
		{
			g_Shadow[cntShadow].pVtxBuffShadow -> Release();
			g_Shadow[cntShadow].pVtxBuffShadow = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateShadow
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateShadow( void )
{
	MODEL *pModel = GetModel();
	BOX *pBox = GetBox();
	ENEMY *pEnemy = GetEnemy();
	ACORN *pAcorn = GetAcorn();
	GOAL *pGoal = GetGoal();

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		VERTEX_3D *pVtx;
		g_Shadow[cntShadow].pVtxBuffShadow -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//�e��N���g���Ă��邩���򂳂���/////////////////////////////////////////////////////////////
		if( g_Shadow[cntShadow].shadowUse == true )
		{
			switch( g_Shadow[cntShadow].shadowPattarn )
			{
			case SHADOW_PLAYER:
				{
					g_Shadow[cntShadow].posShadow.x = pModel -> posModel.x;
					g_Shadow[cntShadow].posShadow.z = pModel -> posModel.z;

					g_Shadow[cntShadow].shadowHeight = 30.0f;
					g_Shadow[cntShadow].shadowWidth = 30.0f;
					break;
				}
			case SHADOW_ENEMY:
				{
					
					g_Shadow[cntShadow].posShadow.x = pEnemy -> posEnemy.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pEnemy -> posEnemy.z;

					g_Shadow[cntShadow].shadowHeight = 30.0f;
					g_Shadow[cntShadow].shadowWidth = 30.0f;
					
					if( pEnemy ->useEnemy == false )
					{
						g_Shadow[cntShadow].shadowUse = false;
					}

					pEnemy++;
					break;
				}

			case SHADOW_BOX:
				{
					
					g_Shadow[cntShadow].posShadow.x = pBox -> posBox.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pBox -> posBox.z;

					g_Shadow[cntShadow].shadowHeight = 40.0f;
					g_Shadow[cntShadow].shadowWidth = 40.0f;

					if( pBox -> boxUse == false )
					{
						g_Shadow[cntShadow].shadowUse = false;

					}

					pBox += 6;
				break;
				}

			case SHADOW_ACORN:
				{
					
					g_Shadow[cntShadow].posShadow.x = pAcorn -> posAcorn.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pAcorn -> posAcorn.z;

					g_Shadow[cntShadow].shadowHeight = 10.0f;
					g_Shadow[cntShadow].shadowWidth = 10.0f;

					if( pAcorn->acornUse == false)
					{
						g_Shadow[cntShadow].shadowUse = false;
					}
					pAcorn++;
					break;
				}
			case SHADOW_GOAL:
				{
					g_Shadow[cntShadow].posShadow.x = pGoal -> posGoal.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pGoal -> posGoal.z;

					g_Shadow[cntShadow].shadowHeight = 10.0f;
					g_Shadow[cntShadow].shadowWidth = 10.0f;
					break;
				}
			}
		}

		//�ݒ�̍X�V///////////////////////////////////////////////////////////////////////
		//���W�X�V
		pVtx[0].pos     = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[1].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[2].pos = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[3].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );

		//���_�J���[�ݒ�
		pVtx[0].col     = D3DXCOLOR( 1.0f , 1.0f , 1.0f, 0.5f );
		pVtx[1].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[2].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[3].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );

		g_Shadow[cntShadow].pVtxBuffShadow -> Unlock();
	}
	
}

/******************************************************************************
* �֐����FDrawShadow
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawShadow( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		if( g_Shadow[cntShadow].shadowUse == true )
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_mtxWorldShadow );

			D3DXMatrixScaling( &mtxScl , g_Shadow[cntShadow].sclShadow.x , g_Shadow[cntShadow].sclShadow.y , g_Shadow[cntShadow].sclShadow.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldShadow , &g_mtxWorldShadow , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Shadow[cntShadow].rotShadow.x , g_Shadow[cntShadow].rotShadow.y , g_Shadow[cntShadow].rotShadow.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldShadow , &g_mtxWorldShadow , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Shadow[cntShadow].posShadow.x , g_Shadow[cntShadow].posShadow.y , g_Shadow[cntShadow].posShadow.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldShadow , &g_mtxWorldShadow , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldShadow );

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_Shadow[0].pVtxBuffShadow , 0 , sizeof( VERTEX_3D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureShadow );

			//�����_�[�X�e�C�g�̐ݒ�ύX
			pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT );
			pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_ONE );

			//�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );

			//�����_�[�X�e�C�g�̐ݒ�߂�
			pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );
			pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		}
	}
}
/******************************************************************************
* �֐����FSetShadow
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetShadow( D3DXVECTOR3 pos , SHADOWPATTARN shadowPattarn )
{
	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		if( g_Shadow[cntShadow].shadowUse == false )
		{
			g_Shadow[cntShadow].posShadow = pos;
			g_Shadow[cntShadow].shadowPattarn = shadowPattarn;
			g_Shadow[cntShadow].shadowUse = true;
			break;
		}
	}
}

/******************************************************************************
* �֐����FGetShadow
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
SHADOW *GetShadow( void )
{
	return g_Shadow;
}
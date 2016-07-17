/******************************************************************************
* �^�C�g��  :
* �t�@�C����:explosion.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/11/17
*******************************************************************************
* �X�V����:-2015/11/17 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
D3DXMATRIX g_mtxWorldExplosion;//billboard�̃��[���h�}�g���b�N�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
EXPLOSION g_Explosion[EXPLOSION_MAX];

/******************************************************************************
* �֐����FInitExplosion
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitExplosion( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( EXPLOSION_NUM_VTX * EXPLOSION_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_3D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffExplosion ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_pTextureExplosion = NULL;

	//�e�N�X�`���ǂݍ���
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/explosion000.png" , &g_pTextureExplosion );
	}

	VERTEX_3D *pVtx;
	g_pVtxBuffExplosion -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntExplosion = 0 , cntVtx = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ , cntVtx += 4 )
	{
		g_Explosion[cntExplosion].posExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Explosion[cntExplosion].rotExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Explosion[cntExplosion].sclExplosion = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Explosion[cntExplosion].explosionUse = false;
		g_Explosion[cntExplosion].nCounterAnim = 0;
		g_Explosion[cntExplosion].nPatternAnim = 0;

		//���W�ݒ�
		pVtx[cntVtx].pos     = D3DXVECTOR3( - EXPLOSION_WIDTH / 2.0f , EXPLOSION_HEIGHT / 2.0f   , 0.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3( EXPLOSION_WIDTH / 2.0f   , EXPLOSION_HEIGHT / 2.0f   , 0.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( - EXPLOSION_WIDTH / 2.0f , - EXPLOSION_HEIGHT / 2.0f , 0.0f );
		pVtx[cntVtx + 3].pos = D3DXVECTOR3( EXPLOSION_WIDTH / 2.0f   , - EXPLOSION_HEIGHT / 2.0f , 0.0f );


		//���_�J���[�ݒ�
		pVtx[cntVtx].col = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		pVtx[cntVtx + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );

		//�e�N�X�`��
		pVtx[cntVtx + 0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 3].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH , 1 );
	
		//�@��
		pVtx[cntVtx].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 1].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 2].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 3].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
	}

	g_pVtxBuffExplosion -> Unlock();


	return S_OK;
}

/******************************************************************************
* �֐����FUninitExplosion
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitExplosion( void )
{
	if( g_pTextureExplosion != NULL )
	{
		g_pTextureExplosion -> Release();
		g_pTextureExplosion = NULL;
	}

	if( g_pVtxBuffExplosion !=NULL )
	{
		g_pVtxBuffExplosion -> Release();
		g_pVtxBuffExplosion = NULL;
	}

}

/******************************************************************************
* �֐����FUpdateExplosion
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateExplosion( void )
{
	VERTEX_3D *pVtx;
	g_pVtxBuffExplosion -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntExplosion = 0 , cntVtx = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ , cntVtx += 4 )
	{
		if( g_Explosion[cntExplosion].explosionUse == true )
		{
			if( g_Explosion[cntExplosion].nPatternAnim < 7 )
			{
				g_Explosion[cntExplosion].nCounterAnim++;

				if( EXPLOSION_TEX_TIME == g_Explosion[cntExplosion].nCounterAnim )
				{
					g_Explosion[cntExplosion].nPatternAnim++;

					//�e�N�X�`��
					pVtx[cntVtx + 0].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * g_Explosion[cntExplosion].nPatternAnim , 0 );
					pVtx[cntVtx + 1].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * ( g_Explosion[cntExplosion].nPatternAnim + 1 ) , 0 );
					pVtx[cntVtx + 2].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * g_Explosion[cntExplosion].nPatternAnim , 1 );
					pVtx[cntVtx + 3].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * ( g_Explosion[cntExplosion].nPatternAnim + 1 ) , 1 );

					g_Explosion[cntExplosion].nCounterAnim = 0;
				}
			}
			else
			{
				g_Explosion[cntExplosion].explosionUse = false;
			}
		}
	}

	g_pVtxBuffExplosion -> Unlock();
}


/******************************************************************************
* �֐����FDrawExplosion
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawExplosion( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	//�A���t�@�e�X�g
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );

	//Z�e�X�g��~
	pDevice -> SetRenderState( D3DRS_ZENABLE , FALSE );

	for( int cntExplosion = 0 , nCntVtx = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ , nCntVtx += 4 )
	{
		if( g_Explosion[cntExplosion].explosionUse == true )
		{
			D3DXMatrixIdentity( &g_mtxWorldExplosion );

			//�r���[�}�g���b�N�X�擾
			pDevice -> GetTransform( D3DTS_VIEW , &mtxView );

			//�t�s������߂�
			D3DXMatrixInverse( &g_mtxWorldExplosion , NULL , &mtxView );

			g_mtxWorldExplosion._41 = 0.0f;
			g_mtxWorldExplosion._42 = 0.0f;
			g_mtxWorldExplosion._43 = 0.0f;

			D3DXMatrixScaling( &mtxScl , 1.0f , 1.0f , 1.0f );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldExplosion , &g_mtxWorldExplosion , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Explosion[cntExplosion].rotExplosion.x , g_Explosion[cntExplosion].rotExplosion.y , g_Explosion[cntExplosion].rotExplosion.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldExplosion , &g_mtxWorldExplosion , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Explosion[cntExplosion].posExplosion.x , g_Explosion[cntExplosion].posExplosion.y , g_Explosion[cntExplosion].posExplosion.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldExplosion , &g_mtxWorldExplosion , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldExplosion );

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_pVtxBuffExplosion , 0 , sizeof( VERTEX_3D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureExplosion );

			//�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , nCntVtx , 2 );

		}
	}

	//Z�e�X�g�ĊJ
	pDevice -> SetRenderState( D3DRS_ZENABLE , TRUE );

	//�A���t�@�e�X�g�߂�
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_ALWAYS );
	pDevice -> SetRenderState( D3DRS_ALPHAREF,0 );
}
/******************************************************************************
* �֐����FSetExplosion
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetExplosion( D3DXVECTOR3 pos )
{
	for( int cntExplosion = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ )
	{
		if( g_Explosion[cntExplosion].explosionUse == false )
		{
			g_Explosion[cntExplosion].nCounterAnim = 0;
			g_Explosion[cntExplosion].nPatternAnim = 0;
			g_Explosion[cntExplosion].posExplosion = pos;
			g_Explosion[cntExplosion].explosionUse = true;
			break;
		}
	}
}
/******************************************************************************
* �֐����FGetExplosion
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
EXPLOSION *GetExplosion( void )
{
	return g_Explosion;
}
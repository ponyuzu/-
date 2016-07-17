/******************************************************************************
* �^�C�g��  :
* �t�@�C����:acorncnt.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o��
******************************************************************************/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAcornCnt = NULL;
LPDIRECT3DTEXTURE9 g_pTextureAcornCnt[ACORN_TEX_MAX];

ACORNCNT g_acornCnt[ACORNCNT_MAX];

int g_AcornCntValue;	//�����_

/******************************************************************************
* �֐����FInitAcornCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitAcornCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main�ł�g_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * ( 4 * ACORNCNT_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffAcornCnt ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_AcornCntValue = 0;

	VERTEX_2D *pVtx;
	g_pVtxBuffAcornCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/number000.png" , &g_pTextureAcornCnt[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/kakeru.png" , &g_pTextureAcornCnt[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/donguri000.png" , &g_pTextureAcornCnt[2] );


	for( int nCntAcornCnt = 0 , vtxCntAcornCnt = 0 , posAcornCntX = 0 ;  nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ , vtxCntAcornCnt += 4  , posAcornCntX -= ACORN_TEX_WIDTH )
	{
		g_acornCnt[nCntAcornCnt].posAcornCnt    = D3DXVECTOR3( 200.0f + posAcornCntX , 40.0f , 0.0f );
		g_acornCnt[nCntAcornCnt].heightAcornCnt = ACORNCNT_HEIGHT / 2;
		g_acornCnt[nCntAcornCnt].widthAcornCnt  = ACORNCNT_WIDTH / 2;
		g_acornCnt[nCntAcornCnt].acornInd       = ACORN_IND;
		g_acornCnt[nCntAcornCnt].cntIndTime    = 0;

		if( nCntAcornCnt == ACORNCNT_MAX - 1 )//�ǂ񂮂�̕�
		{
			g_acornCnt[nCntAcornCnt].heightAcornCnt = ACORN_TEX_HEIGHT / 2;
			g_acornCnt[nCntAcornCnt].widthAcornCnt  = ACORN_TEX_WIDTH / 2;
		}
		else if( nCntAcornCnt == ACORNCNT_MAX - 2 )//�~�̕�
		{
			g_acornCnt[nCntAcornCnt].heightAcornCnt = ACORN_KAKERU_HEIGHT / 2;
		}

		//���W�ݒ�
		pVtx[vtxCntAcornCnt].pos     = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 1].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 2].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 3].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );

		//2�����ϐ�
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[vtxCntAcornCnt + add].rwh = 1.0f;
		}

		//���_�J���[�ݒ�
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[vtxCntAcornCnt + add].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		//�e�N�X�`��
		pVtx[vtxCntAcornCnt].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[vtxCntAcornCnt + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[vtxCntAcornCnt + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[vtxCntAcornCnt + 3].tex = D3DXVECTOR2( 1 , 1 );

	}

	g_pVtxBuffAcornCnt -> Unlock();

	return S_OK;
}

/******************************************************************************
* �֐����FIninitAcornCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitAcornCnt( void )
{
	for( int cntTex = 0; cntTex < ACORN_TEX_MAX ; cntTex++ )
	{
		if( g_pTextureAcornCnt[cntTex] != NULL )
		{
			g_pTextureAcornCnt[cntTex] -> Release();
			g_pTextureAcornCnt[cntTex] = NULL;
		}
	}

	if( g_pVtxBuffAcornCnt !=NULL )
	{
		g_pVtxBuffAcornCnt -> Release();
		g_pVtxBuffAcornCnt = NULL;
	}
	
}

/******************************************************************************
* �֐����FUpdateAcornCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateAcornCnt( void )
{
	float num;
	int scoreWork = g_AcornCntValue;
	
	VERTEX_2D *pVtx;
	g_pVtxBuffAcornCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );


	//���_�𐔎��ɔ��f////////////////////////////////////////////////////////////////////
	for( int nCntAcornCnt = 0 , vtxCntAcornCnt = 0  ; nCntAcornCnt < ACORNCNT_MAX - 2 ; nCntAcornCnt++ , vtxCntAcornCnt += 4 )
	{
		num = scoreWork % 10;
		scoreWork /= 10;
		
		g_acornCnt[nCntAcornCnt].posTexXAcornCnt = ( num / 10 );

		//�e�N�X�`��
		pVtx[vtxCntAcornCnt].tex     = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt                       , 0 );
		pVtx[vtxCntAcornCnt + 1].tex = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt + ACORNCNT_PATTERN_WIDTH , 0 );
		pVtx[vtxCntAcornCnt + 2].tex = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt                       , 1 );
		pVtx[vtxCntAcornCnt + 3].tex = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt + ACORNCNT_PATTERN_WIDTH , 1 );
	}

	for( int nCntAcornCnt = 0 , vtxCntAcornCnt = 0  ; nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ , vtxCntAcornCnt += 4 )
	{
		//�\���̏���//////////////////////////////////////////////////////////////////////
		switch( g_acornCnt[nCntAcornCnt].acornInd )
		{
		case ACORN_NONE://�\�����Ȃ�
			{
				g_acornCnt[nCntAcornCnt].cntIndTime = 0;
				break;
			}
		case ACORN_DOWN://���Ɉړ�
			{
				if( g_acornCnt[nCntAcornCnt].posAcornCnt.y < ACORNCNT_POSY )
				{
					g_acornCnt[nCntAcornCnt].posAcornCnt.y += ACORNCNT_DOWN_SPEED;
				}
				else
				{
					g_acornCnt[nCntAcornCnt].acornInd = ACORN_IND;
				}
				break;
			}
		case ACORN_IND://�\��
			{
				g_acornCnt[nCntAcornCnt].cntIndTime++;

				
				if( g_acornCnt[nCntAcornCnt].cntIndTime  % ACORNCNT_INDICATE_TIME == 0 )
				{
					g_acornCnt[nCntAcornCnt].acornInd = ACORN_UP;
				}
				break;
			}
		case ACORN_UP://��ɂ��܂�
			{
				if( g_acornCnt[nCntAcornCnt].posAcornCnt.y > - ACORNCNT_POSY )
				{
					g_acornCnt[nCntAcornCnt].posAcornCnt.y += ACORNCNT_UP_SPEED;
				}
				else
				{
					g_acornCnt[nCntAcornCnt].acornInd = ACORN_NONE;
				}
				break;
			}
		}

		//���W���
		pVtx[vtxCntAcornCnt].pos     = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 1].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 2].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 3].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );

	}


	//�P�O�O�ɂȂ�����1UP(���Z�b�g)
	if( g_AcornCntValue >= 100 )
	{
		AddLifeCnt(1);
		g_AcornCntValue = 0;
	}

	g_pVtxBuffAcornCnt -> Unlock();
}

/******************************************************************************
* �֐����FDrawAcornCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawAcornCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource( 0 , g_pVtxBuffAcornCnt , 0 , sizeof( VERTEX_2D ));

	//���_�t�H�[�}�b�g
	pDevice -> SetFVF( FVF_VERTEX_2D );

	pDevice -> SetTexture( 0 , g_pTextureAcornCnt[0] );

	for( int nCntAcornCnt = 0 ; nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ )
	{
		if( nCntAcornCnt == ACORNCNT_MAX - 2 )//�e�N�X�`���`�F���W
		{
			pDevice -> SetTexture( 0 , g_pTextureAcornCnt[1] );
		}
		else if( nCntAcornCnt == ACORNCNT_MAX - 1 )
		{
			pDevice -> SetTexture( 0 , g_pTextureAcornCnt[2] );
		}

		//�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 * nCntAcornCnt, 2 );
	}
}

/******************************************************************************
* �֐����FGetAcornCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
ACORNCNT *GetAcornCnt( void )
{
	return g_acornCnt;
}


/******************************************************************************
* �֐����FAddAcornCnt
* 
* ����  �F���Z�p�̃X�R�A
* �߂�l�F�Ȃ�
* ����  �F�W�߂��X�R�A��g_AcornCntvalue�ɑS�đ���
******************************************************************************/
void AddAcornCnt( int value )
{
	g_AcornCntValue += value;

	//�\��
	for( int acornCnt = 0 ; acornCnt < ACORNCNT_MAX ; acornCnt++ )
	{
		g_acornCnt[acornCnt].acornInd = ACORN_DOWN;
	}
}
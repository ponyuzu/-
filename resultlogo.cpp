/******************************************************************************
* �^�C�g��  :
* �t�@�C����:select.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/02/01
*******************************************************************************
* �X�V����:-2016/02/01 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "resultlogo.h"

/******************************************************************************
* �O���[�o��
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureResultLogo[RESULTLOGO_MAX];

RESULTLOGO g_result[RESULTLOGO_MAX];
RESULTMODE g_resultMode;

/******************************************************************************
* �֐����FInitResultLogo
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitResultLogo( void )
{
	InitCamera();
	g_resultMode = GetResultMode();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main�ł�g_pD3DDevice

	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_2D ,
													D3DPOOL_MANAGED ,
													&g_result[nCntResultLogo].pVtxBuffResultLogo ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo000.png" , &g_pTextureResultLogo[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo001.png" , &g_pTextureResultLogo[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo002.png" , &g_pTextureResultLogo[2] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo003.png" , &g_pTextureResultLogo[3] );


	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
		VERTEX_2D *pVtx;
		g_result[nCntResultLogo].pVtxBuffResultLogo -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_result[0].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 - 100 , 0.0f );
		g_result[0].heightResultLogo = RESULTLOGO1_HEIDHT / 2;
		g_result[0].widthResultLogo  = RESULTLOGO1_WIDTH  / 2;

		g_result[1].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT - 200 , 0.0f );
		g_result[1].heightResultLogo = RESULTLOGO2_HEIDHT / 2;
		g_result[1].widthResultLogo  = RESULTLOGO2_WIDTH / 2;

		g_result[2].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 - 100 , 0.0f );
		g_result[2].heightResultLogo = RESULTLOGO3_HEIDHT / 2;
		g_result[2].widthResultLogo  = RESULTLOGO3_WIDTH  / 2;

		g_result[3].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT - 200 , 0.0f );
		g_result[3].heightResultLogo = RESULTLOGO4_HEIDHT / 2;
		g_result[3].widthResultLogo  = RESULTLOGO4_WIDTH / 2;

		g_result[nCntResultLogo].LogoUse = false;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x - g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y - g_result[nCntResultLogo].heightResultLogo , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x + g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y - g_result[nCntResultLogo].heightResultLogo , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x - g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y + g_result[nCntResultLogo].heightResultLogo , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x + g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y + g_result[nCntResultLogo].heightResultLogo , 0.0f );

		//2�����ϐ�
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[add].rwh = 1.0f;
		}

		//���_�J���[�ݒ�
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[add].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		//�e�N�X�`��
		pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );

		g_result[nCntResultLogo].pVtxBuffResultLogo -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* �֐����FIninitResultLogo
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitResultLogo( void )
{
	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
		if( g_result[nCntResultLogo].pVtxBuffResultLogo !=NULL )
		{
			g_result[nCntResultLogo].pVtxBuffResultLogo -> Release();
			g_result[nCntResultLogo].pVtxBuffResultLogo = NULL;
		}

		if( g_pTextureResultLogo[nCntResultLogo] != NULL )
		{
			g_pTextureResultLogo[nCntResultLogo] -> Release();
			g_pTextureResultLogo[nCntResultLogo] = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateResultLogo
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateResultLogo( void )
{
	switch( g_resultMode )
	{
	case RESULT_CREAL:
		{
			g_result[0].LogoUse = true;
			g_result[1].LogoUse = true;
			break;
		}
	case RESULT_GAMEOVER:
		{
			g_result[2].LogoUse = true;
			g_result[3].LogoUse = true;
			break;
		}
	}
}

/******************************************************************************
* �֐����FDrawResultLogo
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawResultLogo( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
		if( g_result[nCntResultLogo].LogoUse == true )
		{

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_result[nCntResultLogo].pVtxBuffResultLogo , 0 , sizeof( VERTEX_2D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_2D );

			pDevice -> SetTexture( 0 , g_pTextureResultLogo[nCntResultLogo] );

			//�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
		}
	}

}
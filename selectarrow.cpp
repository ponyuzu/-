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
#include "selectarrow.h"

/******************************************************************************
* �O���[�o��
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureSelectAro;

SELECTARO g_select[SELECT_ARO_MAX];

/******************************************************************************
* �֐����FInitSelectAro
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitSelectAro( void )
{
	InitCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main�ł�g_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_select[0].pVtxBuffSelectAro ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/select000.png" , &g_pTextureSelectAro );


	for( int nCntSelectAro = 0 ;  nCntSelectAro < SELECT_ARO_MAX ; nCntSelectAro++ )
	{
		VERTEX_2D *pVtx;
		g_select[nCntSelectAro].pVtxBuffSelectAro -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_select[nCntSelectAro].posSelectAro    = D3DXVECTOR3( SCREEN_WIDTH -150 , SCREEN_HEIGHT /2 , 0.0f );
		g_select[nCntSelectAro].heightSelectAro = SELECT_ARO_WIDTH / 2;
		g_select[nCntSelectAro].widthSelectAro  = SELECT_ARO_HEIDHT / 2;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3( g_select[nCntSelectAro].posSelectAro.x - g_select[nCntSelectAro].widthSelectAro , g_select[nCntSelectAro].posSelectAro.y - g_select[nCntSelectAro].heightSelectAro , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_select[nCntSelectAro].posSelectAro.x + g_select[nCntSelectAro].widthSelectAro , g_select[nCntSelectAro].posSelectAro.y - g_select[nCntSelectAro].heightSelectAro , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_select[nCntSelectAro].posSelectAro.x - g_select[nCntSelectAro].widthSelectAro , g_select[nCntSelectAro].posSelectAro.y + g_select[nCntSelectAro].heightSelectAro , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_select[nCntSelectAro].posSelectAro.x + g_select[nCntSelectAro].widthSelectAro , g_select[nCntSelectAro].posSelectAro.y + g_select[nCntSelectAro].heightSelectAro , 0.0f );

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
		pVtx[1].tex = D3DXVECTOR2( 0.5 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 0.5 , 1 );

		g_select[nCntSelectAro].pVtxBuffSelectAro -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* �֐����FIninitSelectAro
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitSelectAro( void )
{
	for( int nCntSelectAro = 0 ;  nCntSelectAro < SELECT_ARO_MAX ; nCntSelectAro++ )
	{
		if( g_select[nCntSelectAro].pVtxBuffSelectAro !=NULL )
		{
			g_select[nCntSelectAro].pVtxBuffSelectAro -> Release();
			g_select[nCntSelectAro].pVtxBuffSelectAro = NULL;
		}
	}

	if( g_pTextureSelectAro != NULL )
	{
		g_pTextureSelectAro -> Release();
		g_pTextureSelectAro = NULL;
	}
}

/******************************************************************************
* �֐����FUpdateSelectAro
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateSelectAro( void )
{
	
}

/******************************************************************************
* �֐����FDrawSelectAro
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawSelectAro( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntSelectAro = 0 ;  nCntSelectAro < SELECT_ARO_MAX ; nCntSelectAro++ )
	{
		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetStreamSource( 0 , g_select[nCntSelectAro].pVtxBuffSelectAro , 0 , sizeof( VERTEX_2D ));

		//���_�t�H�[�}�b�g
		pDevice -> SetFVF( FVF_VERTEX_2D );

		pDevice -> SetTexture( 0 , g_pTextureSelectAro );

		//�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
	}

}
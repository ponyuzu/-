/******************************************************************************
* �^�C�g��  :
* �t�@�C����:fade.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
D3DXCOLOR g_colorFade;		//�t�F�[�h�F
FADE g_fade;				//�t�F�[�h�̏��
MODE g_modeNext;			//���̃��[�h
float g_alphaMove;			//���l�̌v�Z

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;


/******************************************************************************
* �֐����FInitFaed
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitFade( void )
{
	g_colorFade = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );
	g_fade = FADE_IN;
	g_modeNext = MODE_TITLE;
	g_alphaMove = 1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main�ł�g_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffFade ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffFade -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );
	//���W�ݒ�
	pVtx[0].pos = D3DXVECTOR3( 0.0f         , 0.0f          , 0.0f );
	pVtx[1].pos = D3DXVECTOR3( SCREEN_WIDTH , 0.0f          , 0.0f );
	pVtx[2].pos = D3DXVECTOR3( 0.0f         , SCREEN_HEIGHT , 0.0f );
	pVtx[3].pos = D3DXVECTOR3( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f );

	//2�����ϐ�
	pVtx[0].rwh = 1.0f;
	pVtx[1].rwh = 1.0f;
	pVtx[2].rwh = 1.0f;
	pVtx[3].rwh = 1.0f;

	//���_�J���[�ݒ�
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	g_pVtxBuffFade -> Unlock();

	return S_OK;
}

/******************************************************************************
* �֐����FUninitFaed
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitFade( void )
{
}

/******************************************************************************
* �֐����FUpdateFaed
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateFade ( void )
{
	switch( g_fade )
	{
	case FADE_IN:
		//���v�Z
		g_colorFade.a -= 0.02f;

		if( g_colorFade.a <= 0.0f )
		{
			g_fade = FADE_NONE;
		}
		break;

	case FADE_OUT:
		//���v�Z
		g_colorFade.a += 0.02f;

		if( g_colorFade.a >= 1.0f )
		{
			SetMode( g_modeNext );
			g_fade = FADE_IN;
		}
		break;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffFade -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	//���_�J���[�ݒ�
	pVtx[0].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );
	pVtx[1].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );
	pVtx[2].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );
	pVtx[3].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );

	g_pVtxBuffFade -> Unlock();
}

/******************************************************************************
* �֐����FDrawFaed
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawFade( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource( 0 , g_pVtxBuffFade , 0 , sizeof( VERTEX_2D ));

	//���_�t�H�[�}�b�g
	pDevice -> SetFVF( FVF_VERTEX_2D );

	pDevice -> SetTexture( 0 , g_pTextureFade );

	//�|���S���̕`��
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
}

/******************************************************************************
* �֐����FSetFade
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetFade( FADE fade , MODE modeNext )
{
	if( g_fade == FADE_NONE )
	{
		g_fade = fade;
		g_modeNext = modeNext;
	}
}

/******************************************************************************
* �֐����FGetFade
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
FADE *GetFade( void )
{
	return &g_fade;
}
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:pause.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "pause.h"

/******************************************************************************
* �O���[�o��
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_TEX_MAX];

PAUSE g_pause[PAUSE_TEX_MAX];
PAUSEPATTARN g_pausePattarn;

bool g_bPause;				//�|�[�Y���ǂ���

/******************************************************************************
* �֐����FInitPause
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitPause( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main�ł�g_pD3DDevice

	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{
		if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_2D ,
													D3DPOOL_MANAGED ,
													&g_pause[cnt].pVtxBuffPause ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	g_pausePattarn = PAUSE_CONTINUE;	//�|�[�Y�p�^�[���̏����l

	g_bPause = false;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile( pDevice , PAUSE_BG_NAME , &g_pTexturePause[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/pause000.png" , &g_pTexturePause[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/pause001.png" , &g_pTexturePause[2] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/pause002.png" , &g_pTexturePause[3] );


	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{

		VERTEX_2D *pVtx;
		g_pause[cnt].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );


		g_pause[0].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 , 0.0f );
		g_pause[0].height = PAUSE_BG_HEIGHT / 2;
		g_pause[0].width  = PAUSE_BG_WIDTH  / 2;

		g_pause[1].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 100 , 0.0f );
		g_pause[1].height = PAUSE_LOGO1_HEIGHT / 2;
		g_pause[1].width  = PAUSE_LOGO1_WIDTH / 2;

		g_pause[2].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 , 0.0f );
		g_pause[2].height = PAUSE_LOGO2_HEIGHT / 2;
		g_pause[2].width  = PAUSE_LOGO2_WIDTH  / 2;

		g_pause[3].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 + 100, 0.0f );
		g_pause[3].height = PAUSE_LOGO3_HEIGHT / 2;
		g_pause[3].width  = PAUSE_LOGO3_WIDTH / 2;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3( g_pause[cnt].pos.x - g_pause[cnt].width , g_pause[cnt].pos.y - g_pause[cnt].height , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_pause[cnt].pos.x + g_pause[cnt].width , g_pause[cnt].pos.y - g_pause[cnt].height , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_pause[cnt].pos.x - g_pause[cnt].width , g_pause[cnt].pos.y + g_pause[cnt].height , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_pause[cnt].pos.x + g_pause[cnt].width , g_pause[cnt].pos.y + g_pause[cnt].height , 0.0f );


		//2�����ϐ�
		pVtx[0].rwh = 1.0f;
		pVtx[1].rwh = 1.0f;
		pVtx[2].rwh = 1.0f;
		pVtx[3].rwh = 1.0f;

		//���_�J���[�ݒ�
		for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
		{
			pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );

		g_pause[cnt].pVtxBuffPause -> Unlock();

	}

	return S_OK;
}

/******************************************************************************
* �֐����FIninitPause
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitPause( void )
{
	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{
		if( g_pTexturePause[cnt] != NULL )
		{
			g_pTexturePause[cnt] -> Release();
			g_pTexturePause[cnt] = NULL;
		}

		if( g_pause[cnt].pVtxBuffPause !=NULL )
		{
			g_pause[cnt].pVtxBuffPause -> Release();
			g_pause[cnt].pVtxBuffPause = NULL;
		}
	}
	
}

/******************************************************************************
* �֐����FUpdatePause
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdatePause( void )
{

	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{

		VERTEX_2D *pVtx;
		g_pause[cnt].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//���_�J���[�ݒ�
		for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
		{
			pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		g_pause[cnt].pVtxBuffPause -> Unlock();

	}

	switch( g_pausePattarn )
	{
	case PAUSE_CONTINUE:
		{
			VERTEX_2D *pVtx;
			g_pause[1].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//���_�J���[�ݒ�
			for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 0 , 0 , 255 );
			}

			g_pause[1].pVtxBuffPause -> Unlock();

			break;
		}
	case PAUSE_RETRY:
		{
			VERTEX_2D *pVtx;
			g_pause[2].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//���_�J���[�ݒ�
			for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 0 , 0 , 255 );
			}

			g_pause[2].pVtxBuffPause -> Unlock();
			break;
		}
	case PAUSE_QUIT:
		{
			VERTEX_2D *pVtx;
			g_pause[3].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//���_�J���[�ݒ�
			for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 0 , 0 , 255 );
			}

			g_pause[3].pVtxBuffPause -> Unlock();
			break;
		}
	}

	//�|�[�Y���̏���
	if( g_bPause == true )
	{
		//��Ɉړ�
		if( GetKeyboardTrigger( DIK_W ) )
		{
			if( g_pausePattarn == PAUSE_CONTINUE )
			{
				g_pausePattarn = PAUSE_QUIT;
			}
			else if( g_pausePattarn == PAUSE_QUIT )
			{
				g_pausePattarn = PAUSE_RETRY;
			}
			else
			{
				g_pausePattarn = PAUSE_CONTINUE;
			}
		}

		//���Ɉړ�
		else if( GetKeyboardTrigger( DIK_S ) )
		{
			if( g_pausePattarn == PAUSE_CONTINUE )
			{
				g_pausePattarn = PAUSE_RETRY;
			}
			else if( g_pausePattarn == PAUSE_RETRY )
			{
				g_pausePattarn = PAUSE_QUIT;
			}
			else
			{
				g_pausePattarn = PAUSE_CONTINUE;
			}
		}

		//enter�����������̏���
		if( GetKeyboardTrigger( DIK_RETURN ) )
		{
			if( g_pausePattarn == PAUSE_CONTINUE )
			{
				g_bPause = false;
			}
			else if( g_pausePattarn == PAUSE_RETRY )
			{
				SetFade( FADE_OUT , MODE_GAME );
			}
			else
			{
				SetFade( FADE_OUT , MODE_SELECT );
			}
		}
	}

}

/******************************************************************************
* �֐����FDrawPause
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawPause( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{
		if( g_bPause == true )
		{
			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_pause[cnt].pVtxBuffPause , 0 , sizeof( VERTEX_2D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_2D );

			pDevice -> SetTexture( 0 , g_pTexturePause[cnt] );

			//�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
		}
	}

}
/******************************************************************************
* �֐����FGetPause
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
bool GetPause( void )
{
	return g_bPause;
}

/******************************************************************************
* �֐����FSetPause
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetPause( bool pause )
{
	g_bPause = pause;
}
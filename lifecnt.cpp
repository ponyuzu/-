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
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeCnt = NULL;
LPDIRECT3DTEXTURE9 g_pTextureLifeCnt[LIFECNT_TEX_MAX];

LIFECNT g_lifeCnt[LIFECNT_MAX];

int g_LifeCntValue;	//�����_

/******************************************************************************
* �֐����FInitLifeCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitLifeCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//main�ł�g_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * ( 4 * LIFECNT_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffLifeCnt ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_LifeCntValue = 0;

	VERTEX_2D *pVtx;
	g_pVtxBuffLifeCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/number000.png" , &g_pTextureLifeCnt[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/kakeru.png" , &g_pTextureLifeCnt[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/tanuki000.png" , &g_pTextureLifeCnt[2] );

	for( int lifeCnt = 0 , vtxCntLifeCnt = 0 , posLifeCntX = 0 ;  lifeCnt < LIFECNT_MAX ; lifeCnt++ , vtxCntLifeCnt += 4  , posLifeCntX -= LIFECNT_TEX_WIDTH )
	{
		g_lifeCnt[lifeCnt].posLifeCnt    = D3DXVECTOR3( 660.0f + posLifeCntX , -LIFECNT_POSY , 0.0f );
		g_lifeCnt[lifeCnt].heightLifeCnt = LIFECNT_HEIGHT / 2;
		g_lifeCnt[lifeCnt].widthLifeCnt  = LIFECNT_WIDTH / 2;
		g_lifeCnt[lifeCnt].lifeInd       = LIFE_IND;
		g_lifeCnt[lifeCnt].cntIndTime    = 0;

		if( lifeCnt == LIFECNT_MAX - 1 )//���ʂ��̕�
		{
			
			g_lifeCnt[lifeCnt].heightLifeCnt = LIFECNT_TEX_HEIGHT / 2;
			g_lifeCnt[lifeCnt].widthLifeCnt  = LIFECNT_TEX_WIDTH / 2;
		}
		else if( lifeCnt == LIFECNT_MAX - 2 )//�~�̕�
		{
			
			g_lifeCnt[lifeCnt].heightLifeCnt = LIFECNT_KAKERU_HEIGHT / 2;
		}

		//���W�ݒ�
		pVtx[vtxCntLifeCnt].pos     = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 1].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 2].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 3].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );

		//2�����ϐ�
		pVtx[vtxCntLifeCnt].rwh     = 1.0f;
		pVtx[vtxCntLifeCnt + 1].rwh = 1.0f;
		pVtx[vtxCntLifeCnt + 2].rwh = 1.0f;
		pVtx[vtxCntLifeCnt + 3].rwh = 1.0f;

		//���_�J���[�ݒ�
		pVtx[vtxCntLifeCnt].col     = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[vtxCntLifeCnt + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[vtxCntLifeCnt + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[vtxCntLifeCnt + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );

		//�e�N�X�`��
		pVtx[vtxCntLifeCnt].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[vtxCntLifeCnt + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[vtxCntLifeCnt + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[vtxCntLifeCnt + 3].tex = D3DXVECTOR2( 1 , 1 );
	}

	g_pVtxBuffLifeCnt -> Unlock();

	g_LifeCntValue = 4;

	return S_OK;
}

/******************************************************************************
* �֐����FIninitLifeCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitLifeCnt( void )
{
	for( int cntTex = 0 ; cntTex < LIFECNT_TEX_MAX ; cntTex++ )
	{
		if( g_pTextureLifeCnt[cntTex] != NULL )
		{
			g_pTextureLifeCnt[cntTex] -> Release();
			g_pTextureLifeCnt[cntTex] = NULL;
		}
	}

	if( g_pVtxBuffLifeCnt !=NULL )
	{
		g_pVtxBuffLifeCnt -> Release();
		g_pVtxBuffLifeCnt = NULL;
	}
	
}

/******************************************************************************
* �֐����FUpdateLifeCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateLifeCnt( void )
{
	float num;
	int scoreWork = g_LifeCntValue;
	MODEL *pModel = GetModel();
	
	VERTEX_2D *pVtx;
	g_pVtxBuffLifeCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int lifeCnt = 0 , vtxCntLifeCnt = 0  ; lifeCnt < LIFECNT_MAX - 2 ; lifeCnt++ , vtxCntLifeCnt += 4 )
	{
		//�����̕`���ς������v�Z///////////////////////////////////////////////////////////////
		num = scoreWork % 10;
		scoreWork /= 10;
		
		g_lifeCnt[lifeCnt].posTexXLifeCnt = ( num / 10 );

		//�e�N�X�`��
		pVtx[vtxCntLifeCnt].tex     = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt                       , 0 );
		pVtx[vtxCntLifeCnt + 1].tex = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt + LIFECNT_PATTERN_WIDTH , 0 );
		pVtx[vtxCntLifeCnt + 2].tex = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt                       , 1 );
		pVtx[vtxCntLifeCnt + 3].tex = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt + LIFECNT_PATTERN_WIDTH , 1 );

	}

	for( int lifeCnt = 0 , vtxCntLifeCnt = 0  ; lifeCnt < LIFECNT_MAX ; lifeCnt++ , vtxCntLifeCnt += 4 )
	{
		//�\���̏���//////////////////////////////////////////////////////////////////////
		switch( g_lifeCnt[lifeCnt].lifeInd )
		{
		case LIFE_NONE://�\�����Ȃ�
			{
				g_lifeCnt[lifeCnt].cntIndTime    = 0;
				break;
			}
		case LIFE_DOWN://���Ɉړ�
			{
				if( g_lifeCnt[lifeCnt].posLifeCnt.y < LIFECNT_POSY )
				{
					g_lifeCnt[lifeCnt].posLifeCnt.y += LIFECNT_DOWN_SPEED;
				}
				else
				{
					g_lifeCnt[lifeCnt].lifeInd = LIFE_IND;
				}
				break;
			}
		case LIFE_IND://�\��
			{
				g_lifeCnt[lifeCnt].cntIndTime++;

				if( g_lifeCnt[lifeCnt].cntIndTime  % LIFECNT_INDICATE_TIME == 0 )
				{
					g_lifeCnt[lifeCnt].lifeInd = LIFE_UP;
				}
				break;
			}
		case LIFE_UP://��ɂ��܂�
			{
				if( g_lifeCnt[lifeCnt].posLifeCnt.y > - LIFECNT_POSY )
				{
					g_lifeCnt[lifeCnt].posLifeCnt.y += LIFECNT_UP_SPEED;
				}
				else
				{
					g_lifeCnt[lifeCnt].lifeInd = LIFE_NONE;
				}
				break;
			}
		}

		//�Q�[���I�[�o�[///////////////////////////////////////////////////////////
		if( g_LifeCntValue <= -1 )//���C�t���s������
		{
			g_lifeCnt[lifeCnt].posLifeCnt.y = - LIFECNT_POSY;
			SetResultMode( RESULT_GAMEOVER );
			SetFade( FADE_OUT , MODE_RESULT );

			//���Z�b�g���ׂ�����
			InitAcornCnt();
			InitLifeCnt();
		}
		else//�ʒu���Z�b�g
		{
			if(pModel -> death == true )
			{
				SetFade( FADE_OUT , MODE_GAME );
			}
		}

		//���W���
		pVtx[vtxCntLifeCnt].pos     = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 1].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 2].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 3].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );

	}

	g_pVtxBuffLifeCnt -> Unlock();
}

/******************************************************************************
* �֐����FDrawLifeCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawLifeCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice -> SetStreamSource( 0 , g_pVtxBuffLifeCnt , 0 , sizeof( VERTEX_2D ));

	//���_�t�H�[�}�b�g
	pDevice -> SetFVF( FVF_VERTEX_2D );

	pDevice -> SetTexture( 0 , g_pTextureLifeCnt[0] );

	for( int lifeCnt = 0 ; lifeCnt < LIFECNT_MAX ; lifeCnt++ )
	{
		if( lifeCnt == LIFECNT_MAX - 2 )//�e�N�X�`���`�F���W
		{
			pDevice -> SetTexture( 0 , g_pTextureLifeCnt[1] );
		}
		else if( lifeCnt == LIFECNT_MAX - 1 )
		{
			pDevice -> SetTexture( 0 , g_pTextureLifeCnt[2] );
		}

		//�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 * lifeCnt, 2 );
	}
}

/******************************************************************************
* �֐����FGetLifeCnt
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
LIFECNT *GetLifeCnt( void )
{
	return g_lifeCnt;
}

/******************************************************************************
* �֐����FAddLifeCnt
* 
* ����  �F���Z�p�̃X�R�A
* �߂�l�F�Ȃ�
* ����  �F�W�߂��X�R�A��g_LifeCntvalue�ɑS�đ����Alife�\��
******************************************************************************/
void AddLifeCnt( int value )
{
	//����
	g_LifeCntValue += value;

	//�\��
	for( int lifeCnt = 0 ; lifeCnt < LIFECNT_MAX ; lifeCnt++ )
	{
		g_lifeCnt[lifeCnt].lifeInd = LIFE_DOWN;
	}
}
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:tiele.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "title.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
D3DXMATRIX g_mtxWorldTitle;//billboard�̃��[���h�}�g���b�N�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEX_MAX];
TITLE g_Title[TITLE_TEX_MAX];

/******************************************************************************
* �֐����FInitTitle
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitTitle( void )
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *pCamera = GetCamera();

	//�J�����ʒu(�^�C�g�������ʒu)
	pCamera -> posV = D3DXVECTOR3( 0 , 0 , -50 );//�ʒu
	pCamera -> posR = D3DXVECTOR3( 0 , 0 , 10 );//�����_

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * TITLE_TEX_MAX * 4,
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_3D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffTitle ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	for( int cntTex = 0 ; cntTex < TITLE_TEX_MAX ; cntTex++ )
	{
		g_pTextureTitle[cntTex] = NULL;
	}

	//�e�N�X�`���ǂݍ���
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo004.png" , &g_pTextureTitle[0] );//�ۂ�
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo005.png" , &g_pTextureTitle[1] );//�ۂ�
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo001.png" , &g_pTextureTitle[2] );//���ʂ�
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo002.png" , &g_pTextureTitle[3] );//�o�b�N
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo003.png" , &g_pTextureTitle[4] );//�t����
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/press_enter.png" , &g_pTextureTitle[5] );//enter�L�[
	}

	float logoWidth , logoHeight;

	VERTEX_3D *pVtx;
	g_pVtxBuffTitle -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntLogo = 0 , cntVtx = 0 ; cntLogo < TITLE_TEX_MAX ; cntLogo++ , cntVtx += 4 )
	{

		switch( cntLogo )
		{
		case 0:
			{
				logoWidth = TITLE_LOGO1_WIDTH;
				logoHeight = TITLE_LOGO1_HEIGHT;
				break;
			}
		case 1:
			{
				logoWidth = TITLE_LOGO1_WIDTH;
				logoHeight = TITLE_LOGO1_HEIGHT;
				break;
			}
		case 2:
			{
				logoWidth = TITLE_LOGO2_WIDTH;
				logoHeight = TITLE_LOGO2_HEIGHT;
				break;
			}
		case 3:
			{
				logoWidth = TITLE_LOGO3_WIDTH;
				logoHeight = TITLE_LOGO3_HEIGHT;
				break;
			}
		case 4:
			{
				logoWidth = TITLE_LOGO4_WIDTH;
				logoHeight = TITLE_LOGO4_HEIGHT;
				break;
			}
		case 5:
			{
				logoWidth = TITLE_LOGO5_WIDTH;
				logoHeight = TITLE_LOGO5_HEIGHT;
				break;
			}
		}

		//���W�ݒ�
		pVtx[cntVtx].pos     = D3DXVECTOR3( - logoWidth / 2 ,   logoHeight / 2 , 0.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3(   logoWidth / 2 ,   logoHeight / 2 , 0.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( - logoWidth / 2 , - logoHeight / 2 , 0.0f );
		pVtx[cntVtx + 3].pos = D3DXVECTOR3(   logoWidth / 2 , - logoHeight / 2 , 0.0f );


		//���_�J���[�ݒ�
		pVtx[cntVtx].col     = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		pVtx[cntVtx + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );

		//�e�N�X�`��
		pVtx[cntVtx].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 3].tex = D3DXVECTOR2( 1 , 1 );
	
		//�@��
		pVtx[cntVtx].nor     = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 1].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 2].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 3].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
	}

	g_pVtxBuffTitle -> Unlock();

	g_Title[0].posTitle = D3DXVECTOR3( -15.0f , 10.0f , 0.0f );
	g_Title[0].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[0].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[1].posTitle = D3DXVECTOR3( -5.0f , 10.0f , 0.0f );
	g_Title[1].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[1].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[2].posTitle = D3DXVECTOR3( 5.0f , -3.0f , 0.0f );
	g_Title[2].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[2].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[3].posTitle = D3DXVECTOR3( 0.0f , 5.0f , 10.0f );
	g_Title[3].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[3].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[4].posTitle = D3DXVECTOR3( 5.0f , 0.0f , 0.0f );
	g_Title[4].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[4].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[5].posTitle = D3DXVECTOR3( 0.0f , -15.0f , 0.0f );
	g_Title[5].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[5].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	

	return S_OK;
}

/******************************************************************************
* �֐����FIninitTitle
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitTitle( void )
{
	for( int cntLogo = 0 ; cntLogo < TITLE_TEX_MAX ; cntLogo++ )
	{
		if( g_pTextureTitle[cntLogo] != NULL )
		{
			g_pTextureTitle[cntLogo] -> Release();
			g_pTextureTitle[cntLogo] = NULL;
		}
	}

	if( g_pVtxBuffTitle !=NULL )
	{
		g_pVtxBuffTitle -> Release();
		g_pVtxBuffTitle = NULL;
	}
}

/******************************************************************************
* �֐����FUpdateTitle
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateTitle( void )
{
	if( GetKeyboardPress( DIK_RETURN ) )
	{
		SetFade( FADE_OUT , MODE_SELECT );
	}
}

/******************************************************************************
* �֐����FDrawTitle
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawTitle( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	for( int cntLogo = 0 ; cntLogo < TITLE_TEX_MAX ; cntLogo++ )
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_mtxWorldTitle );

		D3DXMatrixScaling( &mtxScl , g_Title[cntLogo].sclTitle.x , g_Title[cntLogo].sclTitle.y , g_Title[cntLogo].sclTitle.z );
	
		//�X�P�[���𔽉f
		D3DXMatrixMultiply( &g_mtxWorldTitle , &g_mtxWorldTitle , &mtxScl );

		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Title[cntLogo].rotTitle.x , g_Title[cntLogo].rotTitle.y , g_Title[cntLogo].rotTitle.z );

		//��]�̔��f
		D3DXMatrixMultiply( &g_mtxWorldTitle , &g_mtxWorldTitle , &mtxRot );

		D3DXMatrixTranslation( &mtxTrans , g_Title[cntLogo].posTitle.x , g_Title[cntLogo].posTitle.y , g_Title[cntLogo].posTitle.z );

		//�ړ��̔��f
		D3DXMatrixMultiply( &g_mtxWorldTitle , &g_mtxWorldTitle , &mtxTrans );

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldTitle );

		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetStreamSource( 0 , g_pVtxBuffTitle , 0 , sizeof( VERTEX_3D ));

		//���_�t�H�[�}�b�g
		pDevice -> SetFVF( FVF_VERTEX_3D );

		pDevice -> SetTexture( 0 , g_pTextureTitle[cntLogo] );

		//�A���t�@�e�X�g
		pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
		pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
		pDevice -> SetRenderState( D3DRS_ALPHAREF,0);

		//�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , cntLogo * 4 , 2 );

		//�A���t�@�e�X�g�߂�
		pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
		pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_ALWAYS );
		pDevice -> SetRenderState( D3DRS_ALPHAREF,0);
	}

}
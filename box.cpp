/******************************************************************************
* �^�C�g��  :
* �t�@�C����:box.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/01/21
*******************************************************************************
* �X�V����:-2016/01/21 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureBox[BOX_TEX_MAX];
D3DXMATRIX g_mtxWorldBox;

BOX g_Box[BOX_MAX][BOX_SURFACE_MAX];

/******************************************************************************
* �֐����FInitBox
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitBox( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
		{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( BOX_NUM_VTX ),
														D3DUSAGE_WRITEONLY ,
														FVF_VERTEX_3D ,
														D3DPOOL_MANAGED ,
														&g_Box[cntBox][cntSurface].pVtxBuffBox ,
														NULL ) ) )
			{
				return E_FAIL;
			}
		}
	}

	for( int cntTex = 0 ;  cntTex < BOX_TEX_MAX ; cntTex++ )
	{
		g_pTextureBox[cntTex] = NULL;
	}

	//�e�N�X�`���ǂݍ���
	if( BOX_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/boxNomal001.jpg" , &g_pTextureBox[0] );
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/boxSpring000.jpg" , &g_pTextureBox[1] );
	}


	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{

		for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
		{
			VERTEX_3D *pVtx;
			g_Box[cntBox][cntSurface].pVtxBuffBox -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			g_Box[cntBox][cntSurface].posBox = D3DXVECTOR3( 0.0f , 5.0f , 0.0f );
			g_Box[cntBox][cntSurface].rotBox = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Box[cntBox][cntSurface].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
			g_Box[cntBox][cntSurface].boxUse = false;
			g_Box[cntBox][cntSurface].boxSpringHit = false;

			//���W�ݒ�
			pVtx[0].pos     = D3DXVECTOR3( - BOX_WIDTH / 2 ,   BOX_HEIGHT / 2 , 0.0f );
			pVtx[1].pos = D3DXVECTOR3(   BOX_WIDTH / 2 ,   BOX_HEIGHT / 2 , 0.0f );
			pVtx[2].pos = D3DXVECTOR3( - BOX_WIDTH / 2 , - BOX_HEIGHT / 2 , 0.0f );
			pVtx[3].pos = D3DXVECTOR3(   BOX_WIDTH / 2 , - BOX_HEIGHT / 2 , 0.0f );


			//���_�J���[�ݒ�
			for( int cntCol = 0 ; cntCol < BOX_NUM_VTX ; cntCol++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 100 , 100, 255 );
			}

			//�e�N�X�`��
			pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
			pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
			pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
			pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
			//�@��
			for( int cntNor = 0 ; cntNor < BOX_NUM_VTX ; cntNor++ )
			{
				pVtx[cntNor].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
			}

			g_Box[cntBox][cntSurface].pVtxBuffBox -> Unlock();

		}

		//��O
		g_Box[cntBox][0].posBox = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Box[cntBox][0].rotBox = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Box[cntBox][0].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Box[cntBox][1].posBox = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Box[cntBox][1].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][1].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//�E
		g_Box[cntBox][2].posBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][2].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][2].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Box[cntBox][3].posBox = D3DXVECTOR3( 0, 0.0f , 0.0f );
		g_Box[cntBox][3].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][3].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Box[cntBox][4].posBox = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Box[cntBox][4].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][4].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Box[cntBox][5].posBox = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Box[cntBox][5].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][5].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	}

	return S_OK;
}

/******************************************************************************
* �֐����FUninitBox
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitBox( void )
{
	for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
	{
		for( int cntTex = 0 ;  cntTex < BOX_TEX_MAX ; cntTex++ )
		{
			if( g_pTextureBox[cntTex] != NULL )
			{
				g_pTextureBox[cntTex] -> Release();
				g_pTextureBox[cntTex] = NULL;
			}
		}
	}

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
		{
			if( g_Box[cntBox][cntSurface].pVtxBuffBox !=NULL )
			{
				g_Box[cntBox][cntSurface].pVtxBuffBox -> Release();
				g_Box[cntBox][cntSurface].pVtxBuffBox = NULL;
			}
		}
	}
}

/******************************************************************************
* �֐����FUpdateBox
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateBox( void )
{

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		VERTEX_3D *pVtx;
		g_Box[cntBox][0].pVtxBuffBox -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		switch( g_Box[cntBox][0].boxPattarn )
		{
		case BOX_NOMAL:
			{
				if( g_Box[cntBox][0].boxUse == false )//����
				{

					for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
					{
						g_Box[cntBox][cntSurface].boxUse = false;
					}
				}
				break;
			}
		case BOX_SPRING:
			{
				break;
			}
			}
		g_Box[cntBox][0].pVtxBuffBox -> Unlock();
	}
}

/******************************************************************************
* �֐����FDrawBox
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawBox( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		if( g_Box[cntBox][0].boxUse == true )
		{
			for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity( &g_mtxWorldBox );

				D3DXMatrixScaling( &mtxScl , g_Box[cntBox][cntSurface].sclBox.x , g_Box[cntBox][cntSurface].sclBox.y , g_Box[cntBox][cntSurface].sclBox.z );
	
				//�X�P�[���𔽉f
				D3DXMatrixMultiply( &g_mtxWorldBox , &g_mtxWorldBox , &mtxScl );

				D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Box[cntBox][cntSurface].rotBox.x , g_Box[cntBox][cntSurface].rotBox.y , g_Box[cntBox][cntSurface].rotBox.z );

				//��]�̔��f
				D3DXMatrixMultiply( &g_mtxWorldBox , &g_mtxWorldBox , &mtxRot );

				D3DXMatrixTranslation( &mtxTrans , g_Box[cntBox][cntSurface].posBox.x , g_Box[cntBox][cntSurface].posBox.y , g_Box[cntBox][cntSurface].posBox.z );

				//�ړ��̔��f
				D3DXMatrixMultiply( &g_mtxWorldBox , &g_mtxWorldBox , &mtxTrans );

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldBox );

				//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource( 0 , g_Box[cntBox][cntSurface].pVtxBuffBox , 0 , sizeof( VERTEX_3D ));

				//���_�t�H�[�}�b�g
				pDevice -> SetFVF( FVF_VERTEX_3D );


				//�e�N�X�`���̐؂�ւ�
				switch( g_Box[cntBox][cntSurface].boxPattarn )
				{
				case BOX_NOMAL:
					{
						pDevice -> SetTexture( 0 , g_pTextureBox[0] );
						break;
					}
				case BOX_SPRING:
					{
						pDevice -> SetTexture( 0 , g_pTextureBox[1] );
						break;
					}
				}

				//�|���S���̕`��
				pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
				
			}
		}
	}
}

/******************************************************************************
* �֐����FSetBox
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetBox( D3DXVECTOR3 pos , BOXPATTARN boxPattarn )
{
	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		if( g_Box[cntBox][0].boxUse == false )
		{
			g_Box[cntBox][0].setPosBox = pos;

			//��O
			g_Box[cntBox][0].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z - BOX_HEIGHT / 2 );
			g_Box[cntBox][0].rotBox = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Box[cntBox][0].boxPattarn = boxPattarn;

			//��
			g_Box[cntBox][1].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z + BOX_HEIGHT / 2 );
			g_Box[cntBox][1].rotBox = D3DXVECTOR3( D3DX_PI * 1.0f , 0.0f , 0.0f );
			g_Box[cntBox][1].boxPattarn = boxPattarn;

			//�E
			g_Box[cntBox][2].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x + BOX_WIDTH / 2 , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][2].rotBox = D3DXVECTOR3( -D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Box[cntBox][2].boxPattarn = boxPattarn;

			//��
			g_Box[cntBox][3].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x - BOX_WIDTH / 2 , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][3].rotBox = D3DXVECTOR3( D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Box[cntBox][3].boxPattarn = boxPattarn;

			//��
			g_Box[cntBox][4].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y + BOX_HEIGHT / 2 , g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][4].rotBox = D3DXVECTOR3( 0.0f , D3DX_PI * 0.5f , 0.0f );
			g_Box[cntBox][4].boxPattarn = boxPattarn;

			//��
			g_Box[cntBox][5].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y  - BOX_HEIGHT / 2, g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][5].rotBox = D3DXVECTOR3( 0.0f , -D3DX_PI * 0.5f , 0.0f );
			g_Box[cntBox][5].boxPattarn = boxPattarn;

			for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
			{
				g_Box[cntBox][cntSurface].boxUse = true;
			}
			
			//�ǂ񂮂肹����
			if( g_Box[cntBox][0].boxPattarn == BOX_NOMAL )
			{
				SetAcorn( D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x + 5, g_Box[cntBox][0].setPosBox.y - BOX_HEIGHT / 2 , g_Box[cntBox][0].setPosBox.z ) );
				SetAcorn( D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y - BOX_HEIGHT / 2, g_Box[cntBox][0].setPosBox.z ) );
				SetAcorn( D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x - 5, g_Box[cntBox][0].setPosBox.y - BOX_HEIGHT / 2, g_Box[cntBox][0].setPosBox.z ) );
			}

			//�e�ݒu
			SetShadow( g_Box[cntBox][0].posBox , SHADOW_BOX );
			break;
		}
	}
}

/******************************************************************************
* �֐����FGetModel
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
BOX *GetBox( void )
{
	return &g_Box[0][0];
}
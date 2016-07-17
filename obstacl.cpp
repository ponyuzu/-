/******************************************************************************
* �^�C�g��  :
* �t�@�C����:obstacl.cpp
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
LPDIRECT3DTEXTURE9 g_pTextureObstacl = NULL;
D3DXMATRIX g_mtxWorldObstacl;

OBSTACL g_Obstacl[OBSTACL_MAX][OBSTACL_SURFACE_MAX];

/******************************************************************************
* �֐����FInitObstacl
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitObstacl( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{

		for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
		{

			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( OBSTACL_NUM_VTX ),
														D3DUSAGE_WRITEONLY ,
														FVF_VERTEX_3D ,
														D3DPOOL_MANAGED ,
														&g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl ,
														NULL ) ) )
			{
				return E_FAIL;
			}

		}
	}

	g_pTextureObstacl = NULL;

	//�e�N�X�`���ǂݍ���
	if( OBSTACL_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/obstacl002.jpg" , &g_pTextureObstacl );
	}

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{
		for( int cntSurface = 0  ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++  )
		{
			VERTEX_3D *pVtx;
			g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );


			g_Obstacl[cntObstacl][cntSurface].posObstacl = D3DXVECTOR3( 0.0f , 5.0f , 0.0f );
			g_Obstacl[cntObstacl][cntSurface].rotObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][cntSurface].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
			g_Obstacl[cntObstacl][cntSurface].obstaclUse = false;

			//���W�ݒ�
			pVtx[0].pos     = D3DXVECTOR3( - OBSTACL_WIDTH / 2 ,   OBSTACL_HEIGHT / 2 , 0.0f );
			pVtx[1].pos = D3DXVECTOR3(   OBSTACL_WIDTH / 2 ,   OBSTACL_HEIGHT / 2 , 0.0f );
			pVtx[2].pos = D3DXVECTOR3( - OBSTACL_WIDTH / 2 , - OBSTACL_HEIGHT / 2 , 0.0f );
			pVtx[3].pos = D3DXVECTOR3(   OBSTACL_WIDTH / 2 , - OBSTACL_HEIGHT / 2 , 0.0f );


			//���_�J���[�ݒ�
			for( int cntCol = 0 ; cntCol < OBSTACL_NUM_VTX ; cntCol++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 100 , 100 , 100, 255 );
			}

			//�e�N�X�`��
			pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
			pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
			pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
			pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
			//�@��
			for( int cntNor = 0 ; cntNor < OBSTACL_NUM_VTX ; cntNor++ )
			{
				pVtx[cntNor].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
			}
			g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl -> Unlock();
		}

		//��O
		g_Obstacl[cntObstacl][0].posObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Obstacl[cntObstacl][0].rotObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][0].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Obstacl[cntObstacl][1].posObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Obstacl[cntObstacl][1].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][1].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//�E
		g_Obstacl[cntObstacl][2].posObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][2].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][2].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Obstacl[cntObstacl][3].posObstacl = D3DXVECTOR3( 0, 0.0f , 0.0f );
		g_Obstacl[cntObstacl][3].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][3].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Obstacl[cntObstacl][4].posObstacl = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Obstacl[cntObstacl][4].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][4].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//��
		g_Obstacl[cntObstacl][5].posObstacl = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Obstacl[cntObstacl][5].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][5].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	}

	return S_OK;
}

/******************************************************************************
* �֐����FUninitObstacl
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitObstacl( void )
{
	for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
	{
		if( g_pTextureObstacl != NULL )
		{
			g_pTextureObstacl -> Release();
			g_pTextureObstacl = NULL;
		}
	}

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{

		for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
		{
			if( g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl !=NULL )
			{
				g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl -> Release();
				g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl = NULL;
			}
		}
	}
}

/******************************************************************************
* �֐����FUpdateObstacl
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateObstacl( void )
{


}

/******************************************************************************
* �֐����FDrawObstacl
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawObstacl( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{
		for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
		{
			if( g_Obstacl[cntObstacl][cntSurface].obstaclUse == true )
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity( &g_mtxWorldObstacl );

				D3DXMatrixScaling( &mtxScl , g_Obstacl[cntObstacl][cntSurface].sclObstacl.x , g_Obstacl[cntObstacl][cntSurface].sclObstacl.y , g_Obstacl[cntObstacl][cntSurface].sclObstacl.z );
	
				//�X�P�[���𔽉f
				D3DXMatrixMultiply( &g_mtxWorldObstacl , &g_mtxWorldObstacl , &mtxScl );

				D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Obstacl[cntObstacl][cntSurface].rotObstacl.x , g_Obstacl[cntObstacl][cntSurface].rotObstacl.y , g_Obstacl[cntObstacl][cntSurface].rotObstacl.z );

				//��]�̔��f
				D3DXMatrixMultiply( &g_mtxWorldObstacl , &g_mtxWorldObstacl , &mtxRot );

				D3DXMatrixTranslation( &mtxTrans , g_Obstacl[cntObstacl][cntSurface].posObstacl.x , g_Obstacl[cntObstacl][cntSurface].posObstacl.y , g_Obstacl[cntObstacl][cntSurface].posObstacl.z );

				//�ړ��̔��f
				D3DXMatrixMultiply( &g_mtxWorldObstacl , &g_mtxWorldObstacl , &mtxTrans );

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldObstacl );

				//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
				pDevice -> SetStreamSource( 0 , g_Obstacl[cntObstacl][cntObstacl].pVtxBuffObstacl , 0 , sizeof( VERTEX_3D ));

				//���_�t�H�[�}�b�g
				pDevice -> SetFVF( FVF_VERTEX_3D );

				pDevice -> SetTexture( 0 , g_pTextureObstacl );

				//�|���S���̕`��
				pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );

			}
		}
	}
}

/******************************************************************************
* �֐����FSetObstacl
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetObstacl( D3DXVECTOR3 pos , OBSTACLPATTARN obstaclPattarn )
{
	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{
		if( g_Obstacl[cntObstacl][0].obstaclUse == false )
		{
			g_Obstacl[cntObstacl][0].setPosObstacl = pos;
			g_Obstacl[cntObstacl][0].obstaclPattarn = obstaclPattarn;

			//��O
			g_Obstacl[cntObstacl][0].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z - OBSTACL_HEIGHT / 2 );
			g_Obstacl[cntObstacl][0].rotObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][0].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//��
			g_Obstacl[cntObstacl][1].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z + OBSTACL_HEIGHT / 2 );
			g_Obstacl[cntObstacl][1].rotObstacl = D3DXVECTOR3( D3DX_PI * 1.0f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][1].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//�E
			g_Obstacl[cntObstacl][2].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x + OBSTACL_WIDTH / 2 , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][2].rotObstacl = D3DXVECTOR3( -D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][2].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//��
			g_Obstacl[cntObstacl][3].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x - OBSTACL_WIDTH / 2 , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][3].rotObstacl = D3DXVECTOR3( D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][3].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//��
			g_Obstacl[cntObstacl][4].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y + OBSTACL_HEIGHT / 2 , g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][4].rotObstacl = D3DXVECTOR3( 0.0f , D3DX_PI * 0.5f , 0.0f );
			g_Obstacl[cntObstacl][4].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//��
			g_Obstacl[cntObstacl][5].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y  - OBSTACL_HEIGHT / 2, g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][5].rotObstacl = D3DXVECTOR3( 0.0f , -D3DX_PI * 0.5f , 0.0f );
			g_Obstacl[cntObstacl][5].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
			{
				g_Obstacl[cntObstacl][cntSurface].obstaclUse = true;
			}
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
OBSTACL *GetObstacl( void )
{
	return &g_Obstacl[0][0];
}
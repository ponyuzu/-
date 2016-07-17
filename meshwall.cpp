/******************************************************************************
* �^�C�g��  :
* �t�@�C����:meshwall.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/11/10
*******************************************************************************
* �X�V����:-2015/11/10 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPDIRECT3DVERTEXBUFFER9 pVtxBuffWall = NULL;//���_�o�b�t�@
LPDIRECT3DINDEXBUFFER9 pIdxBuffWall = NULL ;//�C���f�b�N�X�o�b�t�@
LPDIRECT3DTEXTURE9 pTextureWall = NULL;
D3DXMATRIX mtxWorldWall;

WALL g_wall[WALL_MAX];

/******************************************************************************
* �֐����FInitWall
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitWall( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( WALL_NUM_VTX * WALL_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_3D ,
												D3DPOOL_MANAGED ,
												&pVtxBuffWall ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	pDevice ->CreateIndexBuffer( sizeof( WORD ) * ( WALL_NUM_INDEX * WALL_MAX ),
								D3DUSAGE_WRITEONLY ,
								D3DFMT_INDEX16 ,
								D3DPOOL_MANAGED ,
								&pIdxBuffWall ,
								NULL);

	pTextureWall = NULL;

	//�e�N�X�`���ǂݍ���
	if( WALL_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/akira000.png" , &pTextureWall );
	}

	VERTEX_3D *pVtx;
	pVtxBuffWall -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntWall = 0 , cntVtx = 0 ; cntWall < WALL_MAX ; cntWall++ , cntVtx += 9 )
	{
		//���W�ݒ�
		pVtx[cntVtx].pos = D3DXVECTOR3( -200.0f , 80.0f , 50.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3( 0.0f , 80.0f , 50.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( 200.0f , 80.0f , 50.0f );

		pVtx[cntVtx + 3].pos = D3DXVECTOR3( -200.0f , 50.0f , 0.0f );
		pVtx[cntVtx + 4].pos = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );
		pVtx[cntVtx + 5].pos = D3DXVECTOR3( 200.0f , 50.0f , 0.0f );

		pVtx[cntVtx + 6].pos = D3DXVECTOR3( -200.0f , 0.0f , 0.0f );
		pVtx[cntVtx + 7].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[cntVtx + 8].pos = D3DXVECTOR3( 200.0f , 0.0f , 0.0f );


		//���_�J���[�ݒ�
		for( int cntCol = 0 ; cntCol < WALL_NUM_VTX ; cntCol++ )
		{
			pVtx[cntVtx + cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		}

		//�e�N�X�`��
		pVtx[cntVtx].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( 0.5 , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 1 , 0 );

		pVtx[cntVtx + 3].tex = D3DXVECTOR2( 0 , 0.5 );
		pVtx[cntVtx + 4].tex = D3DXVECTOR2( 0.5 , 0.5 );
		pVtx[cntVtx + 5].tex = D3DXVECTOR2( 1 , 0.5 );

		pVtx[cntVtx + 6].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 7].tex = D3DXVECTOR2( 0.5 , 1 );
		pVtx[cntVtx + 8].tex = D3DXVECTOR2( 1 , 1 );

		//�@��
		for( int cntNml = 0 ; cntNml < WALL_NUM_VTX ; cntNml++ )
		{
			pVtx[cntVtx + cntNml].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		}
	}

	pVtxBuffWall -> Unlock();

	WORD *pIndex;
	pIdxBuffWall -> Lock( 0 , 0 ,( void** )&pIndex ,0 );

	//�C���f�b�N�X
	for( int cntWall = 0 , cntIdx = 0 ; cntWall < WALL_MAX ; cntWall++ , cntIdx += WALL_NUM_INDEX )
	{
		int CntIdxWall = 0;//�C���f�b�N�X�̃J�E���g

		for(int yCnt = 1 ; yCnt <= WALL_Y ; yCnt++ )//���s���܂킷
		{
			for( int xCnt = 0 , p = 0 , q = 0 ; xCnt <= ( WALL_X + 1 ) * 2 - 1; xCnt++ )//x�s���܂킷
			{
				switch( xCnt % 2 )//������ŕ�����
				{
				case 0:
					{
						pIndex[ cntIdx + CntIdxWall] = yCnt * ( WALL_X + 1 ) + p;//�����̎��̒l������
						p++;

						break;
					}
				case 1:
					{
						pIndex[ cntIdx + CntIdxWall] = ( yCnt - 1 ) * ( WALL_X + 1 ) + q;//��̎��̒l������
						q++;

						break;
					}
				}
				CntIdxWall++;
			}
			if( CntIdxWall < WALL_NUM_INDEX )
			{
				pIndex[ cntIdx + CntIdxWall] = pIndex[ CntIdxWall - 1];
				CntIdxWall++;
				pIndex[ cntIdx + CntIdxWall] = pIndex[ CntIdxWall - 3] + 1;
				CntIdxWall++;
			}

		}
	}
	
	pIdxBuffWall -> Unlock();

	g_wall[0].posWall = D3DXVECTOR3( 0.0f , 0.0f , FIELD_HEIGTH * FIELD_Z / 2);
	g_wall[0].rotWall = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_wall[0].sclWall = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_wall[1].posWall = D3DXVECTOR3( -FIELD_WIDHT * FIELD_X / 2 , 0.0f , 0.0f );
	g_wall[1].rotWall = D3DXVECTOR3( -D3DX_PI * 0.5f , 0.0f , 0.0f );
	g_wall[1].sclWall = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_wall[2].posWall = D3DXVECTOR3( FIELD_WIDHT * FIELD_X / 2 , 0.0f , 0.0f );
	g_wall[2].rotWall = D3DXVECTOR3( D3DX_PI * 0.5f , 0.0f , 0.0f );
	g_wall[2].sclWall = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_wall[3].posWall = D3DXVECTOR3( 0.0f , 0.0f , -FIELD_HEIGTH * FIELD_Z / 2);
	g_wall[3].rotWall = D3DXVECTOR3( D3DX_PI * 1.0f , 0.0f , 0.0f );
	g_wall[3].sclWall = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	return S_OK;
}

/******************************************************************************
* �֐����FUninitWall
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitWall( void )
{
	//for( int cntWall = 0 ; cntWall < WALL_MAX ; cntWall++ )
	{
		if( pTextureWall != NULL )
		{
			pTextureWall -> Release();
			pTextureWall = NULL;
		}

		if( pVtxBuffWall !=NULL )
		{
			pVtxBuffWall -> Release();
			pVtxBuffWall = NULL;
		}
	
		if( pIdxBuffWall != NULL )
		{
			pIdxBuffWall -> Release();
			pIdxBuffWall = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateWall
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateWall( void )
{
}


/******************************************************************************
* �֐����FDrawWall
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawWall( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntWall = 0 , cntIdx = 0  ; cntWall < WALL_MAX ; cntWall++ , cntIdx += WALL_NUM_INDEX )
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &mtxWorldWall );

		D3DXMatrixScaling( &mtxScl , g_wall[cntWall].sclWall.x , g_wall[cntWall].sclWall.y , g_wall[cntWall].sclWall.z );
	
		//�X�P�[���𔽉f
		D3DXMatrixMultiply( &mtxWorldWall , &mtxWorldWall , &mtxScl );

		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_wall[cntWall].rotWall.x , g_wall[cntWall].rotWall.y , g_wall[cntWall].rotWall.z );

		//��]�̔��f
		D3DXMatrixMultiply( &mtxWorldWall , &mtxWorldWall , &mtxRot );

		D3DXMatrixTranslation( &mtxTrans , g_wall[cntWall].posWall.x , g_wall[cntWall].posWall.y , g_wall[cntWall].posWall.z );

		//�ړ��̔��f
		D3DXMatrixMultiply( &mtxWorldWall , &mtxWorldWall , &mtxTrans );

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice ->SetTransform( D3DTS_WORLD , &mtxWorldWall );

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetIndices( pIdxBuffWall );

		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetStreamSource( 0 , pVtxBuffWall , 0 , sizeof( VERTEX_3D ));

		//���_�t�H�[�}�b�g
		pDevice -> SetFVF( FVF_VERTEX_3D );

		pDevice -> SetTexture( 0 , pTextureWall );

		//�|���S���̕`��
		pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , WALL_NUM_VTX , cntIdx ,WALL_NUM_PORIGON );
	}
	
}
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:meshsky.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/23
*******************************************************************************
* �X�V����:-2015/10/23 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;
D3DXMATRIX g_mtxWorldSky;

SKY g_Sky[SKY_MAX];

/******************************************************************************
* �֐����FInitSky
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitSky( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * SKY_NUM_VTX,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_3D ,
													D3DPOOL_MANAGED ,
													&g_Sky[cntSky].pVtxBuffSky ,
													NULL ) ) )
		{
			return E_FAIL;
		}

				pDevice ->CreateIndexBuffer( sizeof(WORD) * SKY_NUM_INDEX,
									D3DUSAGE_WRITEONLY ,
									D3DFMT_INDEX16 ,
									D3DPOOL_MANAGED ,
									&g_Sky[cntSky].pIdxBuffSky ,
									NULL);
	}

	g_pTextureSky = NULL;

	//�e�N�X�`���ǂݍ���
	if( SKY_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , SKY_TEX , &g_pTextureSky );
	}


	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		VERTEX_3D *pVtx;
		g_Sky[cntSky].pVtxBuffSky -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//���W�ݒ�
		int cntVtx = 0;

		for( int tate = SKY_Z / 2 , cntTate = 0; cntTate <= SKY_Z ; tate-- , cntTate++ )
		{
			for( int yoko = -SKY_X / 2 , cntYoko = 0 ; cntYoko <= SKY_X ; yoko++ , cntYoko++ )
			{
				pVtx[cntVtx].pos = D3DXVECTOR3( SKY_WIDHT * yoko , 0.0f , SKY_HEIGTH * tate );

				cntVtx++;
			}
		}

		//���_�J���[�ݒ�
		for( int cntCol = 0 ; cntCol < SKY_NUM_VTX ; cntCol++ )
		{
			pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		}

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 0.5 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 1 , 0 );

		pVtx[3].tex = D3DXVECTOR2( 0 , 0.5 );
		pVtx[4].tex = D3DXVECTOR2( 0.5 , 0.5 );
		pVtx[5].tex = D3DXVECTOR2( 1 , 0.5 );

		pVtx[6].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[7].tex = D3DXVECTOR2( 0.5 , 1 );
		pVtx[8].tex = D3DXVECTOR2( 1 , 1 );
	
		//�@��
		for( int cntNml = 0 ;  cntNml < SKY_NUM_VTX ; cntNml++ )
		{
			pVtx[cntNml].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		}

		g_Sky[cntSky].pVtxBuffSky -> Unlock();
	}

	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		WORD *pIndex;
		g_Sky[cntSky].pIdxBuffSky -> Lock( 0 , 0 ,( void** )&pIndex ,0 );

		int cntIdx = 0;

		//�C���f�b�N�X
		for(int zCnt = 1 ; zCnt <= SKY_Z ; zCnt++ )//���s���܂킷
		{
			for( int xCnt = 0, p = 0 , q = 0 ; xCnt <= ( SKY_X + 1 ) * 2 - 1; xCnt++ )//x�s���܂킷
			{
				switch( xCnt % 2 )//������ŕ�����
				{
				case 0:
					{
						pIndex[cntIdx] = zCnt * ( SKY_X + 1 ) + p;//�����̎��̒l������
						p++;

						break;
					}
				case 1:
					{
						pIndex[cntIdx] = ( zCnt - 1 ) * ( SKY_X + 1 ) + q;//��̎��̒l������
						q++;

						break;
					}
				}
				cntIdx++;
			}
			if( cntIdx < SKY_NUM_INDEX )
			{
				pIndex[cntIdx] = pIndex[cntIdx - 1];
				cntIdx++;
				pIndex[cntIdx] = pIndex[cntIdx - 3] + 1;
				cntIdx++;
			}

		}

	g_Sky[cntSky].posSky = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Sky[cntSky].rotSky = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Sky[cntSky].sclSky = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		g_Sky[cntSky].pIdxBuffSky -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* �֐����FUninitSky
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitSky( void )
{
	if( g_pTextureSky != NULL )
	{
		g_pTextureSky -> Release();
		g_pTextureSky = NULL;
	}

	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		if( g_Sky[cntSky].pVtxBuffSky !=NULL )
		{
			g_Sky[cntSky].pVtxBuffSky -> Release();
			g_Sky[cntSky].pVtxBuffSky = NULL;
		}

		if( g_Sky[cntSky].pIdxBuffSky !=NULL )
		{
			g_Sky[cntSky].pIdxBuffSky -> Release();
			g_Sky[cntSky].pIdxBuffSky = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateSky
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateSky( void )
{
	/*VERTEX_3D *pVtx;
	g_Sky[SKY_MAX].pVtxBuffSky -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	pVtx[4].pos = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );

	g_Sky[SKY_MAX].pVtxBuffSky -> Unlock();*/
}


/******************************************************************************
* �֐����FDrawSky
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawSky( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		if( g_Sky[cntSky].useSky == true )
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_mtxWorldSky );

			D3DXMatrixScaling( &mtxScl , g_Sky[cntSky].sclSky.x , g_Sky[cntSky].sclSky.y , g_Sky[cntSky].sclSky.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldSky , &g_mtxWorldSky , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Sky[cntSky].rotSky.x , g_Sky[cntSky].rotSky.y , g_Sky[cntSky].rotSky.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldSky , &g_mtxWorldSky , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Sky[cntSky].posSky.x , g_Sky[cntSky].posSky.y , g_Sky[cntSky].posSky.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldSky , &g_mtxWorldSky , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldSky );

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetIndices( g_Sky[cntSky].pIdxBuffSky );

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_Sky[cntSky].pVtxBuffSky , 0 , sizeof( VERTEX_3D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureSky );

			//�|���S���̕`��
			pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , SKY_NUM_VTX , 0 ,SKY_NUM_PORIGON );
		}
	}
}

/******************************************************************************
* �֐����FGetSky
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
SKY *GetSky( void )
{
	return &g_Sky[0];
}

/******************************************************************************
* �֐����FSetSky
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetSky( D3DXVECTOR3 pos )
{
	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		if( g_Sky[cntSky].useSky == false )
		{
			g_Sky[cntSky].posSky = pos;
			g_Sky[cntSky].useSky = true;

			break;
		}
	}
}
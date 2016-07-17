/******************************************************************************
* �^�C�g��  :
* �t�@�C����:meshfield.cpp
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
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;
D3DXMATRIX g_mtxWorldField;

FIELD g_Field[FIELD_MAX];

/******************************************************************************
* �֐����FInitField
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitField( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * FIELD_NUM_VTX,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_3D ,
													D3DPOOL_MANAGED ,
													&g_Field[cntField].pVtxBuffField ,
													NULL ) ) )
		{
			return E_FAIL;
		}

				pDevice ->CreateIndexBuffer( sizeof(WORD) * FIELD_NUM_INDEX,
									D3DUSAGE_WRITEONLY ,
									D3DFMT_INDEX16 ,
									D3DPOOL_MANAGED ,
									&g_Field[cntField].pIdxBuffField ,
									NULL);
	}

	g_pTextureField = NULL;

	//�e�N�X�`���ǂݍ���
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , FIELD_TEX , &g_pTextureField );
	}


	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		VERTEX_3D *pVtx;
		g_Field[cntField].pVtxBuffField -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//���W�ݒ�
		int cntVtx = 0;

		for( int tate = FIELD_Z / 2 , cntTate = 0; cntTate <= FIELD_Z ; tate-- , cntTate++ )
		{
			for( int yoko = -FIELD_X / 2 , cntYoko = 0 ; cntYoko <= FIELD_X ; yoko++ , cntYoko++ )
			{
				pVtx[cntVtx].pos = D3DXVECTOR3( FIELD_WIDHT * yoko , 0.0f , FIELD_HEIGTH * tate );

				cntVtx++;
			}
		}

		//���_�J���[�ݒ�
		for( int cntCol = 0 ; cntCol < FIELD_NUM_VTX ; cntCol++ )
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
		for( int cntNml = 0 ;  cntNml < FIELD_NUM_VTX ; cntNml++ )
		{
			pVtx[cntNml].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		}

		g_Field[cntField].pVtxBuffField -> Unlock();
	}

	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		WORD *pIndex;
		g_Field[cntField].pIdxBuffField -> Lock( 0 , 0 ,( void** )&pIndex ,0 );

		int cntIdx = 0;

		//�C���f�b�N�X
		for(int zCnt = 1 ; zCnt <= FIELD_Z ; zCnt++ )//���s���܂킷
		{
			for( int xCnt = 0, p = 0 , q = 0 ; xCnt <= ( FIELD_X + 1 ) * 2 - 1; xCnt++ )//x�s���܂킷
			{
				switch( xCnt % 2 )//������ŕ�����
				{
				case 0:
					{
						pIndex[cntIdx] = zCnt * ( FIELD_X + 1 ) + p;//�����̎��̒l������
						p++;

						break;
					}
				case 1:
					{
						pIndex[cntIdx] = ( zCnt - 1 ) * ( FIELD_X + 1 ) + q;//��̎��̒l������
						q++;

						break;
					}
				}
				cntIdx++;
			}
			if( cntIdx < FIELD_NUM_INDEX )
			{
				pIndex[cntIdx] = pIndex[cntIdx - 1];
				cntIdx++;
				pIndex[cntIdx] = pIndex[cntIdx - 3] + 1;
				cntIdx++;
			}

		}

	g_Field[cntField].posField = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Field[cntField].rotField = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Field[cntField].sclField = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	g_Field[cntField].useField = false;

		g_Field[cntField].pIdxBuffField -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* �֐����FUninitField
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitField( void )
{
	if( g_pTextureField != NULL )
	{
		g_pTextureField -> Release();
		g_pTextureField = NULL;
	}

	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		if( g_Field[cntField].pVtxBuffField !=NULL )
		{
			g_Field[cntField].pVtxBuffField -> Release();
			g_Field[cntField].pVtxBuffField = NULL;
		}

		if( g_Field[cntField].pIdxBuffField !=NULL )
		{
			g_Field[cntField].pIdxBuffField -> Release();
			g_Field[cntField].pIdxBuffField = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateField
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateField( void )
{
	/*VERTEX_3D *pVtx;
	g_Field[FIELD_MAX].pVtxBuffField -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	pVtx[4].pos = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );

	g_Field[FIELD_MAX].pVtxBuffField -> Unlock();*/
}


/******************************************************************************
* �֐����FDrawField
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawField( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		if( g_Field[cntField].useField == true )
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_mtxWorldField );

			D3DXMatrixScaling( &mtxScl , g_Field[cntField].sclField.x , g_Field[cntField].sclField.y , g_Field[cntField].sclField.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldField , &g_mtxWorldField , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Field[cntField].rotField.x , g_Field[cntField].rotField.y , g_Field[cntField].rotField.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldField , &g_mtxWorldField , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Field[cntField].posField.x , g_Field[cntField].posField.y , g_Field[cntField].posField.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldField , &g_mtxWorldField , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldField );

			//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetIndices( g_Field[cntField].pIdxBuffField );

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_Field[cntField].pVtxBuffField , 0 , sizeof( VERTEX_3D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureField );

			//�|���S���̕`��
			pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , FIELD_NUM_VTX , 0 ,FIELD_NUM_PORIGON );
		}
	}
}

/******************************************************************************
* �֐����FGetField
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
FIELD *GetField( void )
{
	return &g_Field[0];
}

/******************************************************************************
* �֐����FSetField
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetField( D3DXVECTOR3 pos )
{
	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		if( g_Field[cntField].useField == false )
		{
			g_Field[cntField].posField = pos;
			g_Field[cntField].useField = true;

			break;
		}
	}
}
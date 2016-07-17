/******************************************************************************
* タイトル  :
* ファイル名:meshfield.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/23
*******************************************************************************
* 更新履歴:-2015/10/23 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;
D3DXMATRIX g_mtxWorldField;

FIELD g_Field[FIELD_MAX];

/******************************************************************************
* 関数名：InitField
* 
* 引数  ：
* 戻り値：
* 説明  ：
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

	//テクスチャ読み込み
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , FIELD_TEX , &g_pTextureField );
	}


	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		VERTEX_3D *pVtx;
		g_Field[cntField].pVtxBuffField -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//座標設定
		int cntVtx = 0;

		for( int tate = FIELD_Z / 2 , cntTate = 0; cntTate <= FIELD_Z ; tate-- , cntTate++ )
		{
			for( int yoko = -FIELD_X / 2 , cntYoko = 0 ; cntYoko <= FIELD_X ; yoko++ , cntYoko++ )
			{
				pVtx[cntVtx].pos = D3DXVECTOR3( FIELD_WIDHT * yoko , 0.0f , FIELD_HEIGTH * tate );

				cntVtx++;
			}
		}

		//頂点カラー設定
		for( int cntCol = 0 ; cntCol < FIELD_NUM_VTX ; cntCol++ )
		{
			pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		}

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 0.5 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 1 , 0 );

		pVtx[3].tex = D3DXVECTOR2( 0 , 0.5 );
		pVtx[4].tex = D3DXVECTOR2( 0.5 , 0.5 );
		pVtx[5].tex = D3DXVECTOR2( 1 , 0.5 );

		pVtx[6].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[7].tex = D3DXVECTOR2( 0.5 , 1 );
		pVtx[8].tex = D3DXVECTOR2( 1 , 1 );
	
		//法線
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

		//インデックス
		for(int zCnt = 1 ; zCnt <= FIELD_Z ; zCnt++ )//ｚ行分まわす
		{
			for( int xCnt = 0, p = 0 , q = 0 ; xCnt <= ( FIELD_X + 1 ) * 2 - 1; xCnt++ )//x行分まわす
			{
				switch( xCnt % 2 )//奇数偶数で分ける
				{
				case 0:
					{
						pIndex[cntIdx] = zCnt * ( FIELD_X + 1 ) + p;//偶数の時の値を入れる
						p++;

						break;
					}
				case 1:
					{
						pIndex[cntIdx] = ( zCnt - 1 ) * ( FIELD_X + 1 ) + q;//奇数の時の値を入れる
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
* 関数名：UninitField
* 
* 引数  ：
* 戻り値：
* 説明  ：
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
* 関数名：UpdateField
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateField( void )
{
	/*VERTEX_3D *pVtx;
	g_Field[FIELD_MAX].pVtxBuffField -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	pVtx[4].pos = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );

	g_Field[FIELD_MAX].pVtxBuffField -> Unlock();*/
}


/******************************************************************************
* 関数名：DrawField
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawField( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntField = 0 ; cntField < FIELD_MAX ; cntField++ )
	{
		if( g_Field[cntField].useField == true )
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_mtxWorldField );

			D3DXMatrixScaling( &mtxScl , g_Field[cntField].sclField.x , g_Field[cntField].sclField.y , g_Field[cntField].sclField.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldField , &g_mtxWorldField , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Field[cntField].rotField.x , g_Field[cntField].rotField.y , g_Field[cntField].rotField.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldField , &g_mtxWorldField , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Field[cntField].posField.x , g_Field[cntField].posField.y , g_Field[cntField].posField.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldField , &g_mtxWorldField , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldField );

			//インデックスバッファをデータストリームにバインド
			pDevice -> SetIndices( g_Field[cntField].pIdxBuffField );

			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_Field[cntField].pVtxBuffField , 0 , sizeof( VERTEX_3D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureField );

			//ポリゴンの描画
			pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , FIELD_NUM_VTX , 0 ,FIELD_NUM_PORIGON );
		}
	}
}

/******************************************************************************
* 関数名：GetField
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
FIELD *GetField( void )
{
	return &g_Field[0];
}

/******************************************************************************
* 関数名：SetField
* 
* 引数  ：
* 戻り値：
* 説明  ：
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
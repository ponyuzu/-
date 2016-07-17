/******************************************************************************
* タイトル  :
* ファイル名:meshsky.cpp
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
LPDIRECT3DTEXTURE9 g_pTextureSky = NULL;
D3DXMATRIX g_mtxWorldSky;

SKY g_Sky[SKY_MAX];

/******************************************************************************
* 関数名：InitSky
* 
* 引数  ：
* 戻り値：
* 説明  ：
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

	//テクスチャ読み込み
	if( SKY_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , SKY_TEX , &g_pTextureSky );
	}


	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		VERTEX_3D *pVtx;
		g_Sky[cntSky].pVtxBuffSky -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//座標設定
		int cntVtx = 0;

		for( int tate = SKY_Z / 2 , cntTate = 0; cntTate <= SKY_Z ; tate-- , cntTate++ )
		{
			for( int yoko = -SKY_X / 2 , cntYoko = 0 ; cntYoko <= SKY_X ; yoko++ , cntYoko++ )
			{
				pVtx[cntVtx].pos = D3DXVECTOR3( SKY_WIDHT * yoko , 0.0f , SKY_HEIGTH * tate );

				cntVtx++;
			}
		}

		//頂点カラー設定
		for( int cntCol = 0 ; cntCol < SKY_NUM_VTX ; cntCol++ )
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

		//インデックス
		for(int zCnt = 1 ; zCnt <= SKY_Z ; zCnt++ )//ｚ行分まわす
		{
			for( int xCnt = 0, p = 0 , q = 0 ; xCnt <= ( SKY_X + 1 ) * 2 - 1; xCnt++ )//x行分まわす
			{
				switch( xCnt % 2 )//奇数偶数で分ける
				{
				case 0:
					{
						pIndex[cntIdx] = zCnt * ( SKY_X + 1 ) + p;//偶数の時の値を入れる
						p++;

						break;
					}
				case 1:
					{
						pIndex[cntIdx] = ( zCnt - 1 ) * ( SKY_X + 1 ) + q;//奇数の時の値を入れる
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
* 関数名：UninitSky
* 
* 引数  ：
* 戻り値：
* 説明  ：
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
* 関数名：UpdateSky
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateSky( void )
{
	/*VERTEX_3D *pVtx;
	g_Sky[SKY_MAX].pVtxBuffSky -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	pVtx[4].pos = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );

	g_Sky[SKY_MAX].pVtxBuffSky -> Unlock();*/
}


/******************************************************************************
* 関数名：DrawSky
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawSky( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntSky = 0 ; cntSky < SKY_MAX ; cntSky++ )
	{
		if( g_Sky[cntSky].useSky == true )
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_mtxWorldSky );

			D3DXMatrixScaling( &mtxScl , g_Sky[cntSky].sclSky.x , g_Sky[cntSky].sclSky.y , g_Sky[cntSky].sclSky.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldSky , &g_mtxWorldSky , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Sky[cntSky].rotSky.x , g_Sky[cntSky].rotSky.y , g_Sky[cntSky].rotSky.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldSky , &g_mtxWorldSky , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Sky[cntSky].posSky.x , g_Sky[cntSky].posSky.y , g_Sky[cntSky].posSky.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldSky , &g_mtxWorldSky , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldSky );

			//インデックスバッファをデータストリームにバインド
			pDevice -> SetIndices( g_Sky[cntSky].pIdxBuffSky );

			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_Sky[cntSky].pVtxBuffSky , 0 , sizeof( VERTEX_3D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureSky );

			//ポリゴンの描画
			pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , SKY_NUM_VTX , 0 ,SKY_NUM_PORIGON );
		}
	}
}

/******************************************************************************
* 関数名：GetSky
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
SKY *GetSky( void )
{
	return &g_Sky[0];
}

/******************************************************************************
* 関数名：SetSky
* 
* 引数  ：
* 戻り値：
* 説明  ：
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
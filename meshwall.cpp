/******************************************************************************
* タイトル  :
* ファイル名:meshwall.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/11/10
*******************************************************************************
* 更新履歴:-2015/11/10 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPDIRECT3DVERTEXBUFFER9 pVtxBuffWall = NULL;//頂点バッファ
LPDIRECT3DINDEXBUFFER9 pIdxBuffWall = NULL ;//インデックスバッファ
LPDIRECT3DTEXTURE9 pTextureWall = NULL;
D3DXMATRIX mtxWorldWall;

WALL g_wall[WALL_MAX];

/******************************************************************************
* 関数名：InitWall
* 
* 引数  ：
* 戻り値：
* 説明  ：
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

	//テクスチャ読み込み
	if( WALL_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/akira000.png" , &pTextureWall );
	}

	VERTEX_3D *pVtx;
	pVtxBuffWall -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntWall = 0 , cntVtx = 0 ; cntWall < WALL_MAX ; cntWall++ , cntVtx += 9 )
	{
		//座標設定
		pVtx[cntVtx].pos = D3DXVECTOR3( -200.0f , 80.0f , 50.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3( 0.0f , 80.0f , 50.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( 200.0f , 80.0f , 50.0f );

		pVtx[cntVtx + 3].pos = D3DXVECTOR3( -200.0f , 50.0f , 0.0f );
		pVtx[cntVtx + 4].pos = D3DXVECTOR3( 0.0f , 50.0f , 0.0f );
		pVtx[cntVtx + 5].pos = D3DXVECTOR3( 200.0f , 50.0f , 0.0f );

		pVtx[cntVtx + 6].pos = D3DXVECTOR3( -200.0f , 0.0f , 0.0f );
		pVtx[cntVtx + 7].pos = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		pVtx[cntVtx + 8].pos = D3DXVECTOR3( 200.0f , 0.0f , 0.0f );


		//頂点カラー設定
		for( int cntCol = 0 ; cntCol < WALL_NUM_VTX ; cntCol++ )
		{
			pVtx[cntVtx + cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		}

		//テクスチャ
		pVtx[cntVtx].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( 0.5 , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 1 , 0 );

		pVtx[cntVtx + 3].tex = D3DXVECTOR2( 0 , 0.5 );
		pVtx[cntVtx + 4].tex = D3DXVECTOR2( 0.5 , 0.5 );
		pVtx[cntVtx + 5].tex = D3DXVECTOR2( 1 , 0.5 );

		pVtx[cntVtx + 6].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 7].tex = D3DXVECTOR2( 0.5 , 1 );
		pVtx[cntVtx + 8].tex = D3DXVECTOR2( 1 , 1 );

		//法線
		for( int cntNml = 0 ; cntNml < WALL_NUM_VTX ; cntNml++ )
		{
			pVtx[cntVtx + cntNml].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		}
	}

	pVtxBuffWall -> Unlock();

	WORD *pIndex;
	pIdxBuffWall -> Lock( 0 , 0 ,( void** )&pIndex ,0 );

	//インデックス
	for( int cntWall = 0 , cntIdx = 0 ; cntWall < WALL_MAX ; cntWall++ , cntIdx += WALL_NUM_INDEX )
	{
		int CntIdxWall = 0;//インデックスのカウント

		for(int yCnt = 1 ; yCnt <= WALL_Y ; yCnt++ )//ｚ行分まわす
		{
			for( int xCnt = 0 , p = 0 , q = 0 ; xCnt <= ( WALL_X + 1 ) * 2 - 1; xCnt++ )//x行分まわす
			{
				switch( xCnt % 2 )//奇数偶数で分ける
				{
				case 0:
					{
						pIndex[ cntIdx + CntIdxWall] = yCnt * ( WALL_X + 1 ) + p;//偶数の時の値を入れる
						p++;

						break;
					}
				case 1:
					{
						pIndex[ cntIdx + CntIdxWall] = ( yCnt - 1 ) * ( WALL_X + 1 ) + q;//奇数の時の値を入れる
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
* 関数名：UninitWall
* 
* 引数  ：
* 戻り値：
* 説明  ：
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
* 関数名：UpdateWall
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateWall( void )
{
}


/******************************************************************************
* 関数名：DrawWall
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawWall( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntWall = 0 , cntIdx = 0  ; cntWall < WALL_MAX ; cntWall++ , cntIdx += WALL_NUM_INDEX )
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity( &mtxWorldWall );

		D3DXMatrixScaling( &mtxScl , g_wall[cntWall].sclWall.x , g_wall[cntWall].sclWall.y , g_wall[cntWall].sclWall.z );
	
		//スケールを反映
		D3DXMatrixMultiply( &mtxWorldWall , &mtxWorldWall , &mtxScl );

		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_wall[cntWall].rotWall.x , g_wall[cntWall].rotWall.y , g_wall[cntWall].rotWall.z );

		//回転の反映
		D3DXMatrixMultiply( &mtxWorldWall , &mtxWorldWall , &mtxRot );

		D3DXMatrixTranslation( &mtxTrans , g_wall[cntWall].posWall.x , g_wall[cntWall].posWall.y , g_wall[cntWall].posWall.z );

		//移動の反映
		D3DXMatrixMultiply( &mtxWorldWall , &mtxWorldWall , &mtxTrans );

		//ワールドマトリックスの設定
		pDevice ->SetTransform( D3DTS_WORLD , &mtxWorldWall );

		//インデックスバッファをデータストリームにバインド
		pDevice -> SetIndices( pIdxBuffWall );

		//頂点バッファをデータストリームにバインド
		pDevice -> SetStreamSource( 0 , pVtxBuffWall , 0 , sizeof( VERTEX_3D ));

		//頂点フォーマット
		pDevice -> SetFVF( FVF_VERTEX_3D );

		pDevice -> SetTexture( 0 , pTextureWall );

		//ポリゴンの描画
		pDevice -> DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP , 0 , 0 , WALL_NUM_VTX , cntIdx ,WALL_NUM_PORIGON );
	}
	
}
/******************************************************************************
* タイトル  :
* ファイル名:acorncnt.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル
******************************************************************************/
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffAcornCnt = NULL;
LPDIRECT3DTEXTURE9 g_pTextureAcornCnt[ACORN_TEX_MAX];

ACORNCNT g_acornCnt[ACORNCNT_MAX];

int g_AcornCntValue;	//総得点

/******************************************************************************
* 関数名：InitAcornCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitAcornCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//mainでのg_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * ( 4 * ACORNCNT_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffAcornCnt ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_AcornCntValue = 0;

	VERTEX_2D *pVtx;
	g_pVtxBuffAcornCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	//テクスチャ読み込み
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/number000.png" , &g_pTextureAcornCnt[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/kakeru.png" , &g_pTextureAcornCnt[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/donguri000.png" , &g_pTextureAcornCnt[2] );


	for( int nCntAcornCnt = 0 , vtxCntAcornCnt = 0 , posAcornCntX = 0 ;  nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ , vtxCntAcornCnt += 4  , posAcornCntX -= ACORN_TEX_WIDTH )
	{
		g_acornCnt[nCntAcornCnt].posAcornCnt    = D3DXVECTOR3( 200.0f + posAcornCntX , 40.0f , 0.0f );
		g_acornCnt[nCntAcornCnt].heightAcornCnt = ACORNCNT_HEIGHT / 2;
		g_acornCnt[nCntAcornCnt].widthAcornCnt  = ACORNCNT_WIDTH / 2;
		g_acornCnt[nCntAcornCnt].acornInd       = ACORN_IND;
		g_acornCnt[nCntAcornCnt].cntIndTime    = 0;

		if( nCntAcornCnt == ACORNCNT_MAX - 1 )//どんぐりの幅
		{
			g_acornCnt[nCntAcornCnt].heightAcornCnt = ACORN_TEX_HEIGHT / 2;
			g_acornCnt[nCntAcornCnt].widthAcornCnt  = ACORN_TEX_WIDTH / 2;
		}
		else if( nCntAcornCnt == ACORNCNT_MAX - 2 )//×の幅
		{
			g_acornCnt[nCntAcornCnt].heightAcornCnt = ACORN_KAKERU_HEIGHT / 2;
		}

		//座標設定
		pVtx[vtxCntAcornCnt].pos     = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 1].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 2].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 3].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );

		//2次元変数
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[vtxCntAcornCnt + add].rwh = 1.0f;
		}

		//頂点カラー設定
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[vtxCntAcornCnt + add].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		//テクスチャ
		pVtx[vtxCntAcornCnt].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[vtxCntAcornCnt + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[vtxCntAcornCnt + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[vtxCntAcornCnt + 3].tex = D3DXVECTOR2( 1 , 1 );

	}

	g_pVtxBuffAcornCnt -> Unlock();

	return S_OK;
}

/******************************************************************************
* 関数名：IninitAcornCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitAcornCnt( void )
{
	for( int cntTex = 0; cntTex < ACORN_TEX_MAX ; cntTex++ )
	{
		if( g_pTextureAcornCnt[cntTex] != NULL )
		{
			g_pTextureAcornCnt[cntTex] -> Release();
			g_pTextureAcornCnt[cntTex] = NULL;
		}
	}

	if( g_pVtxBuffAcornCnt !=NULL )
	{
		g_pVtxBuffAcornCnt -> Release();
		g_pVtxBuffAcornCnt = NULL;
	}
	
}

/******************************************************************************
* 関数名：UpdateAcornCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateAcornCnt( void )
{
	float num;
	int scoreWork = g_AcornCntValue;
	
	VERTEX_2D *pVtx;
	g_pVtxBuffAcornCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );


	//得点を数字に反映////////////////////////////////////////////////////////////////////
	for( int nCntAcornCnt = 0 , vtxCntAcornCnt = 0  ; nCntAcornCnt < ACORNCNT_MAX - 2 ; nCntAcornCnt++ , vtxCntAcornCnt += 4 )
	{
		num = scoreWork % 10;
		scoreWork /= 10;
		
		g_acornCnt[nCntAcornCnt].posTexXAcornCnt = ( num / 10 );

		//テクスチャ
		pVtx[vtxCntAcornCnt].tex     = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt                       , 0 );
		pVtx[vtxCntAcornCnt + 1].tex = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt + ACORNCNT_PATTERN_WIDTH , 0 );
		pVtx[vtxCntAcornCnt + 2].tex = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt                       , 1 );
		pVtx[vtxCntAcornCnt + 3].tex = D3DXVECTOR2( g_acornCnt[nCntAcornCnt].posTexXAcornCnt + ACORNCNT_PATTERN_WIDTH , 1 );
	}

	for( int nCntAcornCnt = 0 , vtxCntAcornCnt = 0  ; nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ , vtxCntAcornCnt += 4 )
	{
		//表示の処理//////////////////////////////////////////////////////////////////////
		switch( g_acornCnt[nCntAcornCnt].acornInd )
		{
		case ACORN_NONE://表示しない
			{
				g_acornCnt[nCntAcornCnt].cntIndTime = 0;
				break;
			}
		case ACORN_DOWN://下に移動
			{
				if( g_acornCnt[nCntAcornCnt].posAcornCnt.y < ACORNCNT_POSY )
				{
					g_acornCnt[nCntAcornCnt].posAcornCnt.y += ACORNCNT_DOWN_SPEED;
				}
				else
				{
					g_acornCnt[nCntAcornCnt].acornInd = ACORN_IND;
				}
				break;
			}
		case ACORN_IND://表示
			{
				g_acornCnt[nCntAcornCnt].cntIndTime++;

				
				if( g_acornCnt[nCntAcornCnt].cntIndTime  % ACORNCNT_INDICATE_TIME == 0 )
				{
					g_acornCnt[nCntAcornCnt].acornInd = ACORN_UP;
				}
				break;
			}
		case ACORN_UP://上にしまう
			{
				if( g_acornCnt[nCntAcornCnt].posAcornCnt.y > - ACORNCNT_POSY )
				{
					g_acornCnt[nCntAcornCnt].posAcornCnt.y += ACORNCNT_UP_SPEED;
				}
				else
				{
					g_acornCnt[nCntAcornCnt].acornInd = ACORN_NONE;
				}
				break;
			}
		}

		//座標代入
		pVtx[vtxCntAcornCnt].pos     = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 1].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y - g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 2].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x - g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );
		pVtx[vtxCntAcornCnt + 3].pos = D3DXVECTOR3( g_acornCnt[nCntAcornCnt].posAcornCnt.x + g_acornCnt[nCntAcornCnt].widthAcornCnt , g_acornCnt[nCntAcornCnt].posAcornCnt.y + g_acornCnt[nCntAcornCnt].heightAcornCnt , 0.0f );

	}


	//１００になったら1UP(リセット)
	if( g_AcornCntValue >= 100 )
	{
		AddLifeCnt(1);
		g_AcornCntValue = 0;
	}

	g_pVtxBuffAcornCnt -> Unlock();
}

/******************************************************************************
* 関数名：DrawAcornCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawAcornCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームにバインド
	pDevice -> SetStreamSource( 0 , g_pVtxBuffAcornCnt , 0 , sizeof( VERTEX_2D ));

	//頂点フォーマット
	pDevice -> SetFVF( FVF_VERTEX_2D );

	pDevice -> SetTexture( 0 , g_pTextureAcornCnt[0] );

	for( int nCntAcornCnt = 0 ; nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ )
	{
		if( nCntAcornCnt == ACORNCNT_MAX - 2 )//テクスチャチェンジ
		{
			pDevice -> SetTexture( 0 , g_pTextureAcornCnt[1] );
		}
		else if( nCntAcornCnt == ACORNCNT_MAX - 1 )
		{
			pDevice -> SetTexture( 0 , g_pTextureAcornCnt[2] );
		}

		//ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 * nCntAcornCnt, 2 );
	}
}

/******************************************************************************
* 関数名：GetAcornCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
ACORNCNT *GetAcornCnt( void )
{
	return g_acornCnt;
}


/******************************************************************************
* 関数名：AddAcornCnt
* 
* 引数  ：加算用のスコア
* 戻り値：なし
* 説明  ：集めたスコアをg_AcornCntvalueに全て足す
******************************************************************************/
void AddAcornCnt( int value )
{
	g_AcornCntValue += value;

	//表示
	for( int acornCnt = 0 ; acornCnt < ACORNCNT_MAX ; acornCnt++ )
	{
		g_acornCnt[acornCnt].acornInd = ACORN_DOWN;
	}
}
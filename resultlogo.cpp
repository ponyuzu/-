/******************************************************************************
* タイトル  :
* ファイル名:select.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2016/02/01
*******************************************************************************
* 更新履歴:-2016/02/01 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "resultlogo.h"

/******************************************************************************
* グローバル
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureResultLogo[RESULTLOGO_MAX];

RESULTLOGO g_result[RESULTLOGO_MAX];
RESULTMODE g_resultMode;

/******************************************************************************
* 関数名：InitResultLogo
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitResultLogo( void )
{
	InitCamera();
	g_resultMode = GetResultMode();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//mainでのg_pD3DDevice

	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_2D ,
													D3DPOOL_MANAGED ,
													&g_result[nCntResultLogo].pVtxBuffResultLogo ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo000.png" , &g_pTextureResultLogo[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo001.png" , &g_pTextureResultLogo[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo002.png" , &g_pTextureResultLogo[2] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/resultlogo003.png" , &g_pTextureResultLogo[3] );


	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
		VERTEX_2D *pVtx;
		g_result[nCntResultLogo].pVtxBuffResultLogo -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_result[0].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 - 100 , 0.0f );
		g_result[0].heightResultLogo = RESULTLOGO1_HEIDHT / 2;
		g_result[0].widthResultLogo  = RESULTLOGO1_WIDTH  / 2;

		g_result[1].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT - 200 , 0.0f );
		g_result[1].heightResultLogo = RESULTLOGO2_HEIDHT / 2;
		g_result[1].widthResultLogo  = RESULTLOGO2_WIDTH / 2;

		g_result[2].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 - 100 , 0.0f );
		g_result[2].heightResultLogo = RESULTLOGO3_HEIDHT / 2;
		g_result[2].widthResultLogo  = RESULTLOGO3_WIDTH  / 2;

		g_result[3].posResultLogo    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT - 200 , 0.0f );
		g_result[3].heightResultLogo = RESULTLOGO4_HEIDHT / 2;
		g_result[3].widthResultLogo  = RESULTLOGO4_WIDTH / 2;

		g_result[nCntResultLogo].LogoUse = false;

		//座標設定
		pVtx[0].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x - g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y - g_result[nCntResultLogo].heightResultLogo , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x + g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y - g_result[nCntResultLogo].heightResultLogo , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x - g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y + g_result[nCntResultLogo].heightResultLogo , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_result[nCntResultLogo].posResultLogo.x + g_result[nCntResultLogo].widthResultLogo , g_result[nCntResultLogo].posResultLogo.y + g_result[nCntResultLogo].heightResultLogo , 0.0f );

		//2次元変数
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[add].rwh = 1.0f;
		}

		//頂点カラー設定
		for( int add = 0 ; add < 4 ; add++ )
		{
			pVtx[add].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		//テクスチャ
		pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );

		g_result[nCntResultLogo].pVtxBuffResultLogo -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* 関数名：IninitResultLogo
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitResultLogo( void )
{
	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
		if( g_result[nCntResultLogo].pVtxBuffResultLogo !=NULL )
		{
			g_result[nCntResultLogo].pVtxBuffResultLogo -> Release();
			g_result[nCntResultLogo].pVtxBuffResultLogo = NULL;
		}

		if( g_pTextureResultLogo[nCntResultLogo] != NULL )
		{
			g_pTextureResultLogo[nCntResultLogo] -> Release();
			g_pTextureResultLogo[nCntResultLogo] = NULL;
		}
	}
}

/******************************************************************************
* 関数名：UpdateResultLogo
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateResultLogo( void )
{
	switch( g_resultMode )
	{
	case RESULT_CREAL:
		{
			g_result[0].LogoUse = true;
			g_result[1].LogoUse = true;
			break;
		}
	case RESULT_GAMEOVER:
		{
			g_result[2].LogoUse = true;
			g_result[3].LogoUse = true;
			break;
		}
	}
}

/******************************************************************************
* 関数名：DrawResultLogo
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawResultLogo( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntResultLogo = 0 ;  nCntResultLogo < RESULTLOGO_MAX ; nCntResultLogo++ )
	{
		if( g_result[nCntResultLogo].LogoUse == true )
		{

			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_result[nCntResultLogo].pVtxBuffResultLogo , 0 , sizeof( VERTEX_2D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_2D );

			pDevice -> SetTexture( 0 , g_pTextureResultLogo[nCntResultLogo] );

			//ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
		}
	}

}
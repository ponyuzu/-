/******************************************************************************
* タイトル  :
* ファイル名:pause.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "pause.h"

/******************************************************************************
* グローバル
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTexturePause[PAUSE_TEX_MAX];

PAUSE g_pause[PAUSE_TEX_MAX];
PAUSEPATTARN g_pausePattarn;

bool g_bPause;				//ポーズかどうか

/******************************************************************************
* 関数名：InitPause
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitPause( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//mainでのg_pD3DDevice

	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{
		if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_2D ,
													D3DPOOL_MANAGED ,
													&g_pause[cnt].pVtxBuffPause ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	g_pausePattarn = PAUSE_CONTINUE;	//ポーズパターンの初期値

	g_bPause = false;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile( pDevice , PAUSE_BG_NAME , &g_pTexturePause[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/pause000.png" , &g_pTexturePause[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/pause001.png" , &g_pTexturePause[2] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/pause002.png" , &g_pTexturePause[3] );


	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{

		VERTEX_2D *pVtx;
		g_pause[cnt].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );


		g_pause[0].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 , 0.0f );
		g_pause[0].height = PAUSE_BG_HEIGHT / 2;
		g_pause[0].width  = PAUSE_BG_WIDTH  / 2;

		g_pause[1].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 - 100 , 0.0f );
		g_pause[1].height = PAUSE_LOGO1_HEIGHT / 2;
		g_pause[1].width  = PAUSE_LOGO1_WIDTH / 2;

		g_pause[2].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 , 0.0f );
		g_pause[2].height = PAUSE_LOGO2_HEIGHT / 2;
		g_pause[2].width  = PAUSE_LOGO2_WIDTH  / 2;

		g_pause[3].pos    = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2 + 100, 0.0f );
		g_pause[3].height = PAUSE_LOGO3_HEIGHT / 2;
		g_pause[3].width  = PAUSE_LOGO3_WIDTH / 2;

		//座標設定
		pVtx[0].pos = D3DXVECTOR3( g_pause[cnt].pos.x - g_pause[cnt].width , g_pause[cnt].pos.y - g_pause[cnt].height , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_pause[cnt].pos.x + g_pause[cnt].width , g_pause[cnt].pos.y - g_pause[cnt].height , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_pause[cnt].pos.x - g_pause[cnt].width , g_pause[cnt].pos.y + g_pause[cnt].height , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_pause[cnt].pos.x + g_pause[cnt].width , g_pause[cnt].pos.y + g_pause[cnt].height , 0.0f );


		//2次元変数
		pVtx[0].rwh = 1.0f;
		pVtx[1].rwh = 1.0f;
		pVtx[2].rwh = 1.0f;
		pVtx[3].rwh = 1.0f;

		//頂点カラー設定
		for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
		{
			pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );

		g_pause[cnt].pVtxBuffPause -> Unlock();

	}

	return S_OK;
}

/******************************************************************************
* 関数名：IninitPause
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitPause( void )
{
	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{
		if( g_pTexturePause[cnt] != NULL )
		{
			g_pTexturePause[cnt] -> Release();
			g_pTexturePause[cnt] = NULL;
		}

		if( g_pause[cnt].pVtxBuffPause !=NULL )
		{
			g_pause[cnt].pVtxBuffPause -> Release();
			g_pause[cnt].pVtxBuffPause = NULL;
		}
	}
	
}

/******************************************************************************
* 関数名：UpdatePause
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdatePause( void )
{

	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{

		VERTEX_2D *pVtx;
		g_pause[cnt].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//頂点カラー設定
		for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
		{
			pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		}

		g_pause[cnt].pVtxBuffPause -> Unlock();

	}

	switch( g_pausePattarn )
	{
	case PAUSE_CONTINUE:
		{
			VERTEX_2D *pVtx;
			g_pause[1].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//頂点カラー設定
			for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 0 , 0 , 255 );
			}

			g_pause[1].pVtxBuffPause -> Unlock();

			break;
		}
	case PAUSE_RETRY:
		{
			VERTEX_2D *pVtx;
			g_pause[2].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//頂点カラー設定
			for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 0 , 0 , 255 );
			}

			g_pause[2].pVtxBuffPause -> Unlock();
			break;
		}
	case PAUSE_QUIT:
		{
			VERTEX_2D *pVtx;
			g_pause[3].pVtxBuffPause -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//頂点カラー設定
			for( int cntCol = 0 ; cntCol < 4 ; cntCol ++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 0 , 0 , 255 );
			}

			g_pause[3].pVtxBuffPause -> Unlock();
			break;
		}
	}

	//ポーズ中の処理
	if( g_bPause == true )
	{
		//上に移動
		if( GetKeyboardTrigger( DIK_W ) )
		{
			if( g_pausePattarn == PAUSE_CONTINUE )
			{
				g_pausePattarn = PAUSE_QUIT;
			}
			else if( g_pausePattarn == PAUSE_QUIT )
			{
				g_pausePattarn = PAUSE_RETRY;
			}
			else
			{
				g_pausePattarn = PAUSE_CONTINUE;
			}
		}

		//下に移動
		else if( GetKeyboardTrigger( DIK_S ) )
		{
			if( g_pausePattarn == PAUSE_CONTINUE )
			{
				g_pausePattarn = PAUSE_RETRY;
			}
			else if( g_pausePattarn == PAUSE_RETRY )
			{
				g_pausePattarn = PAUSE_QUIT;
			}
			else
			{
				g_pausePattarn = PAUSE_CONTINUE;
			}
		}

		//enterを押した時の処理
		if( GetKeyboardTrigger( DIK_RETURN ) )
		{
			if( g_pausePattarn == PAUSE_CONTINUE )
			{
				g_bPause = false;
			}
			else if( g_pausePattarn == PAUSE_RETRY )
			{
				SetFade( FADE_OUT , MODE_GAME );
			}
			else
			{
				SetFade( FADE_OUT , MODE_SELECT );
			}
		}
	}

}

/******************************************************************************
* 関数名：DrawPause
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawPause( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cnt = 0 ; cnt < PAUSE_TEX_MAX ; cnt++ )
	{
		if( g_bPause == true )
		{
			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_pause[cnt].pVtxBuffPause , 0 , sizeof( VERTEX_2D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_2D );

			pDevice -> SetTexture( 0 , g_pTexturePause[cnt] );

			//ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
		}
	}

}
/******************************************************************************
* 関数名：GetPause
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
bool GetPause( void )
{
	return g_bPause;
}

/******************************************************************************
* 関数名：SetPause
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetPause( bool pause )
{
	g_bPause = pause;
}
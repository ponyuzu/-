/******************************************************************************
* タイトル  :
* ファイル名:fade.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
D3DXCOLOR g_colorFade;		//フェード色
FADE g_fade;				//フェードの状態
MODE g_modeNext;			//次のモード
float g_alphaMove;			//α値の計算

LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;
LPDIRECT3DTEXTURE9 g_pTextureFade = NULL;


/******************************************************************************
* 関数名：InitFaed
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitFade( void )
{
	g_colorFade = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.0f );
	g_fade = FADE_IN;
	g_modeNext = MODE_TITLE;
	g_alphaMove = 1.0f;

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//mainでのg_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffFade ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffFade -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );
	//座標設定
	pVtx[0].pos = D3DXVECTOR3( 0.0f         , 0.0f          , 0.0f );
	pVtx[1].pos = D3DXVECTOR3( SCREEN_WIDTH , 0.0f          , 0.0f );
	pVtx[2].pos = D3DXVECTOR3( 0.0f         , SCREEN_HEIGHT , 0.0f );
	pVtx[3].pos = D3DXVECTOR3( SCREEN_WIDTH , SCREEN_HEIGHT , 0.0f );

	//2次元変数
	pVtx[0].rwh = 1.0f;
	pVtx[1].rwh = 1.0f;
	pVtx[2].rwh = 1.0f;
	pVtx[3].rwh = 1.0f;

	//頂点カラー設定
	pVtx[0].col = g_colorFade;
	pVtx[1].col = g_colorFade;
	pVtx[2].col = g_colorFade;
	pVtx[3].col = g_colorFade;

	g_pVtxBuffFade -> Unlock();

	return S_OK;
}

/******************************************************************************
* 関数名：UninitFaed
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitFade( void )
{
}

/******************************************************************************
* 関数名：UpdateFaed
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateFade ( void )
{
	switch( g_fade )
	{
	case FADE_IN:
		//α計算
		g_colorFade.a -= 0.02f;

		if( g_colorFade.a <= 0.0f )
		{
			g_fade = FADE_NONE;
		}
		break;

	case FADE_OUT:
		//α計算
		g_colorFade.a += 0.02f;

		if( g_colorFade.a >= 1.0f )
		{
			SetMode( g_modeNext );
			g_fade = FADE_IN;
		}
		break;
	}

	VERTEX_2D *pVtx;
	g_pVtxBuffFade -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );
	pVtx[1].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );
	pVtx[2].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );
	pVtx[3].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , g_colorFade.a );

	g_pVtxBuffFade -> Unlock();
}

/******************************************************************************
* 関数名：DrawFaed
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawFade( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームにバインド
	pDevice -> SetStreamSource( 0 , g_pVtxBuffFade , 0 , sizeof( VERTEX_2D ));

	//頂点フォーマット
	pDevice -> SetFVF( FVF_VERTEX_2D );

	pDevice -> SetTexture( 0 , g_pTextureFade );

	//ポリゴンの描画
	pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
}

/******************************************************************************
* 関数名：SetFade
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetFade( FADE fade , MODE modeNext )
{
	if( g_fade == FADE_NONE )
	{
		g_fade = fade;
		g_modeNext = modeNext;
	}
}

/******************************************************************************
* 関数名：GetFade
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
FADE *GetFade( void )
{
	return &g_fade;
}
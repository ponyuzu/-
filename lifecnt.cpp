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
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLifeCnt = NULL;
LPDIRECT3DTEXTURE9 g_pTextureLifeCnt[LIFECNT_TEX_MAX];

LIFECNT g_lifeCnt[LIFECNT_MAX];

int g_LifeCntValue;	//総得点

/******************************************************************************
* 関数名：InitLifeCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitLifeCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();//mainでのg_pD3DDevice

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * ( 4 * LIFECNT_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_2D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffLifeCnt ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_LifeCntValue = 0;

	VERTEX_2D *pVtx;
	g_pVtxBuffLifeCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	//テクスチャ読み込み
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/number000.png" , &g_pTextureLifeCnt[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/kakeru.png" , &g_pTextureLifeCnt[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/tanuki000.png" , &g_pTextureLifeCnt[2] );

	for( int lifeCnt = 0 , vtxCntLifeCnt = 0 , posLifeCntX = 0 ;  lifeCnt < LIFECNT_MAX ; lifeCnt++ , vtxCntLifeCnt += 4  , posLifeCntX -= LIFECNT_TEX_WIDTH )
	{
		g_lifeCnt[lifeCnt].posLifeCnt    = D3DXVECTOR3( 660.0f + posLifeCntX , -LIFECNT_POSY , 0.0f );
		g_lifeCnt[lifeCnt].heightLifeCnt = LIFECNT_HEIGHT / 2;
		g_lifeCnt[lifeCnt].widthLifeCnt  = LIFECNT_WIDTH / 2;
		g_lifeCnt[lifeCnt].lifeInd       = LIFE_IND;
		g_lifeCnt[lifeCnt].cntIndTime    = 0;

		if( lifeCnt == LIFECNT_MAX - 1 )//たぬきの幅
		{
			
			g_lifeCnt[lifeCnt].heightLifeCnt = LIFECNT_TEX_HEIGHT / 2;
			g_lifeCnt[lifeCnt].widthLifeCnt  = LIFECNT_TEX_WIDTH / 2;
		}
		else if( lifeCnt == LIFECNT_MAX - 2 )//×の幅
		{
			
			g_lifeCnt[lifeCnt].heightLifeCnt = LIFECNT_KAKERU_HEIGHT / 2;
		}

		//座標設定
		pVtx[vtxCntLifeCnt].pos     = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 1].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 2].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 3].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );

		//2次元変数
		pVtx[vtxCntLifeCnt].rwh     = 1.0f;
		pVtx[vtxCntLifeCnt + 1].rwh = 1.0f;
		pVtx[vtxCntLifeCnt + 2].rwh = 1.0f;
		pVtx[vtxCntLifeCnt + 3].rwh = 1.0f;

		//頂点カラー設定
		pVtx[vtxCntLifeCnt].col     = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[vtxCntLifeCnt + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[vtxCntLifeCnt + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[vtxCntLifeCnt + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );

		//テクスチャ
		pVtx[vtxCntLifeCnt].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[vtxCntLifeCnt + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[vtxCntLifeCnt + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[vtxCntLifeCnt + 3].tex = D3DXVECTOR2( 1 , 1 );
	}

	g_pVtxBuffLifeCnt -> Unlock();

	g_LifeCntValue = 4;

	return S_OK;
}

/******************************************************************************
* 関数名：IninitLifeCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitLifeCnt( void )
{
	for( int cntTex = 0 ; cntTex < LIFECNT_TEX_MAX ; cntTex++ )
	{
		if( g_pTextureLifeCnt[cntTex] != NULL )
		{
			g_pTextureLifeCnt[cntTex] -> Release();
			g_pTextureLifeCnt[cntTex] = NULL;
		}
	}

	if( g_pVtxBuffLifeCnt !=NULL )
	{
		g_pVtxBuffLifeCnt -> Release();
		g_pVtxBuffLifeCnt = NULL;
	}
	
}

/******************************************************************************
* 関数名：UpdateLifeCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateLifeCnt( void )
{
	float num;
	int scoreWork = g_LifeCntValue;
	MODEL *pModel = GetModel();
	
	VERTEX_2D *pVtx;
	g_pVtxBuffLifeCnt -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int lifeCnt = 0 , vtxCntLifeCnt = 0  ; lifeCnt < LIFECNT_MAX - 2 ; lifeCnt++ , vtxCntLifeCnt += 4 )
	{
		//数字の描画を変えいく計算///////////////////////////////////////////////////////////////
		num = scoreWork % 10;
		scoreWork /= 10;
		
		g_lifeCnt[lifeCnt].posTexXLifeCnt = ( num / 10 );

		//テクスチャ
		pVtx[vtxCntLifeCnt].tex     = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt                       , 0 );
		pVtx[vtxCntLifeCnt + 1].tex = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt + LIFECNT_PATTERN_WIDTH , 0 );
		pVtx[vtxCntLifeCnt + 2].tex = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt                       , 1 );
		pVtx[vtxCntLifeCnt + 3].tex = D3DXVECTOR2( g_lifeCnt[lifeCnt].posTexXLifeCnt + LIFECNT_PATTERN_WIDTH , 1 );

	}

	for( int lifeCnt = 0 , vtxCntLifeCnt = 0  ; lifeCnt < LIFECNT_MAX ; lifeCnt++ , vtxCntLifeCnt += 4 )
	{
		//表示の処理//////////////////////////////////////////////////////////////////////
		switch( g_lifeCnt[lifeCnt].lifeInd )
		{
		case LIFE_NONE://表示しない
			{
				g_lifeCnt[lifeCnt].cntIndTime    = 0;
				break;
			}
		case LIFE_DOWN://下に移動
			{
				if( g_lifeCnt[lifeCnt].posLifeCnt.y < LIFECNT_POSY )
				{
					g_lifeCnt[lifeCnt].posLifeCnt.y += LIFECNT_DOWN_SPEED;
				}
				else
				{
					g_lifeCnt[lifeCnt].lifeInd = LIFE_IND;
				}
				break;
			}
		case LIFE_IND://表示
			{
				g_lifeCnt[lifeCnt].cntIndTime++;

				if( g_lifeCnt[lifeCnt].cntIndTime  % LIFECNT_INDICATE_TIME == 0 )
				{
					g_lifeCnt[lifeCnt].lifeInd = LIFE_UP;
				}
				break;
			}
		case LIFE_UP://上にしまう
			{
				if( g_lifeCnt[lifeCnt].posLifeCnt.y > - LIFECNT_POSY )
				{
					g_lifeCnt[lifeCnt].posLifeCnt.y += LIFECNT_UP_SPEED;
				}
				else
				{
					g_lifeCnt[lifeCnt].lifeInd = LIFE_NONE;
				}
				break;
			}
		}

		//ゲームオーバー///////////////////////////////////////////////////////////
		if( g_LifeCntValue <= -1 )//ライフが尽きた時
		{
			g_lifeCnt[lifeCnt].posLifeCnt.y = - LIFECNT_POSY;
			SetResultMode( RESULT_GAMEOVER );
			SetFade( FADE_OUT , MODE_RESULT );

			//リセットすべきもの
			InitAcornCnt();
			InitLifeCnt();
		}
		else//位置リセット
		{
			if(pModel -> death == true )
			{
				SetFade( FADE_OUT , MODE_GAME );
			}
		}

		//座標代入
		pVtx[vtxCntLifeCnt].pos     = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 1].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y - g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 2].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x - g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );
		pVtx[vtxCntLifeCnt + 3].pos = D3DXVECTOR3( g_lifeCnt[lifeCnt].posLifeCnt.x + g_lifeCnt[lifeCnt].widthLifeCnt , g_lifeCnt[lifeCnt].posLifeCnt.y + g_lifeCnt[lifeCnt].heightLifeCnt , 0.0f );

	}

	g_pVtxBuffLifeCnt -> Unlock();
}

/******************************************************************************
* 関数名：DrawLifeCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawLifeCnt( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点バッファをデータストリームにバインド
	pDevice -> SetStreamSource( 0 , g_pVtxBuffLifeCnt , 0 , sizeof( VERTEX_2D ));

	//頂点フォーマット
	pDevice -> SetFVF( FVF_VERTEX_2D );

	pDevice -> SetTexture( 0 , g_pTextureLifeCnt[0] );

	for( int lifeCnt = 0 ; lifeCnt < LIFECNT_MAX ; lifeCnt++ )
	{
		if( lifeCnt == LIFECNT_MAX - 2 )//テクスチャチェンジ
		{
			pDevice -> SetTexture( 0 , g_pTextureLifeCnt[1] );
		}
		else if( lifeCnt == LIFECNT_MAX - 1 )
		{
			pDevice -> SetTexture( 0 , g_pTextureLifeCnt[2] );
		}

		//ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 4 * lifeCnt, 2 );
	}
}

/******************************************************************************
* 関数名：GetLifeCnt
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
LIFECNT *GetLifeCnt( void )
{
	return g_lifeCnt;
}

/******************************************************************************
* 関数名：AddLifeCnt
* 
* 引数  ：加算用のスコア
* 戻り値：なし
* 説明  ：集めたスコアをg_LifeCntvalueに全て足す、life表示
******************************************************************************/
void AddLifeCnt( int value )
{
	//足す
	g_LifeCntValue += value;

	//表示
	for( int lifeCnt = 0 ; lifeCnt < LIFECNT_MAX ; lifeCnt++ )
	{
		g_lifeCnt[lifeCnt].lifeInd = LIFE_DOWN;
	}
}
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
#include "selsect.h"

/******************************************************************************
* グローバル
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureSelect[SELECT_MAX];

SELECT g_select[SELECT_MAX];

int g_stage;
bool g_moveLeft[SELECT_MOVE_MAX];
bool g_moveRight[SELECT_MOVE_MAX];

/******************************************************************************
* 関数名：InitSelect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitSelect( void )
{
	InitCamera();

	LPDIRECT3DDEVICE9 pDevice = GetDevice();//mainでのg_pD3DDevice

	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MAX ; nCntSelect++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_2D ) * 4 ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_2D ,
													D3DPOOL_MANAGED ,
													&g_select[nCntSelect].pVtxBuffSelect ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/select001.jpg" , &g_pTextureSelect[0] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/select002.jpg" , &g_pTextureSelect[1] );
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/select003.jpg" , &g_pTextureSelect[2] );


	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MAX ; nCntSelect++ )
	{
		VERTEX_2D *pVtx;
		g_select[nCntSelect].pVtxBuffSelect -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_select[nCntSelect].posSelect    = D3DXVECTOR3( SCREEN_WIDTH * 2, SCREEN_HEIGHT /2 , 0.0f );
		g_select[nCntSelect].heightSelect = SELECY_STAGE_HEIGHT / 2;
		g_select[nCntSelect].widthSelect  = SELECT_STAGE_WIDTH / 2;
		g_select[nCntSelect].StageRelease = false;

		//座標設定
		pVtx[0].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x - g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y - g_select[nCntSelect].heightSelect , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x + g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y - g_select[nCntSelect].heightSelect , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x - g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y + g_select[nCntSelect].heightSelect , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x + g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y + g_select[nCntSelect].heightSelect , 0.0f );

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
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );

		g_select[nCntSelect].pVtxBuffSelect -> Unlock();
	}

	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MOVE_MAX ; nCntSelect++ )
	{
		g_moveLeft[nCntSelect] = false;
		g_moveRight[nCntSelect] = false;
	}

	//0だけ設定しとく
	g_select[0].posSelect = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 , 0.0f );

	//ステージ１解放
	g_select[1].StageRelease = true;
	g_select[2].StageRelease = true;

	g_stage = STAGE_1;

	//やじるし
	InitSelectAro();

	return S_OK;
}

/******************************************************************************
* 関数名：IninitSelect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitSelect( void )
{
	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MAX ; nCntSelect++ )
	{
		if( g_select[nCntSelect].pVtxBuffSelect !=NULL )
		{
			g_select[nCntSelect].pVtxBuffSelect -> Release();
			g_select[nCntSelect].pVtxBuffSelect = NULL;
		}

		if( g_pTextureSelect[nCntSelect] != NULL )
		{
			g_pTextureSelect[nCntSelect] -> Release();
			g_pTextureSelect[nCntSelect] = NULL;
		}
	}

	UninitSelectAro();
}

/******************************************************************************
* 関数名：UpdateSelect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateSelect( void )
{
	ACORNCNT *pAcornCnt = GetAcornCnt();
	LIFECNT *pLifeCnt = GetLifeCnt();


	//ステージ遷移/////////////////////////////////////////////////////////////
	switch( g_stage )
	{
	case STAGE_1:
		{
			g_stage = STAGE_1;

			if( g_select[1].StageRelease )//解放されているか
			{
				if( GetKeyboardTrigger( DIK_D ) )
				{
					g_moveLeft[0] = true;
				}
			}
			break;
		}
	case STAGE_2:
		{
			if( g_select[2].StageRelease )
			{
				if( GetKeyboardTrigger( DIK_D ) && g_moveRight[0] == false )
				{
					g_moveLeft[1] = true;
				}
			}

			if( GetKeyboardTrigger( DIK_A ) && g_moveLeft[1] == false )
			{
				g_moveRight[0] = true;
			}

			break;
		}
	case STAGE_3:
		{
			if( GetKeyboardTrigger( DIK_A ) )
			{
				g_moveRight[1] = true;
			}
			break;
		}
	}

	//移動の計算///////////////////////////////////////////////////////////////
	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MOVE_MAX ; nCntSelect++ )
	{
		if( g_moveLeft[nCntSelect] == true )
		{
			g_select[nCntSelect].posSelect.x -= SELECT_SPEED;
			g_select[nCntSelect + 1].posSelect.x -= SELECT_SPEED;

			if( g_select[nCntSelect].posSelect.x <= - SCREEN_WIDTH )
			{
				g_select[nCntSelect].posSelect = D3DXVECTOR3( -SCREEN_WIDTH , SCREEN_HEIGHT /2 , 0.0f );
				g_select[nCntSelect + 1].posSelect = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 , 0.0f );

				switch( g_stage )
				{
				case STAGE_1:
					{
						g_stage = STAGE_2;
						break;
					}
				case STAGE_2:
					{
						g_stage = STAGE_3;
						break;
					}
				}
				
				g_moveLeft[nCntSelect] = false;
			}
		}

		if( g_moveRight[nCntSelect] == true )
		{
			g_select[nCntSelect].posSelect.x += SELECT_SPEED;
			g_select[nCntSelect + 1].posSelect.x += SELECT_SPEED;

			if( g_select[nCntSelect + 1].posSelect.x >= SCREEN_WIDTH * 2 )
			{
				g_select[nCntSelect].posSelect = D3DXVECTOR3( SCREEN_WIDTH / 2 , SCREEN_HEIGHT /2 , 0.0f );
				g_select[nCntSelect + 1].posSelect = D3DXVECTOR3( SCREEN_WIDTH * 2 , SCREEN_HEIGHT /2 , 0.0f );

				switch( g_stage )
				{
				case STAGE_2:
					{
						g_stage = STAGE_1;
						break;
					}
				case STAGE_3:
					{
						g_stage = STAGE_2;
						break;
					}
				}

				g_moveRight[nCntSelect] = false;
			}
		}
	}

	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MAX ; nCntSelect++ )
	{

		//ふわふわ動かす
		g_select[nCntSelect].moveY += SELECT_MOVEY;
		g_select[nCntSelect].posSelect.y += sinf(g_select[nCntSelect].moveY);

		//回転初期化
		if( g_select[nCntSelect].moveY > D3DX_PI * 2 )
		{
			g_select[nCntSelect].moveY = 0.0f;
		}


		//座標更新/////////////////////////////////////////////////////////////////
		VERTEX_2D *pVtx;
		g_select[nCntSelect].pVtxBuffSelect -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		pVtx[0].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x - g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y - g_select[nCntSelect].heightSelect , 0.0f );
		pVtx[1].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x + g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y - g_select[nCntSelect].heightSelect , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x - g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y + g_select[nCntSelect].heightSelect , 0.0f );
		pVtx[3].pos = D3DXVECTOR3( g_select[nCntSelect].posSelect.x + g_select[nCntSelect].widthSelect , g_select[nCntSelect].posSelect.y + g_select[nCntSelect].heightSelect , 0.0f );

		g_select[nCntSelect].pVtxBuffSelect -> Unlock();
	}

	//ゲーム画面へ移動/////////////////////////////////////////////////////////
	for( int cntMove = 0 ; cntMove < SELECT_MOVE_MAX ; cntMove++ )
	{
		if( g_moveLeft[cntMove] == false && g_moveRight[cntMove] == false)//動いていない状態でゲーム画面へ
		{
			if( GetKeyboardPress( DIK_RETURN ) )
			{
				SetFade( FADE_OUT , MODE_GAME );
			}
		}
	}

	//どんぐり、ライフ描画用///////////////////////////////////////////////////
	UpdateAcornCnt();
	UpdateLifeCnt();

	//移動防止
	for( int nCntAcornCnt = 0 , posAcornCntX = 0 , posLifeCntX = 0 ;  nCntAcornCnt < ACORNCNT_MAX ; nCntAcornCnt++ , posAcornCntX -= ACORN_TEX_WIDTH ,  posLifeCntX -= LIFECNT_TEX_WIDTH )
	{
		pAcornCnt -> posAcornCnt = D3DXVECTOR3( 200.0f + posAcornCntX , 40.0f , 0.0f );

		pLifeCnt -> posLifeCnt    = D3DXVECTOR3( 660.0f + posLifeCntX , LIFECNT_POSY , 0.0f );

		pAcornCnt++;
		pLifeCnt++;
	}

	UpdateSelectAro();

}

/******************************************************************************
* 関数名：DrawSelect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawSelect( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int nCntSelect = 0 ;  nCntSelect < SELECT_MAX ; nCntSelect++ )
	{
		//頂点バッファをデータストリームにバインド
		pDevice -> SetStreamSource( 0 , g_select[nCntSelect].pVtxBuffSelect , 0 , sizeof( VERTEX_2D ));

		//頂点フォーマット
		pDevice -> SetFVF( FVF_VERTEX_2D );

		pDevice -> SetTexture( 0 , g_pTextureSelect[nCntSelect] );

		//ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
	}


	//どんぐり、ライフ表示
	DrawAcornCnt();
	DrawLifeCnt();

	DrawSelectAro();
}

/******************************************************************************
* 関数名：GetSelectMode
* 
* 引数  ：
* 戻り値：
* 説明  ：選択したステージを返す
******************************************************************************/
int GetSelectMode( void )
{
	return g_stage;
}

/******************************************************************************
* 関数名：GetSelect
* 
* 引数  ：
* 戻り値：
* 説明  ：選択したステージを返す
******************************************************************************/
SELECT *GetSelect( void )
{
	return g_select;
}
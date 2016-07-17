/******************************************************************************
* タイトル  :
* ファイル名:tiele.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "title.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
D3DXMATRIX g_mtxWorldTitle;//billboardのワールドマトリックス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;//頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureTitle[TITLE_TEX_MAX];
TITLE g_Title[TITLE_TEX_MAX];

/******************************************************************************
* 関数名：InitTitle
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitTitle( void )
{

	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CAMERA *pCamera = GetCamera();

	//カメラ位置(タイトル初期位置)
	pCamera -> posV = D3DXVECTOR3( 0 , 0 , -50 );//位置
	pCamera -> posR = D3DXVECTOR3( 0 , 0 , 10 );//注視点

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * TITLE_TEX_MAX * 4,
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_3D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffTitle ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	for( int cntTex = 0 ; cntTex < TITLE_TEX_MAX ; cntTex++ )
	{
		g_pTextureTitle[cntTex] = NULL;
	}

	//テクスチャ読み込み
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo004.png" , &g_pTextureTitle[0] );//ぽん
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo005.png" , &g_pTextureTitle[1] );//ぽん
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo001.png" , &g_pTextureTitle[2] );//たぬき
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo002.png" , &g_pTextureTitle[3] );//バック
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/title_logo003.png" , &g_pTextureTitle[4] );//葉っぱ
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/press_enter.png" , &g_pTextureTitle[5] );//enterキー
	}

	float logoWidth , logoHeight;

	VERTEX_3D *pVtx;
	g_pVtxBuffTitle -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntLogo = 0 , cntVtx = 0 ; cntLogo < TITLE_TEX_MAX ; cntLogo++ , cntVtx += 4 )
	{

		switch( cntLogo )
		{
		case 0:
			{
				logoWidth = TITLE_LOGO1_WIDTH;
				logoHeight = TITLE_LOGO1_HEIGHT;
				break;
			}
		case 1:
			{
				logoWidth = TITLE_LOGO1_WIDTH;
				logoHeight = TITLE_LOGO1_HEIGHT;
				break;
			}
		case 2:
			{
				logoWidth = TITLE_LOGO2_WIDTH;
				logoHeight = TITLE_LOGO2_HEIGHT;
				break;
			}
		case 3:
			{
				logoWidth = TITLE_LOGO3_WIDTH;
				logoHeight = TITLE_LOGO3_HEIGHT;
				break;
			}
		case 4:
			{
				logoWidth = TITLE_LOGO4_WIDTH;
				logoHeight = TITLE_LOGO4_HEIGHT;
				break;
			}
		case 5:
			{
				logoWidth = TITLE_LOGO5_WIDTH;
				logoHeight = TITLE_LOGO5_HEIGHT;
				break;
			}
		}

		//座標設定
		pVtx[cntVtx].pos     = D3DXVECTOR3( - logoWidth / 2 ,   logoHeight / 2 , 0.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3(   logoWidth / 2 ,   logoHeight / 2 , 0.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( - logoWidth / 2 , - logoHeight / 2 , 0.0f );
		pVtx[cntVtx + 3].pos = D3DXVECTOR3(   logoWidth / 2 , - logoHeight / 2 , 0.0f );


		//頂点カラー設定
		pVtx[cntVtx].col     = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		pVtx[cntVtx + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );

		//テクスチャ
		pVtx[cntVtx].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 3].tex = D3DXVECTOR2( 1 , 1 );
	
		//法線
		pVtx[cntVtx].nor     = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 1].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 2].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 3].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
	}

	g_pVtxBuffTitle -> Unlock();

	g_Title[0].posTitle = D3DXVECTOR3( -15.0f , 10.0f , 0.0f );
	g_Title[0].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[0].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[1].posTitle = D3DXVECTOR3( -5.0f , 10.0f , 0.0f );
	g_Title[1].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[1].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[2].posTitle = D3DXVECTOR3( 5.0f , -3.0f , 0.0f );
	g_Title[2].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[2].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[3].posTitle = D3DXVECTOR3( 0.0f , 5.0f , 10.0f );
	g_Title[3].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[3].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[4].posTitle = D3DXVECTOR3( 5.0f , 0.0f , 0.0f );
	g_Title[4].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[4].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

	g_Title[5].posTitle = D3DXVECTOR3( 0.0f , -15.0f , 0.0f );
	g_Title[5].rotTitle = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
	g_Title[5].sclTitle = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	

	return S_OK;
}

/******************************************************************************
* 関数名：IninitTitle
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitTitle( void )
{
	for( int cntLogo = 0 ; cntLogo < TITLE_TEX_MAX ; cntLogo++ )
	{
		if( g_pTextureTitle[cntLogo] != NULL )
		{
			g_pTextureTitle[cntLogo] -> Release();
			g_pTextureTitle[cntLogo] = NULL;
		}
	}

	if( g_pVtxBuffTitle !=NULL )
	{
		g_pVtxBuffTitle -> Release();
		g_pVtxBuffTitle = NULL;
	}
}

/******************************************************************************
* 関数名：UpdateTitle
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateTitle( void )
{
	if( GetKeyboardPress( DIK_RETURN ) )
	{
		SetFade( FADE_OUT , MODE_SELECT );
	}
}

/******************************************************************************
* 関数名：DrawTitle
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawTitle( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	for( int cntLogo = 0 ; cntLogo < TITLE_TEX_MAX ; cntLogo++ )
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity( &g_mtxWorldTitle );

		D3DXMatrixScaling( &mtxScl , g_Title[cntLogo].sclTitle.x , g_Title[cntLogo].sclTitle.y , g_Title[cntLogo].sclTitle.z );
	
		//スケールを反映
		D3DXMatrixMultiply( &g_mtxWorldTitle , &g_mtxWorldTitle , &mtxScl );

		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Title[cntLogo].rotTitle.x , g_Title[cntLogo].rotTitle.y , g_Title[cntLogo].rotTitle.z );

		//回転の反映
		D3DXMatrixMultiply( &g_mtxWorldTitle , &g_mtxWorldTitle , &mtxRot );

		D3DXMatrixTranslation( &mtxTrans , g_Title[cntLogo].posTitle.x , g_Title[cntLogo].posTitle.y , g_Title[cntLogo].posTitle.z );

		//移動の反映
		D3DXMatrixMultiply( &g_mtxWorldTitle , &g_mtxWorldTitle , &mtxTrans );

		//ワールドマトリックスの設定
		pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldTitle );

		//頂点バッファをデータストリームにバインド
		pDevice -> SetStreamSource( 0 , g_pVtxBuffTitle , 0 , sizeof( VERTEX_3D ));

		//頂点フォーマット
		pDevice -> SetFVF( FVF_VERTEX_3D );

		pDevice -> SetTexture( 0 , g_pTextureTitle[cntLogo] );

		//アルファテスト
		pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
		pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
		pDevice -> SetRenderState( D3DRS_ALPHAREF,0);

		//ポリゴンの描画
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , cntLogo * 4 , 2 );

		//アルファテスト戻す
		pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
		pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_ALWAYS );
		pDevice -> SetRenderState( D3DRS_ALPHAREF,0);
	}

}
/******************************************************************************
* タイトル  :
* ファイル名:box.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2016/01/21
*******************************************************************************
* 更新履歴:-2016/01/21 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureBox[BOX_TEX_MAX];
D3DXMATRIX g_mtxWorldBox;

BOX g_Box[BOX_MAX][BOX_SURFACE_MAX];

/******************************************************************************
* 関数名：InitBox
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitBox( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
		{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( BOX_NUM_VTX ),
														D3DUSAGE_WRITEONLY ,
														FVF_VERTEX_3D ,
														D3DPOOL_MANAGED ,
														&g_Box[cntBox][cntSurface].pVtxBuffBox ,
														NULL ) ) )
			{
				return E_FAIL;
			}
		}
	}

	for( int cntTex = 0 ;  cntTex < BOX_TEX_MAX ; cntTex++ )
	{
		g_pTextureBox[cntTex] = NULL;
	}

	//テクスチャ読み込み
	if( BOX_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/boxNomal001.jpg" , &g_pTextureBox[0] );
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/boxSpring000.jpg" , &g_pTextureBox[1] );
	}


	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{

		for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
		{
			VERTEX_3D *pVtx;
			g_Box[cntBox][cntSurface].pVtxBuffBox -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			g_Box[cntBox][cntSurface].posBox = D3DXVECTOR3( 0.0f , 5.0f , 0.0f );
			g_Box[cntBox][cntSurface].rotBox = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Box[cntBox][cntSurface].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
			g_Box[cntBox][cntSurface].boxUse = false;
			g_Box[cntBox][cntSurface].boxSpringHit = false;

			//座標設定
			pVtx[0].pos     = D3DXVECTOR3( - BOX_WIDTH / 2 ,   BOX_HEIGHT / 2 , 0.0f );
			pVtx[1].pos = D3DXVECTOR3(   BOX_WIDTH / 2 ,   BOX_HEIGHT / 2 , 0.0f );
			pVtx[2].pos = D3DXVECTOR3( - BOX_WIDTH / 2 , - BOX_HEIGHT / 2 , 0.0f );
			pVtx[3].pos = D3DXVECTOR3(   BOX_WIDTH / 2 , - BOX_HEIGHT / 2 , 0.0f );


			//頂点カラー設定
			for( int cntCol = 0 ; cntCol < BOX_NUM_VTX ; cntCol++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 255 , 100 , 100, 255 );
			}

			//テクスチャ
			pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
			pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
			pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
			pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
			//法線
			for( int cntNor = 0 ; cntNor < BOX_NUM_VTX ; cntNor++ )
			{
				pVtx[cntNor].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
			}

			g_Box[cntBox][cntSurface].pVtxBuffBox -> Unlock();

		}

		//手前
		g_Box[cntBox][0].posBox = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Box[cntBox][0].rotBox = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Box[cntBox][0].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//奥
		g_Box[cntBox][1].posBox = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Box[cntBox][1].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][1].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//右
		g_Box[cntBox][2].posBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][2].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][2].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//左
		g_Box[cntBox][3].posBox = D3DXVECTOR3( 0, 0.0f , 0.0f );
		g_Box[cntBox][3].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][3].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//上
		g_Box[cntBox][4].posBox = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Box[cntBox][4].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][4].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//下
		g_Box[cntBox][5].posBox = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Box[cntBox][5].rotBox = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Box[cntBox][5].sclBox = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	}

	return S_OK;
}

/******************************************************************************
* 関数名：UninitBox
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitBox( void )
{
	for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
	{
		for( int cntTex = 0 ;  cntTex < BOX_TEX_MAX ; cntTex++ )
		{
			if( g_pTextureBox[cntTex] != NULL )
			{
				g_pTextureBox[cntTex] -> Release();
				g_pTextureBox[cntTex] = NULL;
			}
		}
	}

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
		{
			if( g_Box[cntBox][cntSurface].pVtxBuffBox !=NULL )
			{
				g_Box[cntBox][cntSurface].pVtxBuffBox -> Release();
				g_Box[cntBox][cntSurface].pVtxBuffBox = NULL;
			}
		}
	}
}

/******************************************************************************
* 関数名：UpdateBox
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateBox( void )
{

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		VERTEX_3D *pVtx;
		g_Box[cntBox][0].pVtxBuffBox -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		switch( g_Box[cntBox][0].boxPattarn )
		{
		case BOX_NOMAL:
			{
				if( g_Box[cntBox][0].boxUse == false )//消去
				{

					for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
					{
						g_Box[cntBox][cntSurface].boxUse = false;
					}
				}
				break;
			}
		case BOX_SPRING:
			{
				break;
			}
			}
		g_Box[cntBox][0].pVtxBuffBox -> Unlock();
	}
}

/******************************************************************************
* 関数名：DrawBox
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawBox( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		if( g_Box[cntBox][0].boxUse == true )
		{
			for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity( &g_mtxWorldBox );

				D3DXMatrixScaling( &mtxScl , g_Box[cntBox][cntSurface].sclBox.x , g_Box[cntBox][cntSurface].sclBox.y , g_Box[cntBox][cntSurface].sclBox.z );
	
				//スケールを反映
				D3DXMatrixMultiply( &g_mtxWorldBox , &g_mtxWorldBox , &mtxScl );

				D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Box[cntBox][cntSurface].rotBox.x , g_Box[cntBox][cntSurface].rotBox.y , g_Box[cntBox][cntSurface].rotBox.z );

				//回転の反映
				D3DXMatrixMultiply( &g_mtxWorldBox , &g_mtxWorldBox , &mtxRot );

				D3DXMatrixTranslation( &mtxTrans , g_Box[cntBox][cntSurface].posBox.x , g_Box[cntBox][cntSurface].posBox.y , g_Box[cntBox][cntSurface].posBox.z );

				//移動の反映
				D3DXMatrixMultiply( &g_mtxWorldBox , &g_mtxWorldBox , &mtxTrans );

				//ワールドマトリックスの設定
				pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldBox );

				//頂点バッファをデータストリームにバインド
				pDevice -> SetStreamSource( 0 , g_Box[cntBox][cntSurface].pVtxBuffBox , 0 , sizeof( VERTEX_3D ));

				//頂点フォーマット
				pDevice -> SetFVF( FVF_VERTEX_3D );


				//テクスチャの切り替え
				switch( g_Box[cntBox][cntSurface].boxPattarn )
				{
				case BOX_NOMAL:
					{
						pDevice -> SetTexture( 0 , g_pTextureBox[0] );
						break;
					}
				case BOX_SPRING:
					{
						pDevice -> SetTexture( 0 , g_pTextureBox[1] );
						break;
					}
				}

				//ポリゴンの描画
				pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );
				
			}
		}
	}
}

/******************************************************************************
* 関数名：SetBox
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetBox( D3DXVECTOR3 pos , BOXPATTARN boxPattarn )
{
	for( int cntBox = 0 ; cntBox < BOX_MAX ; cntBox++ )
	{
		if( g_Box[cntBox][0].boxUse == false )
		{
			g_Box[cntBox][0].setPosBox = pos;

			//手前
			g_Box[cntBox][0].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z - BOX_HEIGHT / 2 );
			g_Box[cntBox][0].rotBox = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Box[cntBox][0].boxPattarn = boxPattarn;

			//奥
			g_Box[cntBox][1].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z + BOX_HEIGHT / 2 );
			g_Box[cntBox][1].rotBox = D3DXVECTOR3( D3DX_PI * 1.0f , 0.0f , 0.0f );
			g_Box[cntBox][1].boxPattarn = boxPattarn;

			//右
			g_Box[cntBox][2].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x + BOX_WIDTH / 2 , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][2].rotBox = D3DXVECTOR3( -D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Box[cntBox][2].boxPattarn = boxPattarn;

			//左
			g_Box[cntBox][3].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x - BOX_WIDTH / 2 , g_Box[cntBox][0].setPosBox.y , g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][3].rotBox = D3DXVECTOR3( D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Box[cntBox][3].boxPattarn = boxPattarn;

			//上
			g_Box[cntBox][4].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y + BOX_HEIGHT / 2 , g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][4].rotBox = D3DXVECTOR3( 0.0f , D3DX_PI * 0.5f , 0.0f );
			g_Box[cntBox][4].boxPattarn = boxPattarn;

			//下
			g_Box[cntBox][5].posBox = D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y  - BOX_HEIGHT / 2, g_Box[cntBox][0].setPosBox.z );
			g_Box[cntBox][5].rotBox = D3DXVECTOR3( 0.0f , -D3DX_PI * 0.5f , 0.0f );
			g_Box[cntBox][5].boxPattarn = boxPattarn;

			for( int cntSurface = 0 ; cntSurface < BOX_SURFACE_MAX ; cntSurface++ )
			{
				g_Box[cntBox][cntSurface].boxUse = true;
			}
			
			//どんぐりせっち
			if( g_Box[cntBox][0].boxPattarn == BOX_NOMAL )
			{
				SetAcorn( D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x + 5, g_Box[cntBox][0].setPosBox.y - BOX_HEIGHT / 2 , g_Box[cntBox][0].setPosBox.z ) );
				SetAcorn( D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x , g_Box[cntBox][0].setPosBox.y - BOX_HEIGHT / 2, g_Box[cntBox][0].setPosBox.z ) );
				SetAcorn( D3DXVECTOR3( g_Box[cntBox][0].setPosBox.x - 5, g_Box[cntBox][0].setPosBox.y - BOX_HEIGHT / 2, g_Box[cntBox][0].setPosBox.z ) );
			}

			//影設置
			SetShadow( g_Box[cntBox][0].posBox , SHADOW_BOX );
			break;
		}
	}
}

/******************************************************************************
* 関数名：GetModel
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
BOX *GetBox( void )
{
	return &g_Box[0][0];
}
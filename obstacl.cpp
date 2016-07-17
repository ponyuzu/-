/******************************************************************************
* タイトル  :
* ファイル名:obstacl.cpp
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
LPDIRECT3DTEXTURE9 g_pTextureObstacl = NULL;
D3DXMATRIX g_mtxWorldObstacl;

OBSTACL g_Obstacl[OBSTACL_MAX][OBSTACL_SURFACE_MAX];

/******************************************************************************
* 関数名：InitObstacl
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitObstacl( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{

		for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
		{

			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( OBSTACL_NUM_VTX ),
														D3DUSAGE_WRITEONLY ,
														FVF_VERTEX_3D ,
														D3DPOOL_MANAGED ,
														&g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl ,
														NULL ) ) )
			{
				return E_FAIL;
			}

		}
	}

	g_pTextureObstacl = NULL;

	//テクスチャ読み込み
	if( OBSTACL_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/obstacl002.jpg" , &g_pTextureObstacl );
	}

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{
		for( int cntSurface = 0  ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++  )
		{
			VERTEX_3D *pVtx;
			g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );


			g_Obstacl[cntObstacl][cntSurface].posObstacl = D3DXVECTOR3( 0.0f , 5.0f , 0.0f );
			g_Obstacl[cntObstacl][cntSurface].rotObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][cntSurface].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
			g_Obstacl[cntObstacl][cntSurface].obstaclUse = false;

			//座標設定
			pVtx[0].pos     = D3DXVECTOR3( - OBSTACL_WIDTH / 2 ,   OBSTACL_HEIGHT / 2 , 0.0f );
			pVtx[1].pos = D3DXVECTOR3(   OBSTACL_WIDTH / 2 ,   OBSTACL_HEIGHT / 2 , 0.0f );
			pVtx[2].pos = D3DXVECTOR3( - OBSTACL_WIDTH / 2 , - OBSTACL_HEIGHT / 2 , 0.0f );
			pVtx[3].pos = D3DXVECTOR3(   OBSTACL_WIDTH / 2 , - OBSTACL_HEIGHT / 2 , 0.0f );


			//頂点カラー設定
			for( int cntCol = 0 ; cntCol < OBSTACL_NUM_VTX ; cntCol++ )
			{
				pVtx[cntCol].col = D3DCOLOR_RGBA( 100 , 100 , 100, 255 );
			}

			//テクスチャ
			pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
			pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
			pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
			pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
			//法線
			for( int cntNor = 0 ; cntNor < OBSTACL_NUM_VTX ; cntNor++ )
			{
				pVtx[cntNor].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
			}
			g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl -> Unlock();
		}

		//手前
		g_Obstacl[cntObstacl][0].posObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Obstacl[cntObstacl][0].rotObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][0].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//奥
		g_Obstacl[cntObstacl][1].posObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0 );
		g_Obstacl[cntObstacl][1].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][1].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//右
		g_Obstacl[cntObstacl][2].posObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][2].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][2].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//左
		g_Obstacl[cntObstacl][3].posObstacl = D3DXVECTOR3( 0, 0.0f , 0.0f );
		g_Obstacl[cntObstacl][3].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][3].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//上
		g_Obstacl[cntObstacl][4].posObstacl = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Obstacl[cntObstacl][4].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][4].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

		//下
		g_Obstacl[cntObstacl][5].posObstacl = D3DXVECTOR3( 0.0f , 0 , 0.0f );
		g_Obstacl[cntObstacl][5].rotObstacl = D3DXVECTOR3( 0 , 0.0f , 0.0f );
		g_Obstacl[cntObstacl][5].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
	}

	return S_OK;
}

/******************************************************************************
* 関数名：UninitObstacl
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitObstacl( void )
{
	for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
	{
		if( g_pTextureObstacl != NULL )
		{
			g_pTextureObstacl -> Release();
			g_pTextureObstacl = NULL;
		}
	}

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{

		for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
		{
			if( g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl !=NULL )
			{
				g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl -> Release();
				g_Obstacl[cntObstacl][cntSurface].pVtxBuffObstacl = NULL;
			}
		}
	}
}

/******************************************************************************
* 関数名：UpdateObstacl
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateObstacl( void )
{


}

/******************************************************************************
* 関数名：DrawObstacl
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawObstacl( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{
		for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
		{
			if( g_Obstacl[cntObstacl][cntSurface].obstaclUse == true )
			{
				//ワールドマトリックスの初期化
				D3DXMatrixIdentity( &g_mtxWorldObstacl );

				D3DXMatrixScaling( &mtxScl , g_Obstacl[cntObstacl][cntSurface].sclObstacl.x , g_Obstacl[cntObstacl][cntSurface].sclObstacl.y , g_Obstacl[cntObstacl][cntSurface].sclObstacl.z );
	
				//スケールを反映
				D3DXMatrixMultiply( &g_mtxWorldObstacl , &g_mtxWorldObstacl , &mtxScl );

				D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Obstacl[cntObstacl][cntSurface].rotObstacl.x , g_Obstacl[cntObstacl][cntSurface].rotObstacl.y , g_Obstacl[cntObstacl][cntSurface].rotObstacl.z );

				//回転の反映
				D3DXMatrixMultiply( &g_mtxWorldObstacl , &g_mtxWorldObstacl , &mtxRot );

				D3DXMatrixTranslation( &mtxTrans , g_Obstacl[cntObstacl][cntSurface].posObstacl.x , g_Obstacl[cntObstacl][cntSurface].posObstacl.y , g_Obstacl[cntObstacl][cntSurface].posObstacl.z );

				//移動の反映
				D3DXMatrixMultiply( &g_mtxWorldObstacl , &g_mtxWorldObstacl , &mtxTrans );

				//ワールドマトリックスの設定
				pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldObstacl );

				//頂点バッファをデータストリームにバインド
				pDevice -> SetStreamSource( 0 , g_Obstacl[cntObstacl][cntObstacl].pVtxBuffObstacl , 0 , sizeof( VERTEX_3D ));

				//頂点フォーマット
				pDevice -> SetFVF( FVF_VERTEX_3D );

				pDevice -> SetTexture( 0 , g_pTextureObstacl );

				//ポリゴンの描画
				pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );

			}
		}
	}
}

/******************************************************************************
* 関数名：SetObstacl
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetObstacl( D3DXVECTOR3 pos , OBSTACLPATTARN obstaclPattarn )
{
	for( int cntObstacl = 0 ; cntObstacl < OBSTACL_MAX ; cntObstacl++ )
	{
		if( g_Obstacl[cntObstacl][0].obstaclUse == false )
		{
			g_Obstacl[cntObstacl][0].setPosObstacl = pos;
			g_Obstacl[cntObstacl][0].obstaclPattarn = obstaclPattarn;

			//手前
			g_Obstacl[cntObstacl][0].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z - OBSTACL_HEIGHT / 2 );
			g_Obstacl[cntObstacl][0].rotObstacl = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][0].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//奥
			g_Obstacl[cntObstacl][1].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z + OBSTACL_HEIGHT / 2 );
			g_Obstacl[cntObstacl][1].rotObstacl = D3DXVECTOR3( D3DX_PI * 1.0f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][1].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//右
			g_Obstacl[cntObstacl][2].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x + OBSTACL_WIDTH / 2 , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][2].rotObstacl = D3DXVECTOR3( -D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][2].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//左
			g_Obstacl[cntObstacl][3].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x - OBSTACL_WIDTH / 2 , g_Obstacl[cntObstacl][0].setPosObstacl.y , g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][3].rotObstacl = D3DXVECTOR3( D3DX_PI * 0.5f , 0.0f , 0.0f );
			g_Obstacl[cntObstacl][3].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//上
			g_Obstacl[cntObstacl][4].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y + OBSTACL_HEIGHT / 2 , g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][4].rotObstacl = D3DXVECTOR3( 0.0f , D3DX_PI * 0.5f , 0.0f );
			g_Obstacl[cntObstacl][4].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			//下
			g_Obstacl[cntObstacl][5].posObstacl = D3DXVECTOR3( g_Obstacl[cntObstacl][0].setPosObstacl.x , g_Obstacl[cntObstacl][0].setPosObstacl.y  - OBSTACL_HEIGHT / 2, g_Obstacl[cntObstacl][0].setPosObstacl.z );
			g_Obstacl[cntObstacl][5].rotObstacl = D3DXVECTOR3( 0.0f , -D3DX_PI * 0.5f , 0.0f );
			g_Obstacl[cntObstacl][5].sclObstacl = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );

			for( int cntSurface = 0 ; cntSurface < OBSTACL_SURFACE_MAX ; cntSurface++ )
			{
				g_Obstacl[cntObstacl][cntSurface].obstaclUse = true;
			}
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
OBSTACL *GetObstacl( void )
{
	return &g_Obstacl[0][0];
}
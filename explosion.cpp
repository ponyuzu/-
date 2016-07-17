/******************************************************************************
* タイトル  :
* ファイル名:explosion.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/11/17
*******************************************************************************
* 更新履歴:-2015/11/17 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
D3DXMATRIX g_mtxWorldExplosion;//billboardのワールドマトリックス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;//頂点バッファ
LPDIRECT3DTEXTURE9 g_pTextureExplosion = NULL;
EXPLOSION g_Explosion[EXPLOSION_MAX];

/******************************************************************************
* 関数名：InitExplosion
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitExplosion( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( EXPLOSION_NUM_VTX * EXPLOSION_MAX ),
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_3D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffExplosion ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_pTextureExplosion = NULL;

	//テクスチャ読み込み
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/explosion000.png" , &g_pTextureExplosion );
	}

	VERTEX_3D *pVtx;
	g_pVtxBuffExplosion -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntExplosion = 0 , cntVtx = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ , cntVtx += 4 )
	{
		g_Explosion[cntExplosion].posExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Explosion[cntExplosion].rotExplosion = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Explosion[cntExplosion].sclExplosion = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Explosion[cntExplosion].explosionUse = false;
		g_Explosion[cntExplosion].nCounterAnim = 0;
		g_Explosion[cntExplosion].nPatternAnim = 0;

		//座標設定
		pVtx[cntVtx].pos     = D3DXVECTOR3( - EXPLOSION_WIDTH / 2.0f , EXPLOSION_HEIGHT / 2.0f   , 0.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3( EXPLOSION_WIDTH / 2.0f   , EXPLOSION_HEIGHT / 2.0f   , 0.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( - EXPLOSION_WIDTH / 2.0f , - EXPLOSION_HEIGHT / 2.0f , 0.0f );
		pVtx[cntVtx + 3].pos = D3DXVECTOR3( EXPLOSION_WIDTH / 2.0f   , - EXPLOSION_HEIGHT / 2.0f , 0.0f );


		//頂点カラー設定
		pVtx[cntVtx].col = D3DCOLOR_RGBA( 255 , 255 , 255, 255 );
		pVtx[cntVtx + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );
		pVtx[cntVtx + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 255 );

		//テクスチャ
		pVtx[cntVtx + 0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 3].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH , 1 );
	
		//法線
		pVtx[cntVtx].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 1].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 2].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 3].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
	}

	g_pVtxBuffExplosion -> Unlock();


	return S_OK;
}

/******************************************************************************
* 関数名：UninitExplosion
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitExplosion( void )
{
	if( g_pTextureExplosion != NULL )
	{
		g_pTextureExplosion -> Release();
		g_pTextureExplosion = NULL;
	}

	if( g_pVtxBuffExplosion !=NULL )
	{
		g_pVtxBuffExplosion -> Release();
		g_pVtxBuffExplosion = NULL;
	}

}

/******************************************************************************
* 関数名：UpdateExplosion
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateExplosion( void )
{
	VERTEX_3D *pVtx;
	g_pVtxBuffExplosion -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntExplosion = 0 , cntVtx = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ , cntVtx += 4 )
	{
		if( g_Explosion[cntExplosion].explosionUse == true )
		{
			if( g_Explosion[cntExplosion].nPatternAnim < 7 )
			{
				g_Explosion[cntExplosion].nCounterAnim++;

				if( EXPLOSION_TEX_TIME == g_Explosion[cntExplosion].nCounterAnim )
				{
					g_Explosion[cntExplosion].nPatternAnim++;

					//テクスチャ
					pVtx[cntVtx + 0].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * g_Explosion[cntExplosion].nPatternAnim , 0 );
					pVtx[cntVtx + 1].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * ( g_Explosion[cntExplosion].nPatternAnim + 1 ) , 0 );
					pVtx[cntVtx + 2].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * g_Explosion[cntExplosion].nPatternAnim , 1 );
					pVtx[cntVtx + 3].tex = D3DXVECTOR2( EXPLOSION_TEX_WIDTH * ( g_Explosion[cntExplosion].nPatternAnim + 1 ) , 1 );

					g_Explosion[cntExplosion].nCounterAnim = 0;
				}
			}
			else
			{
				g_Explosion[cntExplosion].explosionUse = false;
			}
		}
	}

	g_pVtxBuffExplosion -> Unlock();
}


/******************************************************************************
* 関数名：DrawExplosion
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawExplosion( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	//アルファテスト
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );

	//Zテスト停止
	pDevice -> SetRenderState( D3DRS_ZENABLE , FALSE );

	for( int cntExplosion = 0 , nCntVtx = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ , nCntVtx += 4 )
	{
		if( g_Explosion[cntExplosion].explosionUse == true )
		{
			D3DXMatrixIdentity( &g_mtxWorldExplosion );

			//ビューマトリックス取得
			pDevice -> GetTransform( D3DTS_VIEW , &mtxView );

			//逆行列を求める
			D3DXMatrixInverse( &g_mtxWorldExplosion , NULL , &mtxView );

			g_mtxWorldExplosion._41 = 0.0f;
			g_mtxWorldExplosion._42 = 0.0f;
			g_mtxWorldExplosion._43 = 0.0f;

			D3DXMatrixScaling( &mtxScl , 1.0f , 1.0f , 1.0f );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldExplosion , &g_mtxWorldExplosion , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Explosion[cntExplosion].rotExplosion.x , g_Explosion[cntExplosion].rotExplosion.y , g_Explosion[cntExplosion].rotExplosion.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldExplosion , &g_mtxWorldExplosion , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Explosion[cntExplosion].posExplosion.x , g_Explosion[cntExplosion].posExplosion.y , g_Explosion[cntExplosion].posExplosion.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldExplosion , &g_mtxWorldExplosion , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldExplosion );

			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_pVtxBuffExplosion , 0 , sizeof( VERTEX_3D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureExplosion );

			//ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , nCntVtx , 2 );

		}
	}

	//Zテスト再開
	pDevice -> SetRenderState( D3DRS_ZENABLE , TRUE );

	//アルファテスト戻す
	pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
	pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_ALWAYS );
	pDevice -> SetRenderState( D3DRS_ALPHAREF,0 );
}
/******************************************************************************
* 関数名：SetExplosion
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetExplosion( D3DXVECTOR3 pos )
{
	for( int cntExplosion = 0 ; cntExplosion < EXPLOSION_MAX ; cntExplosion++ )
	{
		if( g_Explosion[cntExplosion].explosionUse == false )
		{
			g_Explosion[cntExplosion].nCounterAnim = 0;
			g_Explosion[cntExplosion].nPatternAnim = 0;
			g_Explosion[cntExplosion].posExplosion = pos;
			g_Explosion[cntExplosion].explosionUse = true;
			break;
		}
	}
}
/******************************************************************************
* 関数名：GetExplosion
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
EXPLOSION *GetExplosion( void )
{
	return g_Explosion;
}
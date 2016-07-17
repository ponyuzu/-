/******************************************************************************
* タイトル  :
* ファイル名:effect.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2016/02/01
*******************************************************************************
* 更新履歴:-2016/02/01 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "result.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
D3DXMATRIX g_mtxWorldEffect;

EFFECT g_Effect[EFFECT_MAX];

/******************************************************************************
* 関数名：InitEffect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitEffect( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//頂点獲得
	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( EFFECT_NUM_VTX ),
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_3D ,
													D3DPOOL_MANAGED ,
													&g_Effect[cntEffect].pVtxBuffEffect ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	g_pTextureEffect = NULL;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/shadow000.jpg" , &g_pTextureEffect );

	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		VERTEX_3D *pVtx;
		g_Effect[cntEffect].pVtxBuffEffect -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_Effect[cntEffect].posEffect    = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Effect[cntEffect].rotEffect    = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Effect[cntEffect].sclEffect    = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Effect[cntEffect].effectHeight = EFFECT_ACORN_HEIGHT;
		g_Effect[cntEffect].effectWidht  = EFFECT_ACORN_WIDTH;
		g_Effect[cntEffect].effectR      = 1.0f;
		g_Effect[cntEffect].effectG      = 1.0f;
		g_Effect[cntEffect].effectB      = 1.0f;
		g_Effect[cntEffect].effectAlpha  = 1.0f;
		g_Effect[cntEffect].effectUse    = false;

		//座標設定
		pVtx[0].pos = D3DXVECTOR3( - g_Effect[cntEffect].effectWidht / 2 ,   g_Effect[cntEffect].effectHeight / 2 , 0.0f );
		pVtx[1].pos = D3DXVECTOR3(   g_Effect[cntEffect].effectWidht / 2 ,   g_Effect[cntEffect].effectHeight / 2 , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( - g_Effect[cntEffect].effectWidht / 2 , - g_Effect[cntEffect].effectHeight / 2 , 0.0f );
		pVtx[3].pos = D3DXVECTOR3(   g_Effect[cntEffect].effectWidht / 2 , - g_Effect[cntEffect].effectHeight / 2 , 0.0f );


		//頂点カラー設定
		for( int addCol = 0 ; addCol < EFFECT_NUM_VTX ; addCol++ )
		{
			pVtx[addCol + 0].col = D3DXCOLOR( g_Effect[cntEffect].effectR , g_Effect[cntEffect].effectG , g_Effect[cntEffect].effectB , g_Effect[cntEffect].effectAlpha );
		}

		//テクスチャ
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
		//法線
		for( int addNor = 0 ; addNor < EFFECT_NUM_VTX ; addNor++ )
		{
			pVtx[addNor + 0].nor = D3DXVECTOR3( 0.0f , 0.0f , 1.0f );
		}

		g_Effect[cntEffect].pVtxBuffEffect -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* 関数名：IninitEffect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitEffect( void )
{
	if( g_pTextureEffect != NULL )
	{
		g_pTextureEffect -> Release();
		g_pTextureEffect = NULL;
	}

	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
			if( g_Effect[cntEffect].pVtxBuffEffect !=NULL )
		{
			g_Effect[cntEffect].pVtxBuffEffect -> Release();
			g_Effect[cntEffect].pVtxBuffEffect = NULL;
		}
	}
}

/******************************************************************************
* 関数名：UpdateEffect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateEffect( void )
{
	//共通エフェクト処理(α値変更)
	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		if( g_Effect[cntEffect].effectUse == true )
		{
			VERTEX_3D *pVtx;
			g_Effect[cntEffect].pVtxBuffEffect -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//α値減らす計算
			g_Effect[cntEffect].effectAlpha += EFFECT_ALPHA;

			//頂点カラー更新
			for( int addCol = 0 ; addCol < EFFECT_NUM_VTX ; addCol++ )
			{
				pVtx[addCol + 0].col = D3DXCOLOR( g_Effect[cntEffect].effectR ,
												  g_Effect[cntEffect].effectG ,
												  g_Effect[cntEffect].effectB ,
												  g_Effect[cntEffect].effectAlpha );
			}

			//描画終了
			if( g_Effect[cntEffect].effectAlpha <= 0.0f )
			{
				g_Effect[cntEffect].effectUse = false;
			}

			g_Effect[cntEffect].pVtxBuffEffect -> Unlock();
		}
	}

}

/******************************************************************************
* 関数名：DrawEffect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawEffect( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		if( g_Effect[cntEffect].effectUse == true )
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_mtxWorldEffect );

			D3DXMatrixScaling( &mtxScl , g_Effect[cntEffect].sclEffect.x , g_Effect[cntEffect].sclEffect.y , g_Effect[cntEffect].sclEffect.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldEffect , &g_mtxWorldEffect , &mtxScl );

			//ビューマトリックス取得
			pDevice -> GetTransform( D3DTS_VIEW , &mtxView );

			//逆行列を求める
			D3DXMatrixInverse( &g_mtxWorldEffect , NULL , &mtxView );

			g_mtxWorldEffect._41 = 0.0f;
			g_mtxWorldEffect._42 = 0.0f;
			g_mtxWorldEffect._43 = 0.0f;

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Effect[cntEffect].rotEffect.x , g_Effect[cntEffect].rotEffect.y , g_Effect[cntEffect].rotEffect.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldEffect , &g_mtxWorldEffect , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Effect[cntEffect].posEffect.x , g_Effect[cntEffect].posEffect.y , g_Effect[cntEffect].posEffect.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldEffect , &g_mtxWorldEffect , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldEffect );

			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_Effect[cntEffect].pVtxBuffEffect , 0 , sizeof( VERTEX_3D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureEffect );


			//アルファテスト
			pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
			pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
			pDevice -> SetRenderState( D3DRS_ALPHAREF,0);

			//レンダーステイトの設定変更
			pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT );
			pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_ONE );

			//ポリゴンの描画
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );

			//レンダーステイトの設定戻す
			pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );
			pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		}
	}
}

/******************************************************************************
* 関数名：SetEffect
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetEffect( D3DXVECTOR3 pos , EFFECTPATTARN pattarn )
{
	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		if( g_Effect[cntEffect].effectUse == false )
		{
			g_Effect[cntEffect].posEffect = pos;
			g_Effect[cntEffect].effectPttrn = pattarn;
			g_Effect[cntEffect].effectAlpha = 1.0f;
			g_Effect[cntEffect].effectUse = true;

			break;
		}
	}
}
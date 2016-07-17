/******************************************************************************
* タイトル  :
* ファイル名:shadow.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/11/12
*******************************************************************************
* 更新履歴:-2015/11/12 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;
D3DXMATRIX g_mtxWorldShadow;

SHADOW g_Shadow[SHADOW_MAX];

int g_CntIdxShadow = 0;//インデックスのカウント

/******************************************************************************
* 関数名：InitShadow
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitShadow( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * SHADOW_NUM_VTX ,
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_3D ,
													D3DPOOL_MANAGED ,
													&g_Shadow[cntShadow].pVtxBuffShadow ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}


	g_pTextureShadow = NULL;

	//テクスチャ読み込み
	if( SHADOW_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/shadow000.jpg" , &g_pTextureShadow );
	}

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		VERTEX_3D *pVtx;
		g_Shadow[cntShadow].pVtxBuffShadow -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_Shadow[cntShadow].posShadow = D3DXVECTOR3( 0.0f , 0.5f , 0.0f );
		g_Shadow[cntShadow].rotShadow = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Shadow[cntShadow].sclShadow = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Shadow[cntShadow].shadowUse = false;
		g_Shadow[cntShadow].shadowHeight = 0.0f;
		g_Shadow[cntShadow].shadowWidth = 0.0f;

		//座標設定
		pVtx[0].pos = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[1].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[2].pos = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[3].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );

		//頂点カラー設定
		pVtx[0].col     = D3DXCOLOR( 1.0f , 1.0f , 1.0f, 0.5f );
		pVtx[1].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[2].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[3].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );

		//テクスチャ
		pVtx[0].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
		//法線
		pVtx[0].nor     = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[1].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[2].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );
		pVtx[3].nor = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );

		g_Shadow[cntShadow].pVtxBuffShadow -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* 関数名：UninitShadow
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitShadow( void )
{
	if( g_pTextureShadow != NULL )
	{
		g_pTextureShadow -> Release();
		g_pTextureShadow = NULL;
	}

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		if( g_Shadow[cntShadow].pVtxBuffShadow !=NULL )
		{
			g_Shadow[cntShadow].pVtxBuffShadow -> Release();
			g_Shadow[cntShadow].pVtxBuffShadow = NULL;
		}
	}
}

/******************************************************************************
* 関数名：UpdateShadow
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateShadow( void )
{
	MODEL *pModel = GetModel();
	BOX *pBox = GetBox();
	ENEMY *pEnemy = GetEnemy();
	ACORN *pAcorn = GetAcorn();
	GOAL *pGoal = GetGoal();

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		VERTEX_3D *pVtx;
		g_Shadow[cntShadow].pVtxBuffShadow -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		//影を誰が使っているか分岐させる/////////////////////////////////////////////////////////////
		if( g_Shadow[cntShadow].shadowUse == true )
		{
			switch( g_Shadow[cntShadow].shadowPattarn )
			{
			case SHADOW_PLAYER:
				{
					g_Shadow[cntShadow].posShadow.x = pModel -> posModel.x;
					g_Shadow[cntShadow].posShadow.z = pModel -> posModel.z;

					g_Shadow[cntShadow].shadowHeight = 30.0f;
					g_Shadow[cntShadow].shadowWidth = 30.0f;
					break;
				}
			case SHADOW_ENEMY:
				{
					
					g_Shadow[cntShadow].posShadow.x = pEnemy -> posEnemy.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pEnemy -> posEnemy.z;

					g_Shadow[cntShadow].shadowHeight = 30.0f;
					g_Shadow[cntShadow].shadowWidth = 30.0f;
					
					if( pEnemy ->useEnemy == false )
					{
						g_Shadow[cntShadow].shadowUse = false;
					}

					pEnemy++;
					break;
				}

			case SHADOW_BOX:
				{
					
					g_Shadow[cntShadow].posShadow.x = pBox -> posBox.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pBox -> posBox.z;

					g_Shadow[cntShadow].shadowHeight = 40.0f;
					g_Shadow[cntShadow].shadowWidth = 40.0f;

					if( pBox -> boxUse == false )
					{
						g_Shadow[cntShadow].shadowUse = false;

					}

					pBox += 6;
				break;
				}

			case SHADOW_ACORN:
				{
					
					g_Shadow[cntShadow].posShadow.x = pAcorn -> posAcorn.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pAcorn -> posAcorn.z;

					g_Shadow[cntShadow].shadowHeight = 10.0f;
					g_Shadow[cntShadow].shadowWidth = 10.0f;

					if( pAcorn->acornUse == false)
					{
						g_Shadow[cntShadow].shadowUse = false;
					}
					pAcorn++;
					break;
				}
			case SHADOW_GOAL:
				{
					g_Shadow[cntShadow].posShadow.x = pGoal -> posGoal.x;
					g_Shadow[cntShadow].posShadow.y = 0.5f;
					g_Shadow[cntShadow].posShadow.z = pGoal -> posGoal.z;

					g_Shadow[cntShadow].shadowHeight = 10.0f;
					g_Shadow[cntShadow].shadowWidth = 10.0f;
					break;
				}
			}
		}

		//設定の更新///////////////////////////////////////////////////////////////////////
		//座標更新
		pVtx[0].pos     = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[1].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f ,   g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[2].pos = D3DXVECTOR3( - g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );
		pVtx[3].pos = D3DXVECTOR3(   g_Shadow[cntShadow].shadowWidth / 2 , 0.0f , - g_Shadow[cntShadow].shadowHeight / 2 );

		//頂点カラー設定
		pVtx[0].col     = D3DXCOLOR( 1.0f , 1.0f , 1.0f, 0.5f );
		pVtx[1].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[2].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );
		pVtx[3].col = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 0.5f );

		g_Shadow[cntShadow].pVtxBuffShadow -> Unlock();
	}
	
}

/******************************************************************************
* 関数名：DrawShadow
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawShadow( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;

	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		if( g_Shadow[cntShadow].shadowUse == true )
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_mtxWorldShadow );

			D3DXMatrixScaling( &mtxScl , g_Shadow[cntShadow].sclShadow.x , g_Shadow[cntShadow].sclShadow.y , g_Shadow[cntShadow].sclShadow.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldShadow , &g_mtxWorldShadow , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Shadow[cntShadow].rotShadow.x , g_Shadow[cntShadow].rotShadow.y , g_Shadow[cntShadow].rotShadow.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldShadow , &g_mtxWorldShadow , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Shadow[cntShadow].posShadow.x , g_Shadow[cntShadow].posShadow.y , g_Shadow[cntShadow].posShadow.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldShadow , &g_mtxWorldShadow , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldShadow );

			//頂点バッファをデータストリームにバインド
			pDevice -> SetStreamSource( 0 , g_Shadow[0].pVtxBuffShadow , 0 , sizeof( VERTEX_3D ));

			//頂点フォーマット
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureShadow );

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
* 関数名：SetShadow
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetShadow( D3DXVECTOR3 pos , SHADOWPATTARN shadowPattarn )
{
	for( int cntShadow = 0 ; cntShadow < SHADOW_MAX ; cntShadow++ )
	{
		if( g_Shadow[cntShadow].shadowUse == false )
		{
			g_Shadow[cntShadow].posShadow = pos;
			g_Shadow[cntShadow].shadowPattarn = shadowPattarn;
			g_Shadow[cntShadow].shadowUse = true;
			break;
		}
	}
}

/******************************************************************************
* 関数名：GetShadow
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
SHADOW *GetShadow( void )
{
	return g_Shadow;
}
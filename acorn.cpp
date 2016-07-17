/******************************************************************************
* タイトル  :
* ファイル名:acorn.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/27
*******************************************************************************
* 更新履歴:-2015/10/27 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPD3DXBUFFER g_pBuffMatAcorn = NULL;		//マテリアルの情報
LPDIRECT3DTEXTURE9 g_pTextureAcorn = NULL;
LPD3DXMESH g_pMeshAcorn;		//メッシュ情報
DWORD g_numMatAcorn;			//マテリアルの数
D3DXMATRIX g_mtxWorldAcorn;
ACORN g_Acorn[ACORN_MAX];

/******************************************************************************
* 関数名：InitAcorn
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデル初期化処理
******************************************************************************/
void InitAcorn( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXLoadMeshFromX( "data/MODEL/donguri.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatAcorn,
						NULL,
						&g_numMatAcorn,
						&g_pMeshAcorn );

	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		g_Acorn[cntAcorn].posAcorn  = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
		g_Acorn[cntAcorn].rotAcorn  = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Acorn[cntAcorn].sclAcorn  = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Acorn[cntAcorn].moveY     = 0.0f;
		g_Acorn[cntAcorn].moveRot   = 0.0f;
		g_Acorn[cntAcorn].EffectTime= 0.0f;
		g_Acorn[cntAcorn].acornUse  = false;
		g_Acorn[cntAcorn].acornDraw = false;
	}
}

/******************************************************************************
* 関数名：UninitAcorn
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデル終了処理
******************************************************************************/
void UninitAcorn( void )
{
	if( g_pMeshAcorn != NULL )
	{
		g_pMeshAcorn -> Release();
		g_pMeshAcorn = NULL;
	}

	if( g_pBuffMatAcorn !=NULL )
	{
		g_pBuffMatAcorn -> Release();
		g_pBuffMatAcorn = NULL;
	}
}

/******************************************************************************
* 関数名：UpdateAcorn
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：
******************************************************************************/
void UpdateAcorn( void )
{
	MODEL *pModel = GetModel();

	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		g_Acorn[cntAcorn].rotAcorn.x += ACORN_ROT_SPEED;

		//回転の初期化
		if( g_Acorn[cntAcorn].rotAcorn.x >= D3DX_PI * 2 )
		{
			g_Acorn[cntAcorn].rotAcorn.x = 0.0f;
		}
		g_Acorn[cntAcorn].rotAcorn.z = ACOUNT_ROTZ;

		//プレイヤーの周りをくるくる
		if( g_Acorn[cntAcorn].acornDraw == true && g_Acorn[cntAcorn].acornUse == false )
		{
			//座標計算
			g_Acorn[cntAcorn].moveY   += ACORN_MOVEY;
			g_Acorn[cntAcorn].moveRot += ACORN_MOVE_ROT;

			g_Acorn[cntAcorn].sclAcorn   = D3DXVECTOR3( 0.5f , 0.5f , 0.5f );
			g_Acorn[cntAcorn].posAcorn.y = pModel -> posModel.y + g_Acorn[cntAcorn].moveY;
			g_Acorn[cntAcorn].posAcorn.x = sinf(g_Acorn[cntAcorn].moveRot) * 20 + pModel -> posModel.x ;
			g_Acorn[cntAcorn].posAcorn.z = cosf(g_Acorn[cntAcorn].moveRot) * 20 + pModel -> posModel.z ;

			//エフェクトのセット
			g_Acorn[cntAcorn].EffectTime++;
			//if( g_Acorn[cntAcorn].EffectTime % ACORN_EFFECT_TIME == 0 )
			{
				SetEffect( g_Acorn[cntAcorn].posAcorn , EFFECT_ACORN );
			}

			//描画終了
			if( g_Acorn[cntAcorn].posAcorn.y - pModel -> posModel.y > 40 )
			{
				g_Acorn[cntAcorn].acornDraw = false;
			}
		}
	}
}


/******************************************************************************
* 関数名：DrawAcorn
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデルの描画
******************************************************************************/
void DrawAcorn( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		if( g_Acorn[cntAcorn].acornDraw == true )
		{
			D3DXMatrixIdentity( &g_mtxWorldAcorn );

			D3DXMatrixScaling( &mtxScl , g_Acorn[cntAcorn].sclAcorn.x , g_Acorn[cntAcorn].sclAcorn.y , g_Acorn[cntAcorn].sclAcorn.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldAcorn , &g_mtxWorldAcorn , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Acorn[cntAcorn].rotAcorn.x , g_Acorn[cntAcorn].rotAcorn.y , g_Acorn[cntAcorn].rotAcorn.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldAcorn , &g_mtxWorldAcorn , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Acorn[cntAcorn].posAcorn.x , g_Acorn[cntAcorn].posAcorn.y , g_Acorn[cntAcorn].posAcorn.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldAcorn , &g_mtxWorldAcorn , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldAcorn );

			pDevice ->GetMaterial( &matDef );

			pMat = ( D3DXMATERIAL* )g_pBuffMatAcorn -> GetBufferPointer();
			for( int nCntMat = 0 ; nCntMat < (int) g_numMatAcorn ; nCntMat++ )
			{
				pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
				pDevice -> SetTexture( 0 , g_pTextureAcorn );
				g_pMeshAcorn ->DrawSubset( nCntMat );
			}

			//マテリアルを元に戻す
			pDevice -> SetMaterial( &matDef );
		}

	}
}

/******************************************************************************
* 関数名：SetAcorn
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetAcorn( D3DXVECTOR3 pos )
{
	for( int cntAcorn  = 0 ; cntAcorn < ACORN_MAX ; cntAcorn++ )
	{
		if( g_Acorn[cntAcorn].acornUse == false )
		{
			g_Acorn[cntAcorn].posAcorn = pos;
			g_Acorn[cntAcorn].acornUse = true;
			g_Acorn[cntAcorn].acornDraw = true;

			SetShadow( g_Acorn[cntAcorn].posAcorn , SHADOW_ACORN );
			break;
		}
	}
}

/******************************************************************************
* 関数名：GetAcorn
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
ACORN *GetAcorn( void )
{
	return &g_Acorn[0];
}
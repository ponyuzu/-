/******************************************************************************
* タイトル  :
* ファイル名:enemy.cpp
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
LPD3DXBUFFER g_pBuffMatEnemy;//マテリアルの情報
LPDIRECT3DTEXTURE9 g_pTextureEnemy = NULL;
LPD3DXMESH g_pMeshEnemy;		//メッシュ情報
DWORD g_numMatEnemy;			//マテリアルの数
D3DXMATRIX g_mtxWorldEnemy;
ENEMY g_Enemy[ENEMY_MAX];

/******************************************************************************
* 関数名：InitEnemy
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデル初期化処理
******************************************************************************/
void InitEnemy( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	D3DXLoadMeshFromX( "data/MODEL/mouse.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatEnemy,
						NULL,
						&g_numMatEnemy,
						&g_pMeshEnemy );

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		g_Enemy[cntEnemy].posEnemy = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
		g_Enemy[cntEnemy].rotEnemy = D3DXVECTOR3( D3DX_PI / 2 , 0.0f , 0.0f );
		g_Enemy[cntEnemy].sclEnemy = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Enemy[cntEnemy].move     = false;
		g_Enemy[cntEnemy].useEnemy = false;
	}
}

/******************************************************************************
* 関数名：UninitEnemy
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデル終了処理
******************************************************************************/
void UninitEnemy( void )
{
	if( g_pMeshEnemy != NULL )
	{
		g_pMeshEnemy -> Release();
		g_pMeshEnemy = NULL;
	}

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( g_pBuffMatEnemy !=NULL )
		{
			g_pBuffMatEnemy -> Release();
			g_pBuffMatEnemy = NULL;
		}
	}
}

/******************************************************************************
* 関数名：UpdateEnemy
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：
******************************************************************************/
void UpdateEnemy( void )
{
	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		//SetEffect( g_Enemy[cntEnemy].posEnemy , EFFECT_ACORN );

		//移動//////////////////////////////////////////////////////////////////////////
		if( g_Enemy[cntEnemy].move == false )//左に移動
		{
			g_Enemy[cntEnemy].posEnemy.x -= ENEMY_SPEED;
			g_Enemy[cntEnemy].rotEnemy.x = D3DX_PI / 2;
		}
		else
		{
			g_Enemy[cntEnemy].posEnemy.x += ENEMY_SPEED;
			g_Enemy[cntEnemy].rotEnemy.x = -D3DX_PI / 2;
		}

		//回転//////////////////////////////////////////////////////////////////////////


		//当たり判定///////////////////////////////////////////////////////////////////////
		//右に当たる
		if( g_Enemy[cntEnemy].posEnemy.x + 50 > FIELD_WIDHT )
		{
			g_Enemy[cntEnemy].move = false;
		}

		//左に当たる
		if( g_Enemy[cntEnemy].posEnemy.x - 50 < - FIELD_WIDHT )
		{
			g_Enemy[cntEnemy].move = true;
		}
	}

}


/******************************************************************************
* 関数名：DrawEnemy
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデルの描画
******************************************************************************/
void DrawEnemy( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( g_Enemy[cntEnemy].useEnemy == true)
		{
				//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_mtxWorldEnemy );

			D3DXMatrixScaling( &mtxScl , g_Enemy[cntEnemy].sclEnemy.x , g_Enemy[cntEnemy].sclEnemy.y , g_Enemy[cntEnemy].sclEnemy.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldEnemy , &g_mtxWorldEnemy , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Enemy[cntEnemy].rotEnemy.x , g_Enemy[cntEnemy].rotEnemy.y , g_Enemy[cntEnemy].rotEnemy.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldEnemy , &g_mtxWorldEnemy , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Enemy[cntEnemy].posEnemy.x , g_Enemy[cntEnemy].posEnemy.y , g_Enemy[cntEnemy].posEnemy.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldEnemy , &g_mtxWorldEnemy , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldEnemy );

			pDevice ->GetMaterial( &matDef );

			pMat = ( D3DXMATERIAL* )g_pBuffMatEnemy -> GetBufferPointer();

			for( int nCntMat = 0 ; nCntMat < (int) g_numMatEnemy ; nCntMat++ )
			{
				pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
				pDevice -> SetTexture( 0 , g_pTextureEnemy );
				g_pMeshEnemy ->DrawSubset( nCntMat );
			}

			//マテリアルを元に戻す
			pDevice -> SetMaterial( &matDef );
		}
	}
}

/******************************************************************************
* 関数名：SetEnemy
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetEnemy( D3DXVECTOR3 pos )
{
	for( int cntEnemy = 0 ; cntEnemy < ENEMY_MAX ; cntEnemy++ )
	{
		if( g_Enemy[cntEnemy].useEnemy == false )
		{
			g_Enemy[cntEnemy].posEnemy = pos;
			g_Enemy[cntEnemy].useEnemy = true;

			SetShadow( g_Enemy[cntEnemy].posEnemy , SHADOW_ENEMY );
			break;
		}
	}
}

/******************************************************************************
* 関数名：GetEnemy
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
ENEMY *GetEnemy( void )
{
	return &g_Enemy[0];
}
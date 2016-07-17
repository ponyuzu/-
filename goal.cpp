/******************************************************************************
* タイトル  :
* ファイル名:goal.cpp
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
LPD3DXBUFFER g_pBuffMatGoal;//マテリアルの情報
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;
LPD3DXMESH g_pMeshGoal;		//メッシュ情報
DWORD g_numMatGoal;			//マテリアルの数
D3DXMATRIX g_mtxWorldGoal;
GOAL g_Goal[GOAL_MAX];

float g_rotY;

/******************************************************************************
* 関数名：InitGoal
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデル初期化処理
******************************************************************************/
void InitGoal( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	D3DXLoadMeshFromX( "data/MODEL/candy.x",
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&g_pBuffMatGoal,
						NULL,
						&g_numMatGoal,
						&g_pMeshGoal );

	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		g_Goal[cntGoal].posGoal = D3DXVECTOR3( 0.0f , 0.0f ,  0.0f );
		g_Goal[cntGoal].rotGoal = D3DXVECTOR3( 0.0f , 0.0f , 0.6f );
		g_Goal[cntGoal].sclGoal = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		g_Goal[cntGoal].useGoal = false;
	}
	g_rotY =0.0f;
}

/******************************************************************************
* 関数名：UninitGoal
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデル終了処理
******************************************************************************/
void UninitGoal( void )
{
	if( g_pMeshGoal != NULL )
	{
		g_pMeshGoal -> Release();
		g_pMeshGoal = NULL;
	}

	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		if( g_pBuffMatGoal !=NULL )
		{
			g_pBuffMatGoal -> Release();
			g_pBuffMatGoal = NULL;
		}
	}
}

/******************************************************************************
* 関数名：UpdateGoal
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：
******************************************************************************/
void UpdateGoal( void )
{
	//回転させる
	g_Goal[0].rotGoal.x -= GOAL_SPEED;
	//初期化
	if( g_Goal[0].rotGoal.x > D3DX_PI * 2 )
	{
		g_Goal[0].rotGoal.x = 0;
	}

	//ふわふわさせる
	g_rotY += GOAL_SPEED;
	//初期化
	g_Goal[0].posGoal.y += sinf( g_rotY ) / 2;
	if( g_rotY > D3DX_PI * 2 )
	{
		g_rotY = 0.0f;
	}
}


/******************************************************************************
* 関数名：DrawGoal
* 
* 引数  ：なし
* 戻り値：なし
* 説明  ：モデルの描画
******************************************************************************/
void DrawGoal( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans;
	D3DXMATERIAL *pMat;
	D3DMATERIAL9 matDef;

	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		if( g_Goal[cntGoal].useGoal == true)
		{
				//ワールドマトリックスの初期化
			D3DXMatrixIdentity( &g_mtxWorldGoal );

			D3DXMatrixScaling( &mtxScl , g_Goal[cntGoal].sclGoal.x , g_Goal[cntGoal].sclGoal.y , g_Goal[cntGoal].sclGoal.z );
	
			//スケールを反映
			D3DXMatrixMultiply( &g_mtxWorldGoal , &g_mtxWorldGoal , &mtxScl );

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Goal[cntGoal].rotGoal.x , g_Goal[cntGoal].rotGoal.y , g_Goal[cntGoal].rotGoal.z );

			//回転の反映
			D3DXMatrixMultiply( &g_mtxWorldGoal , &g_mtxWorldGoal , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Goal[cntGoal].posGoal.x , g_Goal[cntGoal].posGoal.y , g_Goal[cntGoal].posGoal.z );

			//移動の反映
			D3DXMatrixMultiply( &g_mtxWorldGoal , &g_mtxWorldGoal , &mtxTrans );

			//ワールドマトリックスの設定
			pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldGoal );

			pDevice ->GetMaterial( &matDef );

			pMat = ( D3DXMATERIAL* )g_pBuffMatGoal -> GetBufferPointer();

			for( int nCntMat = 0 ; nCntMat < (int) g_numMatGoal ; nCntMat++ )
			{
				pDevice -> SetMaterial( &pMat[nCntMat].MatD3D );
				pDevice -> SetTexture( 0 , g_pTextureGoal );
				g_pMeshGoal ->DrawSubset( nCntMat );
			}

			//マテリアルを元に戻す
			pDevice -> SetMaterial( &matDef );
		}
	}
}

/******************************************************************************
* 関数名：SetGoal
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetGoal( D3DXVECTOR3 pos )
{
	for( int cntGoal = 0 ; cntGoal < GOAL_MAX ; cntGoal++ )
	{
		if( g_Goal[cntGoal].useGoal == false )
		{
			g_Goal[cntGoal].posGoal = pos;
			g_Goal[cntGoal].useGoal = true;

			SetShadow( g_Goal[cntGoal].posGoal , SHADOW_GOAL );
			break;
		}
	}
}

/******************************************************************************
* 関数名：GetGoal
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
GOAL *GetGoal( void )
{
	return &g_Goal[0];
}
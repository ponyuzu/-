/******************************************************************************
* タイトル  :
* ファイル名:light.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/23
*******************************************************************************
* 更新履歴:-2015/10/23 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
D3DLIGHT9 g_aLight[3];

/******************************************************************************
* 関数名：InitLight
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void InitLight( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	//初期化
	ZeroMemory( &g_aLight[0] , sizeof( D3DLIGHT9 ) );

	//光の設定１
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;						//平行光源
	g_aLight[0].Diffuse = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.5f );	//光の色
	vecDir = D3DXVECTOR3( 0.1f , -0.5f , 0.8f );					//光の向き
	D3DXVec3Normalize( ( D3DXVECTOR3* )&g_aLight[0].Direction , &vecDir );

	pDevice ->SetLight( 0 , &g_aLight[0] );

	pDevice->LightEnable( 0 , TRUE );			//光１の有効、無効

	//初期化
	ZeroMemory( &g_aLight[1] , sizeof( D3DLIGHT9 ) );

	//光の設定2（反射光）
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;						//平行光源
	g_aLight[1].Diffuse = D3DXCOLOR( 0.5f , 0.5f , 0.5f , 1.0f );	//光の色
	vecDir = D3DXVECTOR3( -0.1f , 0.5f , 0.1f );					//光の向き
	D3DXVec3Normalize( ( D3DXVECTOR3* )&g_aLight[1].Direction , &vecDir );

	pDevice ->SetLight( 1 , &g_aLight[1] );

	pDevice->LightEnable( 1 , TRUE );			//光2の有効、無効

	//初期化
	ZeroMemory( &g_aLight[2] , sizeof( D3DLIGHT9 ) );

	//光の設定3（環境光）
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;						//平行光源
	g_aLight[2].Diffuse = D3DXCOLOR( 0.1f , 0.1f , 0.1f , 0.5f );	//光の色
	vecDir = D3DXVECTOR3( 0.0f , 0.0f , -0.1f );					//光の向き
	D3DXVec3Normalize( ( D3DXVECTOR3* )&g_aLight[2].Direction , &vecDir );

	pDevice ->SetLight( 2 , &g_aLight[2] );

	pDevice->LightEnable( 2 , TRUE );			//光3の有効、無効

	pDevice ->SetRenderState( D3DRS_LIGHTING , TRUE );	//主電源
}

/******************************************************************************
* 関数名：UninitLight
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitLight( void )
{
	
}

/******************************************************************************
* 関数名：UpdateLight
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateLight( void )
{
	
}
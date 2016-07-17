/******************************************************************************
* タイトル  :
* ファイル名:camera.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/23
*******************************************************************************
* 更新履歴:-2015/10/23 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include <stdio.h>
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
CAMERA g_camera;//カメラ情報

LPD3DXFONT g_FontCamera;
int g_CntTime;
D3DXVECTOR3 dffrncRot;

/******************************************************************************
* 関数名：InitCamera
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void InitCamera( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_camera.rot.y = 0;
	g_camera.length = 200.0f;
	g_camera.goalRot = D3DXVECTOR3( 0 , 0 , 0 );

	//g_camera.posV = D3DXVECTOR3( 0 , 200 , -310 );	//カメラ位置
	//g_camera.posR = D3DXVECTOR3( 0 , 50 , -100 );				//注視点位置
	g_camera.vecU = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );			//カメラ上の位置
	
	g_camera.posVMove = D3DXVECTOR3( 0 , 0 , 0 );
	g_camera.posRMove = D3DXVECTOR3( 0 , 0 , 0 );

	g_camera.distanthModel = 0;

	g_CntTime = 0;

	g_FontCamera = NULL;
	D3DXCreateFont( pDevice , 18 , 0 , 0 , 0 , FALSE , SHIFTJIS_CHARSET , OUT_DEFAULT_PRECIS , DEFAULT_QUALITY , DEFAULT_PITCH , "Terminal" , &g_FontCamera );
}

/******************************************************************************
* 関数名：UninitCamera
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitCamera( void )
{
}

/******************************************************************************
* 関数名：UpdateCamera
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateCamera( void )
{
	MODEL *pModel = GetModel();

	D3DXVECTOR3 posVOld;
	D3DXVECTOR3 posROld;


	posVOld = g_camera.posV;
	posROld = g_camera.posR;

	/*移動*/
	//視点移動
	/*g_camera.posRMove.x = pModel -> posModel.x;
	g_camera.posRMove.z = pModel -> posModel.z;*/

	//カメラ回転(プレイヤーの背後に)
	/*g_CntTime++;
	if( g_CntTime > 300 )
	{
		g_camera.goalRot.y = pModel -> rotModel.x + D3DX_PI;
		g_CntTime = 0;
	}*/
	//目標値計算
	//g_camera.goalRot.y = pModel -> rotModel.x + D3DX_PI;

	//差分計算
	//dffrncRot.y = g_camera.goalRot.y - g_camera.rot.y;

	//目標補正
	/*if( g_camera.goalRot.y > D3DX_PI )
	{
		g_camera.goalRot.y -= D3DX_PI * 2.0f;
	}
	else if( g_camera.goalRot.y < -D3DX_PI )
	{
		g_camera.goalRot.y += D3DX_PI * 2.0f;
	}*/


	//回転の補正
	//現在地
	/*if( g_camera.rot.y > D3DX_PI )
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if( g_camera.rot.y < -D3DX_PI )
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}*/

	//差分
	/*if( dffrncRot.y > D3DX_PI )
	{
		dffrncRot.y -= D3DX_PI * 2.0f;
	}
	else if( dffrncRot.y < -D3DX_PI )
	{
		dffrncRot.y += D3DX_PI * 2.0f;
	}*/

	//カメラとモデルの距離の計算///////////////////////////////////////////////////////////////
	g_camera.distanthModel = g_camera.posR.z - pModel -> posModel.z;

	//注視点座標代入/////////////////////////////////////////////////////////////////////
	//g_camera.posR.x = pModel -> posModel.x;

	//カメラを前に動かす
	if( g_camera.distanthModel <= - DISTANTH_MODEL_FLONT )
	{
		g_camera.posR.z = pModel -> posModel.z - DISTANTH_MODEL_FLONT;
	}
	//カメラを後ろに動かす
	if( g_camera.distanthModel >= DISTANTH_MODEL_BACK )
	{
		g_camera.posR.z = pModel -> posModel.z + DISTANTH_MODEL_BACK;
	}

	

	//g_camera.rot.y += dffrncRot.y * 0.02;

	//注視点から視点を求める
	g_camera.posV.x = g_camera.posR.x + ( sinf( g_camera.rot.y + D3DX_PI ) * 250 );
	g_camera.posV.z = g_camera.posR.z + ( cosf( g_camera.rot.y + D3DX_PI ) * 280 );

	/*if( pModel -> hitModel == true )
	{
		g_camera.posV = posVOld;
		g_camera.posR = posROld;
	}*/

	//カメラのデバッグモード
	if( GetKeyboardTrigger( DIK_F1 ))
	{
		if( g_camera.cameraDebug )
		{
			g_camera.cameraDebug = false;
		}
		else
		{
			g_camera.cameraDebug = true;
		}
	}
}
/******************************************************************************
* 関数名：DrawCamera
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawCamera( void )
{

	if( g_camera.cameraDebug )
	{
		char posRX[64];
		char posRY[64];
		char posRZ[64];

		char posVX[64];
		char posVY[64];
		char posVZ[64];

		char rot[64];
		char goalRot[64];
		char dfRot[64];

		//視点
		RECT rectposVX = { 0 , 15 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posVX[0] , "視点x座標%f\n" , g_camera.posV.x );
		g_FontCamera ->DrawText( NULL , &posVX[0] , -1 , &rectposVX , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposVY = { 0 , 30 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posVY[0] , "視点y座標%f\n" , g_camera.posV.y );
		g_FontCamera ->DrawText( NULL , &posVY[0] , -1 , &rectposVY , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposVZ = { 0 , 45 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posVZ[0] , "視点z座標%f\n" , g_camera.posV.z );
		g_FontCamera ->DrawText( NULL , &posVZ[0] , -1 , &rectposVZ , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));
	
		//注視点
		RECT rectposRX = { 0 , 60 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posRX[0] , "注視点x座標%f\n" , g_camera.posR.x );
		g_FontCamera ->DrawText( NULL , &posRX[0] , -1 , &rectposRX , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposRY = { 0 , 75 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posRY[0] , "注視点y座標%f\n" , g_camera.posR.y );
		g_FontCamera ->DrawText( NULL , &posRY[0] , -1 , &rectposRY , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposRZ = { 0 , 90 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posRZ[0] , "注視点z座標%f\n" , g_camera.posR.z );
		g_FontCamera ->DrawText( NULL , &posRZ[0] , -1 , &rectposRZ , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		//角度
		RECT rectrot = { 0 , 115 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &rot[0] , "回転角度%f\n" , g_camera.rot.y );
		g_FontCamera ->DrawText( NULL , &rot[0] , -1 , &rectrot , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectgoalRot = { 0 , 130 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &goalRot[0] , "目標回転角度%f\n" , g_camera.goalRot.y );
		g_FontCamera ->DrawText( NULL , &goalRot[0] , -1 , &rectgoalRot , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectdfRot = { 0 , 145 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &dfRot[0] , "回転角度差分%f\n" , g_camera.distanthModel );
		g_FontCamera ->DrawText( NULL , &dfRot[0] , -1 , &rectdfRot , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));
	}
	
}

/******************************************************************************
* 関数名：SetCamera
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetCamera( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity( &g_camera.mtxProjection );

	//プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH( &g_camera.mtxProjection ,
								D3DX_PI / 4 ,					//視野角
								SCREEN_WIDTH / SCREEN_HEIGHT ,	//アスペクト比
								CAMERA_NEARZ ,					//NearZ値
								CAMERA_FARZ );					//FarZ値

	//プロジェクションマトリクスの設定
	pDevice -> SetTransform( D3DTS_PROJECTION , &g_camera.mtxProjection );

	//ビューマトリックスの初期化
	D3DXMatrixIdentity( &g_camera.mtxView );

	//ビューマトリックス作成
	D3DXMatrixLookAtLH( &g_camera.mtxView , &g_camera.posV , &g_camera.posR , &g_camera.vecU );

	//ビューマリックス設定
	pDevice -> SetTransform( D3DTS_VIEW , &g_camera.mtxView );
}
/******************************************************************************
* 関数名：GetCamera
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
CAMERA *GetCamera( void )
{
	return &g_camera;
}
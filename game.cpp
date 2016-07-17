/******************************************************************************
* タイトル  :
* ファイル名:game.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "game.h"

/******************************************************************************
* 関数名：InitGame
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void InitGame( void )
{
	CAMERA *pCamera = GetCamera();

	//カメラ位置(ゲーム初期位置)
	pCamera -> posV = D3DXVECTOR3( 100 , 220 , -310 );//位置
	pCamera -> posR = D3DXVECTOR3( 0 , 50 , -100 );//注視点

	InitWall();
	InitTree();
	InitField();
	InitObstacl();
	InitBox();
	InitEnemy();
	InitGoal();
	InitShadow();
	//InitEffect();
	InitModel();
	InitAcorn();
	InitStage();
	InitPause();

	SetStage();
}

/******************************************************************************
* 関数名：IninitGame
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitGame( void )
{
	UninitWall();
	UninitTree();
	UninitField();
	UninitObstacl();
	UninitModel();
	UninitAcorn();
	UninitEnemy();
	UninitGoal();
	UninitBox();
	UninitShadow();
	UninitPause();
	//UninitEffect();
}

/******************************************************************************
* 関数名：UpdateGame
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateGame( void )
{
	bool pPause = GetPause();

	//Ｐを押したらポーズ開始or解除
	if( GetKeyboardTrigger( DIK_P ) )
	{
		if( pPause == false )
		{
			InitPause();//初期化呼び出し
			SetPause( true );
		}
		else
		{
			SetPause( false );
		}
	}

	if( !pPause )
	{
		UpdateWall();
		UpdateTree();
		UpdateField();
		UpdateObstacl();
		UpdateAcorn();
		UpdateEnemy();
		UpdateGoal();
		UpdateBox();
		//UpdateEffect();
		UpdateShadow();
		UpdateLifeCnt();
		UpdateModel();
		UpdateAcornCnt();
	}
	else
	{
		UpdatePause();
	}
}

/******************************************************************************
* 関数名：DrawGame
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void DrawGame( void )
{
	//DrawWall();
	DrawTree();
	DrawField();
	DrawObstacl();
	DrawModel();
	DrawAcorn();
	DrawEnemy();
	DrawGoal();
	DrawBox();
	DrawShadow();
	DrawAcornCnt();
	DrawLifeCnt();
	DrawPause();
	//DrawEffect();
}
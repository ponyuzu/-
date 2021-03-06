/******************************************************************************
* タイトル  :
* ファイル名:goal.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/27
*******************************************************************************
* 更新履歴:-2015/10/27 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
/*多重インクルード防止*/
#ifndef _GOAL_H_
#define _GOAL_H_

/******************************************************************************
* マクロ定義
******************************************************************************/
//#define FIELD_USE_TEX ( true )//テクスチャの有無
#define GOAL_SPEED (0.05f)//回転スピード
#define GOAL_RADIUS (50)//半径

#define GOAL_MAX (3)//エネミーの数

/******************************************************************************
* 構造体定義
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posGoal;
	D3DXVECTOR3 rotGoal;
	D3DXVECTOR3 sclGoal;

	bool useGoal;//goalを使ってるかどうか

}GOAL;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
void InitGoal( void );
void UninitGoal( void );
void UpdateGoal( void );
void DrawGoal( void );
void SetGoal( D3DXVECTOR3 pos );
GOAL *GetGoal( void );


/*多重インクルード防止*/
#endif
/******************************************************************************
* タイトル  :
* ファイル名:acorncnt.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/
/*多重インクルード防止*/
#ifndef _ACORNCNT_H_
#define _ACORNCNT_H_

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* マクロ定義
******************************************************************************/
#define ACORNCNT_MAX (4)
#define ACORN_TEX_MAX (3)

#define ACORNCNT_WIDTH  (30.0)		//ポリゴン横幅
#define ACORNCNT_HEIGHT (50.0)		//ポリゴン縦幅
#define ACORN_TEX_WIDTH (40.0)		//テクスチャ同士の横幅

#define ACORN_TEX_HEIGHT (40.0)		//どんぐりポリゴン縦幅
#define ACORN_TEX_WIDTH  (40.0)		//ポリゴン横幅

#define ACORN_KAKERU_HEIGHT (20.0)		//かけるポリゴン縦幅

#define ACORNCNT_PATTERN_WIDTH (1.0f / 10 )		//１フレームの横幅

#define ACORNCNT_DOWN_SPEED (30)		//表示する時のスピード
#define ACORNCNT_UP_SPEED (-1)		//しまう時のスピード
#define ACORNCNT_INDICATE_TIME (200)	//表示しておく時間
#define ACORNCNT_POSY (40.0f)		//表示Ｙ座標

/******************************************************************************
* 列挙型
******************************************************************************/
typedef enum
{
	ACORN_NONE = 0,
	ACORN_DOWN,
	ACORN_IND,
	ACORN_UP

}ACORNIND;

/******************************************************************************
* 構造体定義
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posAcornCnt;		//ポリゴンの中心点
	float widthAcornCnt;			//ポリゴン中心点からの横幅
	float heightAcornCnt;			//ポリゴン中心点からの縦幅
	float posTexXAcornCnt;			//テクスチャのポジション

	ACORNIND acornInd;
	int cntIndTime;

}ACORNCNT;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
HRESULT InitAcornCnt( void );
void UninitAcornCnt( void );
void UpdateAcornCnt( void );
void DrawAcornCnt( void );
ACORNCNT *GetAcornCnt( void );
void AddAcornCnt( int value );

#endif
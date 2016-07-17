/******************************************************************************
* タイトル  :
* ファイル名:select.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2016/02/01
*******************************************************************************
* 更新履歴:-2016/02/01 渡邉柚香
*           -v0.01 
******************************************************************************/
/*多重インクルード防止*/
#ifndef _RESULTLOGO_H_
#define _RESULTLOGO_H_

/******************************************************************************
* マクロ定義
******************************************************************************/
#define RESULTLOGO_MAX (4)//オブジェクトの数

#define RESULTLOGO1_WIDTH (600)//くりあの幅
#define RESULTLOGO1_HEIDHT (200)

#define RESULTLOGO2_WIDTH (700)//ねくすとの幅
#define RESULTLOGO2_HEIDHT (100)

#define RESULTLOGO3_WIDTH (700)//げーむおーばーの幅
#define RESULTLOGO3_HEIDHT (100)

#define RESULTLOGO4_WIDTH (700)//またの幅
#define RESULTLOGO4_HEIDHT (100)

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "main.h"

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffResultLogo;//頂点バッファ

	D3DXVECTOR3 posResultLogo;		//ポリゴンの中心点
	float widthResultLogo;			//ポリゴン中心点からの横幅
	float heightResultLogo;			//ポリゴン中心点からの縦幅

	bool LogoUse;		//描画するかどうか

}RESULTLOGO;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
HRESULT InitResultLogo( void );
void UninitResultLogo( void );
void UpdateResultLogo( void );
void DrawResultLogo( void );

#endif
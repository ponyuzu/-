/******************************************************************************
* タイトル  :
* ファイル名:effect.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2016/02/01
*******************************************************************************
* 更新履歴:-2016/02/01 渡邉柚香
*           -v0.01 
******************************************************************************/
/*多重インクルード防止*/
#ifndef _EFFECT_H_
#define _EFFECT_H_

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* マクロ定義
******************************************************************************/
#define EFFECT_MAX (100)		//エフェクトの数
#define EFFECT_NUM_VTX (4)	//頂点数
#define EFFECT_ALPHA (-0.01)	//α値の変更

#define EFFECT_ACORN_WIDTH (20)		//どんぐりエフェクトの横幅
#define EFFECT_ACORN_HEIGHT (20)	//どんぐりエフェクトの縦幅

#define EFFECT_IN_WIDHT (70)	//復活エフェクトの横幅
#define EFFECT_IN_HEIGHT (70)	//復活エフェクトの縦幅

#define EFFECT_1UP_WIDHT (70)	//１ＵＰエフェクトの横幅
#define EFFECT_1UP_HEIGHT (70)	//1UPエフェクトの縦幅

/******************************************************************************
* 列挙型
******************************************************************************/
typedef enum
{
	EFFECT_NONE = 0,
	EFFECT_ACORN,
	EFFECT_IN,
	EFFECT_1UP

}EFFECTPATTARN;

/******************************************************************************
* 構造体定義
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffEffect;//頂点バッファ

	D3DXVECTOR3 posEffect;		//位置情報
	D3DXVECTOR3 rotEffect;		//回転情報
	D3DXVECTOR3 sclEffect;		//倍率情報

	float effectWidht;		//エフェクト横幅
	float effectHeight;		//エフェクト縦幅

	float effectR;			//R
	float effectG;			//G
	float effectB;			//B
	float effectAlpha;		//α値

	bool effectUse;//エフェクトをつかっているかどうか

	EFFECTPATTARN effectPttrn;//エフェクトの種類

}EFFECT;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
HRESULT InitEffect( void );
void UninitEffect( void );
void UpdateEffect( void );
void DrawEffect( void );
void SetEffect( D3DXVECTOR3 pos , EFFECTPATTARN pattarn );

#endif
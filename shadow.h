/******************************************************************************
* タイトル  :
* ファイル名:shadow.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/11/12
*******************************************************************************
* 更新履歴:-2015/11/12 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
/*多重インクルード防止*/
#ifndef _SHADOW_H_
#define _SHADOW_H_

/******************************************************************************
* マクロ定義
******************************************************************************/
#define SHADOW_USE_TEX ( true )//テクスチャの有無
#define SHADOW_MAX (50)//画面上の影の数

#define SHADOW_X (1)//xのブロック数
#define SHADOW_Z (1)//zのブロック数

#define SHADOW_NUM_INDEX ( ( SHADOW_X + 1.0 ) * 2.0 * SHADOW_Z + ( SHADOW_Z - 1.0 ) * 2.0 )//インデックス数
#define SHADOW_NUM_VTX ( ( SHADOW_X + 1.0 ) * ( SHADOW_Z + 1.0 ) )//頂点数
#define SHADOW_NUM_PORIGON ( SHADOW_X * SHADOW_Z * 2.0 + 4.0 * ( SHADOW_Z - 1.0 ) )//ポリゴン数

/******************************************************************************
* 列挙型
******************************************************************************/
typedef enum
{
	SHADOW_PLAYER = 0,
	SHADOW_ENEMY ,
	SHADOW_BOX ,
	SHADOW_ACORN ,
	SHADOW_GOAL ,
	SHADOW_NONE

}SHADOWPATTARN;

/******************************************************************************
* 構造体
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffShadow;//頂点バッファ

	D3DXVECTOR3 posShadow;		//位置情報
	D3DXVECTOR3 rotShadow;		//回転情報
	D3DXVECTOR3 sclShadow;		//倍率情報

	float shadowHeight;
	float shadowWidth;

	bool shadowUse;		//使ってるかどうか
	SHADOWPATTARN shadowPattarn;	//誰の影か

}SHADOW;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
HRESULT InitShadow( void );
void UninitShadow( void );
void UpdateShadow( void );
void DrawShadow( void );
void SetShadow( D3DXVECTOR3 pos , SHADOWPATTARN shadowPattarn );
SHADOW *GetShadow( void );


/*多重インクルード防止*/
#endif
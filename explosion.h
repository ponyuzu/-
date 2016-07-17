/******************************************************************************
* タイトル  :
* ファイル名:explosion.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/11/17
*******************************************************************************
* 更新履歴:-2015/11/17 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
/*多重インクルード防止*/
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

/******************************************************************************
* マクロ定義
******************************************************************************/
#define EXPLOSION_USE_TEX ( true )//テクスチャの有無
#define EXPLOSION_MAX (50)//画面内の弾数

#define EXPLOSION_SPEED (3)//弾のスピード

#define EXPLOSION_X (1)//xのブロック数
#define EXPLOSION_Z (1)//zのブロック数

#define EXPLOSION_HEIGHT (40.0f)//弾の縦幅
#define EXPLOSION_WIDTH (40.0f)//弾の横幅
#define EXPLOSION_TEX_WIDTH ( 1.0f / 8.0 )//テクスチャ横幅

#define EXPLOSION_TEX_TIME (10)

#define EXPLOSION_NUM_INDEX ( ( EXPLOSION_X + 1.0 ) * 2.0 * EXPLOSION_Z + ( EXPLOSION_Z - 1.0 ) * 2.0 )//インデックス数
#define EXPLOSION_NUM_VTX ( ( EXPLOSION_X + 1.0 ) * ( EXPLOSION_Z + 1.0 ) )//頂点数
#define EXPLOSION_NUM_PORIGON ( EXPLOSION_X * EXPLOSION_Z * 2.0 + 4.0 * ( EXPLOSION_Z - 1.0 ) )//ポリゴン数

/******************************************************************************
* 構造体定義
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posExplosion;		//位置情報
	D3DXVECTOR3 rotExplosion;		//回転情報
	D3DXVECTOR3 sclExplosion;		//倍率情報

	bool explosionUse;			//使ってるかどうか

	int nCounterAnim;//アニメーションカウンター
	int nPatternAnim;//アニメーションパターンNO.


}EXPLOSION;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
HRESULT InitExplosion( void );
void UninitExplosion( void );
void UpdateExplosion( void );
void DrawExplosion( void );
void SetExplosion( D3DXVECTOR3 pos );
EXPLOSION *GetExplosion( void );

/*多重インクルード防止*/
#endif
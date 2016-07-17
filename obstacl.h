/******************************************************************************
* タイトル  :
* ファイル名:obstacl.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2016/01/21
*******************************************************************************
* 更新履歴:-2016/01/21 渡邉柚香
*           -v0.01 
******************************************************************************/

/*多重インクルード防止*/
#ifndef _OBSTACL_H_
#define _OBSTACL_H_

/******************************************************************************
* マクロ定義
******************************************************************************/
#define OBSTACL_USE_TEX ( true )//テクスチャの有無
#define OBSTACL_SURFACE_MAX (6)//一個の箱の面の数
#define OBSTACL_MAX (10)//箱の数

#define OBSTACL_WIDTH (40)
#define OBSTACL_HEIGHT (40)

//#define OBSTACL_X (1)//xのブロック数
//#define OBSTACL_Z (1)//zのブロック数
//
//#define OBSTACL_NUM_INDEX ( ( OBSTACL_X + 1.0 ) * 2.0 * OBSTACL_Z + ( OBSTACL_Z - 1.0 ) * 2.0 )//インデックス数
#define OBSTACL_NUM_VTX (4)//頂点数
//#define OBSTACL_NUM_PORIGON ( OBSTACL_X * OBSTACL_Z * 2.0 + 4.0 * ( OBSTACL_Z - 1.0 ) )//ポリゴン数

/******************************************************************************
* 列挙型
******************************************************************************/
typedef enum
{
	OBSTACL_NOMAL = 0,
	OBSTACL_SPRING ,
	OBSTACL_NONE

}OBSTACLPATTARN;

/******************************************************************************
* 構造体
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffObstacl;//頂点バッファ

	D3DXVECTOR3 posObstacl;		//位置情報
	D3DXVECTOR3 rotObstacl;		//回転情報
	D3DXVECTOR3 sclObstacl;		//倍率情報

	D3DXVECTOR3 setPosObstacl;		//箱の中心点

	bool obstaclUse;		//使ってるかどうか
	bool obstaclSpringHit;		//playerが上でジャンプしたかどうじか
	OBSTACLPATTARN obstaclPattarn;	//種類

}OBSTACL;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
HRESULT InitObstacl( void );
void UninitObstacl( void );
void UpdateObstacl( void );
void DrawObstacl( void );
void SetObstacl( D3DXVECTOR3 pos , OBSTACLPATTARN obstaclPattarn );
OBSTACL *GetObstacl( void );

/*多重インクルード防止*/
#endif
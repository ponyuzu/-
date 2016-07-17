/******************************************************************************
* タイトル  :
* ファイル名:main.h
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/23
*******************************************************************************
* 更新履歴:-2015/10/23 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
/*多重インクルード防止*/
#ifndef _MAIN_H_
#define _MAIN_H_

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include <windows.h>
#include "d3dx9.h"		//描画に必要
#define DIRECTINPUT_VERSION (0x0800)//警告対処
#include "camera.h"
#include "light.h"
#include "meshfield.h"
#include "model.h"
#include "dinput.h"//入力処理に必要
#include "input.h"
#include "meshwall.h"
#include "shadow.h"
#include "explosion.h"
#include "box.h"
#include "tree.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "common.h"
#include "obstacl.h"
#include "acorn.h"
#include "enemy.h"
#include "result.h"
#include "selsect.h"
#include "stage.h"
#include "acorncnt.h"
#include "lifecnt.h"
#include "fade.h"
#include "sky.h"
#include "effect.h"
#include "selectarrow.h"
#include "goal.h"
#include "resultlogo.h"
#include "pause.h"

/*****************************************************************************
*ライブラリのリンク
******************************************************************************/
#pragma comment(lib , "d3d9.lib")		//描画処理に必要
#pragma comment(lib , "d3dx9.lib")	//上記の拡張ライブラリ
#pragma comment(lib , "dxguid.lib")	//directXコンポーネント使用に必要
#pragma comment(lib , "winmm.lib")	//システム時刻獲得に必要
#pragma comment(lib , "dinput8.lib")	//入力処理に必要

#pragma warning ( disable : 4996 )

/******************************************************************************
* マクロ定義
******************************************************************************/
#define SCREEN_WIDTH (1280.0f)		//画面の横幅
#define SCREEN_HEIGHT (720.0f)	//画面の縦幅
#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )//座標・カラー・テクスチャ
#define FVF_VERTEX_3D ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	//座標・法線・カラー・テクスチャ
#define TYOUTEN (4)				//頂点の数

/******************************************************************************
* 構造体定義
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 pos;
	float rwh;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_2D;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;

}VERTEX_3D;

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
LPDIRECT3DDEVICE9 GetDevice( void );
void SetMode( MODE mode );


/*多重インクルード防止*/
#endif
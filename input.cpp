/******************************************************************************
* タイトル  :
* ファイル名:input.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/06/22
*******************************************************************************
* 更新履歴:-2015/06/22 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
*インクルード宣言
******************************************************************************/
#include "input.h"

/******************************************************************************
* グローバル
******************************************************************************/
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;

BYTE g_aKeyState[256];//キー情報
BYTE g_aKeyStateTrigger[256];//トリガー情報
BYTE g_aKeyStateRelease[256];//リリース情報
BYTE g_aKeyStateRepeat[256];//キーリピート情報

int g_aKeySatetRepeatCount[256];//キーリピートカウント

/******************************************************************************
* 関数名：IntKeyboard
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitInput( HINSTANCE hInstance , HWND hwnd )
{
	if( g_pInput == NULL )
	{
		if( FAILED( DirectInput8Create( hInstance , DIRECTINPUT_VERSION , IID_IDirectInput8 , ( void** )&g_pInput , NULL ) ) )
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

/******************************************************************************
* 関数名：UninitInput
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitInput( void )
{
	if( g_pInput != NULL )
	{
		g_pInput -> Release();
		g_pInput = NULL;
	}
}

/******************************************************************************
* 関数名：UpdateInput
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdeteInput( void )
{
}

/******************************************************************************
* 関数名：InitKeyboard
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT InitKeyboard( HINSTANCE hInstance , HWND hWnd)
{
	if( FAILED( InitInput( hInstance , hWnd ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_pInput -> CreateDevice ( GUID_SysKeyboard , &g_pDevKeyboard , NULL ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_pDevKeyboard -> SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		return E_FAIL;
	}

	if( FAILED( g_pDevKeyboard -> SetCooperativeLevel( hWnd , ( DISCL_FOREGROUND | DISCL_NONEXCLUSIVE ) ) ) )
	{
		return E_FAIL;
	}
	g_pDevKeyboard -> Acquire();//アクセス権
	return S_OK;
}

/******************************************************************************
* 関数名：InitKeyboard
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UninitKeyboard( void )
{
	if( g_pDevKeyboard != NULL )
	{
		g_pDevKeyboard -> Unacquire();
		g_pDevKeyboard -> Release();
		g_pDevKeyboard = NULL;
	}
	UninitInput();
}

/******************************************************************************
* 関数名：UpdateKeyboard
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void UpdateKeyboard( void )
{
	BYTE aKeyState[256];

	if( SUCCEEDED( g_pDevKeyboard -> GetDeviceState( sizeof(aKeyState) ,&aKeyState[0] ) ) )
	{
		for( int nCntKey = 0 ; nCntKey < 256 ; nCntKey++ )
		{
			g_aKeyStateRelease[nCntKey] = ( aKeyState[nCntKey] ^ g_aKeyState[nCntKey] ) & g_aKeyState[nCntKey];
			g_aKeyStateTrigger[nCntKey] = ( aKeyState[nCntKey] ^ g_aKeyState[nCntKey] ) & ~g_aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		g_pDevKeyboard -> Acquire();
	}
}

/******************************************************************************
* 関数名：GetKeyboardPress
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
bool GetKeyboardPress( int nKey )
{
	return ( g_aKeyState[nKey]&0x80 ) ? true : false;
}

/******************************************************************************
* 関数名：GetKeyboardTrigger
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
bool GetKeyboardTrigger( int nKey )
{
	return ( g_aKeyStateTrigger[nKey]&0x80 ) ? true : false;
}

/******************************************************************************
* 関数名：GetKeyboardRelease
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
bool GetKeyboardRelease( int nKey )
{
	return ( g_aKeyStateRelease[nKey]&0x80 ) ? true : false;
}
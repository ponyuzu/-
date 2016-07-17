/******************************************************************************
* �^�C�g��  :
* �t�@�C����:input.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "input.h"

/******************************************************************************
* �O���[�o��
******************************************************************************/
LPDIRECTINPUT8 g_pInput = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;

BYTE g_aKeyState[256];//�L�[���
BYTE g_aKeyStateTrigger[256];//�g���K�[���
BYTE g_aKeyStateRelease[256];//�����[�X���
BYTE g_aKeyStateRepeat[256];//�L�[���s�[�g���

int g_aKeySatetRepeatCount[256];//�L�[���s�[�g�J�E���g

/******************************************************************************
* �֐����FIntKeyboard
* 
* ����  �F
* �߂�l�F
* ����  �F
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
* �֐����FUninitInput
* 
* ����  �F
* �߂�l�F
* ����  �F
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
* �֐����FUpdateInput
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdeteInput( void )
{
}

/******************************************************************************
* �֐����FInitKeyboard
* 
* ����  �F
* �߂�l�F
* ����  �F
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
	g_pDevKeyboard -> Acquire();//�A�N�Z�X��
	return S_OK;
}

/******************************************************************************
* �֐����FInitKeyboard
* 
* ����  �F
* �߂�l�F
* ����  �F
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
* �֐����FUpdateKeyboard
* 
* ����  �F
* �߂�l�F
* ����  �F
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
* �֐����FGetKeyboardPress
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
bool GetKeyboardPress( int nKey )
{
	return ( g_aKeyState[nKey]&0x80 ) ? true : false;
}

/******************************************************************************
* �֐����FGetKeyboardTrigger
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
bool GetKeyboardTrigger( int nKey )
{
	return ( g_aKeyStateTrigger[nKey]&0x80 ) ? true : false;
}

/******************************************************************************
* �֐����FGetKeyboardRelease
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
bool GetKeyboardRelease( int nKey )
{
	return ( g_aKeyStateRelease[nKey]&0x80 ) ? true : false;
}
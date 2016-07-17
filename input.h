/******************************************************************************
* �^�C�g��  :
* �t�@�C����:input.h
* �� �� ��  :AT12C245 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _INPUT_H_
#define _INPUT_H_

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitInput( HINSTANCE hInstance , HWND hwnd );
void UninitInput( void );
void UpdeteInput( void );
HRESULT InitKeyboard( HINSTANCE hInstance , HWND hwnd );
void UninitKeyboard( void );
void UpdateKeyboard( void );


bool GetKeyboardPress( int nkey );
bool GetKeyboardTrigger( int nkey );
bool GetKeyboardRelease( int nkey );

/*���d�C���N���[�h�h�~*/
#endif
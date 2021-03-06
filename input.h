/******************************************************************************
* ^Cg  :
* t@C¼:input.h
* ì Ò ¼  :AT12C245 nç³M
* ì ¬ ú  :2015/06/22
*******************************************************************************
* XVð:-2015/06/22 nç³M
*           -v0.01 
******************************************************************************/
/*½dCN[hh~*/
#ifndef _INPUT_H_
#define _INPUT_H_

/******************************************************************************
*CN[hé¾
******************************************************************************/
#include "main.h"

/******************************************************************************
* vg^Cvé¾
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

/*½dCN[hh~*/
#endif
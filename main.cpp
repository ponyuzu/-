/******************************************************************************
* タイトル  :
* ファイル名:main.cpp
* 作 者 名  :AT12C245 42 渡邉柚香
* 作 成 日  :2015/10/23
*******************************************************************************
* 更新履歴:-2015/010/23 渡邉柚香
*           -v0.01 
******************************************************************************/

/******************************************************************************
* インクルード宣言
******************************************************************************/
#include "main.h"

/******************************************************************************
* グローバル変数
******************************************************************************/
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;//フォントへのポインタ
int g_nCountFPS;//FPSカウンタ
MODE g_mode = MODE_TITLE;//現在のモード

/******************************************************************************
* プロトタイプ宣言
******************************************************************************/
LRESULT CALLBACK WndProc( HWND , UINT , WPARAM , LPARAM );
HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow );
void Uninit( void );
void Update( void );
void Draw( void );
void FPSDraw( void );

/******************************************************************************
* 関数名：main
* 
* 引数  ：正常終了：int型0
* 戻り値：
* 説明  ：
******************************************************************************/
int WINAPI WinMain ( HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	AdjustWindowRect( &rect , WS_OVERLAPPEDWINDOW , false );

	//FPS
	DWORD dwFrameCount;
	DWORD dwCurrentTime;
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;

	timeBeginPeriod( 1 );

	dwFrameCount =
	dwCurrentTime = 0;
	dwExecLastTime = 
	dwFPSLastTime =timeGetTime();

	WNDCLASSEX wcex =
	{
		sizeof( WNDCLASSEX ),     //メモリサイズを指定
		CS_CLASSDC,               //ウィンドウのスタイル指定
		WndProc,                  //ウィンドウプロシージャのアドレス指定
		0,
		0,
		hInstance,                        //WinMainのインスタンスハンドル指定
		NULL,                             //アイコンを指定
		LoadCursor( NULL , IDC_ARROW ),   //マウスカーソル指定
		( HBRUSH )( COLOR_WINDOW + 1 ),   //クライアント領域の背景色指定
		NULL,                     //メニュー指定
		"A",                      //ウィンドウクラスの名前
		NULL,                     //小さいアイコンが設定された場合の情報
	};

	HWND hWnd;                 //ウィンドウハンドル
	MSG msg;                   //メッセージ
	RegisterClassEx( & wcex ); //ウィンドウクラスの登録

	hWnd = CreateWindowEx( 0,
						"A",   //ウィンドウクラスの名前
						"テスト",         //ウィンドウの名前
						WS_OVERLAPPEDWINDOW,   //ウィンドウのスタイル
						CW_USEDEFAULT,    //左上X座標
						CW_USEDEFAULT,    //左上Y座標
						rect.right - rect.left,//ウインドウ幅
						rect.bottom - rect.top,//ウインドウ高さ
						NULL,   //親ウィンドウのハンドル
						NULL,   //メニューハンドル　OR　子ウィンドウID
						hInstance,
						NULL );

	if( FAILED( Init( hInstance , hWnd , TRUE ) ) )
	{
		return -1;
	}

	//ウィンドウの表示
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	//メッセージループ
	while( 1 )
	{
		if( PeekMessage( &msg , NULL , 0 , 0  , PM_REMOVE ) !=0 )
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( & msg );
				DispatchMessage( & msg );
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if( ( dwCurrentTime - dwFPSLastTime ) >= 500 )
			{
				g_nCountFPS = ( dwFrameCount * 1000 ) / ( dwCurrentTime - dwFPSLastTime );
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount= 0 ;
			}

			if( ( dwCurrentTime - dwExecLastTime ) >= ( 1000 / 60 ) )
			{
				dwExecLastTime = dwCurrentTime;

				Update();
				Draw();

				dwFrameCount++;
			}
		}
	}
	Uninit();

	timeEndPeriod( 1 );

	//ウィンドウクラスの登録解除
	UnregisterClass( "A",
					wcex.hInstance );

	return ( int ) msg.wParam;
}

/******************************************************************************
* 関数名：
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
LRESULT CALLBACK WndProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	int nID;

	switch( uMsg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	
	
	case WM_KEYDOWN:
		switch( wParam )
		{
		//ESCでウィンドウを消す
		case VK_ESCAPE:
			nID = MessageBox( hWnd, "終了しますか？" , "確認" , MB_YESNO );
			if( nID == IDYES )
			{
				DestroyWindow( hWnd );
			}
			break;
		}
		break;

	}
	
	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}

/******************************************************************************
* 関数名：Init
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow )
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	if( g_pD3D == NULL )
	{
		return E_FAIL;
	}

	if( FAILED( g_pD3D ->GetAdapterDisplayMode( D3DADAPTER_DEFAULT , &d3ddm ) ) )
	{
		return E_FAIL;
	}

	ZeroMemory( &d3dpp , sizeof( d3dpp ));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = d3ddm.Format;//バックバッファの形式
	d3dpp.BackBufferCount = 1;//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.Windowed = bWindow;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT ,
										D3DDEVTYPE_HAL , hWnd ,
										D3DCREATE_HARDWARE_VERTEXPROCESSING ,
										&d3dpp , &g_pD3DDevice ) ) )
	{
		if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT ,
											D3DDEVTYPE_HAL , hWnd ,
											D3DCREATE_SOFTWARE_VERTEXPROCESSING ,
											&d3dpp , &g_pD3DDevice ) ) )
		{
			if( FAILED( g_pD3D -> CreateDevice( D3DADAPTER_DEFAULT , 
												D3DDEVTYPE_REF , hWnd ,
												D3DCREATE_SOFTWARE_VERTEXPROCESSING ,
												&d3dpp , &g_pD3DDevice ) ) )
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_CCW );
	g_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
	g_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	g_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );

	//サンプラーステートの設定
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MINFILTER , D3DTEXF_LINEAR );//テクスチャ縮小時の補間設定
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MAGFILTER , D3DTEXF_LINEAR );//テクスチャ拡大時の補間設定

	//FPS
	D3DXCreateFont( g_pD3DDevice , 18 , 0 , 0 , 0 , FALSE , SHIFTJIS_CHARSET ,
					OUT_DEFAULT_PRECIS , DEFAULT_QUALITY ,
					DEFAULT_PITCH , "Terminal" , &g_pFont );
	InitKeyboard(hInstance , hWnd);

	InitFade();
	SetMode( g_mode );//モード
	InitCamera();
	InitLight();

	InitAcornCnt();
	InitLifeCnt();

	return S_OK;
}

/******************************************************************************
* 関数名：Uninit
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void Uninit( void )
{
	if( g_pD3DDevice != NULL )
	{
		g_pD3DDevice -> Release();
		g_pD3DDevice = NULL;
	}
	if( g_pD3D != NULL )
	{
		g_pD3D -> Release();
		g_pD3D = NULL;
	}
	if( g_pFont != NULL )
	{
		g_pFont -> Release();
		g_pFont = NULL;
	}
	UninitKeyboard();
	UninitFade();
	UninitCamera();
	UninitLight();

	UninitAcornCnt();
	UninitLifeCnt();
}

/******************************************************************************
* 関数名：Update
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void Update( void )
{
	UpdateKeyboard();
	UpdateFade();

	UpdateLight();

	switch( g_mode )
	{
	case MODE_TITLE:
		UpdateTitle();
		break;

	case MODE_SELECT:
		UpdateSelect();
		break;

	case MODE_TUTO:
		break;

	case MODE_GAME:
		UpdateCamera();
		UpdateGame();
		break;

	case MODE_RESULT:
		UpdateResult();
		break;
	}
}

/******************************************************************************
* 関数名：Draw
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void Draw( void )
{
	g_pD3DDevice -> Clear( 0 , NULL ,
							( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ) ,
							D3DCOLOR_RGBA( 150 , 150 , 225 , 255 ) , 1.0f , 0 );//背景の色

	if( SUCCEEDED( g_pD3DDevice -> BeginScene() ) )
	{
		FPSDraw();

		//DrawCamera();
		SetCamera();

		switch( g_mode )
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_SELECT:
			DrawSelect();
			break;

		case MODE_TUTO:
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		}
		DrawFade();
		g_pD3DDevice -> EndScene();//描画終了
	}
	g_pD3DDevice -> Present( NULL , NULL , NULL , NULL );
}

/******************************************************************************
* 関数名：LPDIRECT3DDEVICE9 GetDevice
* 
* 引数  ：
* 戻り値：
* 説明  ：他のcppでg_pD3DDeviceを使うための関数
******************************************************************************/
LPDIRECT3DDEVICE9 GetDevice( void )
{
	return g_pD3DDevice;
}

/******************************************************************************
* 関数名：FPSDraw
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void FPSDraw( void )
{
	RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0] , "FPS:%d\n" , g_nCountFPS);
	g_pFont -> DrawText( NULL , &aStr[0] , -1 , &rect , DT_LEFT , D3DCOLOR_RGBA( 0 , 0 , 0 , 255 ) );
}

/******************************************************************************
* 関数名：SetMode
* 
* 引数  ：
* 戻り値：
* 説明  ：
******************************************************************************/
void SetMode( MODE mode )
{
	//MODEのUninit呼び出し
	switch( g_mode )
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_SELECT:
		UninitSelect();
		break;

	case MODE_TUTO:
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;
	}

	//MODEのInit呼び出し
	switch( mode )
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_SELECT:
		InitSelect();
		break;

	case MODE_TUTO:
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;
	}

	g_mode = mode;
}
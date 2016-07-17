/******************************************************************************
* �^�C�g��  :
* �t�@�C����:main.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/23
*******************************************************************************
* �X�V����:-2015/010/23 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
LPD3DXFONT g_pFont = NULL;//�t�H���g�ւ̃|�C���^
int g_nCountFPS;//FPS�J�E���^
MODE g_mode = MODE_TITLE;//���݂̃��[�h

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
LRESULT CALLBACK WndProc( HWND , UINT , WPARAM , LPARAM );
HRESULT Init( HINSTANCE hInstance , HWND hWnd , BOOL bWindow );
void Uninit( void );
void Update( void );
void Draw( void );
void FPSDraw( void );

/******************************************************************************
* �֐����Fmain
* 
* ����  �F����I���Fint�^0
* �߂�l�F
* ����  �F
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
		sizeof( WNDCLASSEX ),     //�������T�C�Y���w��
		CS_CLASSDC,               //�E�B���h�E�̃X�^�C���w��
		WndProc,                  //�E�B���h�E�v���V�[�W���̃A�h���X�w��
		0,
		0,
		hInstance,                        //WinMain�̃C���X�^���X�n���h���w��
		NULL,                             //�A�C�R�����w��
		LoadCursor( NULL , IDC_ARROW ),   //�}�E�X�J�[�\���w��
		( HBRUSH )( COLOR_WINDOW + 1 ),   //�N���C�A���g�̈�̔w�i�F�w��
		NULL,                     //���j���[�w��
		"A",                      //�E�B���h�E�N���X�̖��O
		NULL,                     //�������A�C�R�����ݒ肳�ꂽ�ꍇ�̏��
	};

	HWND hWnd;                 //�E�B���h�E�n���h��
	MSG msg;                   //���b�Z�[�W
	RegisterClassEx( & wcex ); //�E�B���h�E�N���X�̓o�^

	hWnd = CreateWindowEx( 0,
						"A",   //�E�B���h�E�N���X�̖��O
						"�e�X�g",         //�E�B���h�E�̖��O
						WS_OVERLAPPEDWINDOW,   //�E�B���h�E�̃X�^�C��
						CW_USEDEFAULT,    //����X���W
						CW_USEDEFAULT,    //����Y���W
						rect.right - rect.left,//�E�C���h�E��
						rect.bottom - rect.top,//�E�C���h�E����
						NULL,   //�e�E�B���h�E�̃n���h��
						NULL,   //���j���[�n���h���@OR�@�q�E�B���h�EID
						hInstance,
						NULL );

	if( FAILED( Init( hInstance , hWnd , TRUE ) ) )
	{
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow( hWnd , nCmdShow );
	UpdateWindow( hWnd );

	//���b�Z�[�W���[�v
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

	//�E�B���h�E�N���X�̓o�^����
	UnregisterClass( "A",
					wcex.hInstance );

	return ( int ) msg.wParam;
}

/******************************************************************************
* �֐����F
* 
* ����  �F
* �߂�l�F
* ����  �F
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
		//ESC�ŃE�B���h�E������
		case VK_ESCAPE:
			nID = MessageBox( hWnd, "�I�����܂����H" , "�m�F" , MB_YESNO );
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
* �֐����FInit
* 
* ����  �F
* �߂�l�F
* ����  �F
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
	d3dpp.BackBufferFormat = d3ddm.Format;//�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;//�o�b�N�o�b�t�@�̐�
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

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice -> SetRenderState( D3DRS_CULLMODE , D3DCULL_CCW );
	g_pD3DDevice -> SetRenderState( D3DRS_ALPHABLENDENABLE , TRUE );
	g_pD3DDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
	g_pD3DDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MINFILTER , D3DTEXF_LINEAR );//�e�N�X�`���k�����̕�Ԑݒ�
	g_pD3DDevice -> SetSamplerState( 0 , D3DSAMP_MAGFILTER , D3DTEXF_LINEAR );//�e�N�X�`���g�厞�̕�Ԑݒ�

	//FPS
	D3DXCreateFont( g_pD3DDevice , 18 , 0 , 0 , 0 , FALSE , SHIFTJIS_CHARSET ,
					OUT_DEFAULT_PRECIS , DEFAULT_QUALITY ,
					DEFAULT_PITCH , "Terminal" , &g_pFont );
	InitKeyboard(hInstance , hWnd);

	InitFade();
	SetMode( g_mode );//���[�h
	InitCamera();
	InitLight();

	InitAcornCnt();
	InitLifeCnt();

	return S_OK;
}

/******************************************************************************
* �֐����FUninit
* 
* ����  �F
* �߂�l�F
* ����  �F
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
* �֐����FUpdate
* 
* ����  �F
* �߂�l�F
* ����  �F
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
* �֐����FDraw
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void Draw( void )
{
	g_pD3DDevice -> Clear( 0 , NULL ,
							( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ) ,
							D3DCOLOR_RGBA( 150 , 150 , 225 , 255 ) , 1.0f , 0 );//�w�i�̐F

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
		g_pD3DDevice -> EndScene();//�`��I��
	}
	g_pD3DDevice -> Present( NULL , NULL , NULL , NULL );
}

/******************************************************************************
* �֐����FLPDIRECT3DDEVICE9 GetDevice
* 
* ����  �F
* �߂�l�F
* ����  �F����cpp��g_pD3DDevice���g�����߂̊֐�
******************************************************************************/
LPDIRECT3DDEVICE9 GetDevice( void )
{
	return g_pD3DDevice;
}

/******************************************************************************
* �֐����FFPSDraw
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void FPSDraw( void )
{
	RECT rect = { 0 , 0 , SCREEN_WIDTH , SCREEN_HEIGHT };
	char aStr[256];

	wsprintf(&aStr[0] , "FPS:%d\n" , g_nCountFPS);
	g_pFont -> DrawText( NULL , &aStr[0] , -1 , &rect , DT_LEFT , D3DCOLOR_RGBA( 0 , 0 , 0 , 255 ) );
}

/******************************************************************************
* �֐����FSetMode
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetMode( MODE mode )
{
	//MODE��Uninit�Ăяo��
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

	//MODE��Init�Ăяo��
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
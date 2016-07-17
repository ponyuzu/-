/******************************************************************************
* �^�C�g��  :
* �t�@�C����:camera.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/23
*******************************************************************************
* �X�V����:-2015/10/23 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include <stdio.h>
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
CAMERA g_camera;//�J�������

LPD3DXFONT g_FontCamera;
int g_CntTime;
D3DXVECTOR3 dffrncRot;

/******************************************************************************
* �֐����FInitCamera
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void InitCamera( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_camera.rot.y = 0;
	g_camera.length = 200.0f;
	g_camera.goalRot = D3DXVECTOR3( 0 , 0 , 0 );

	//g_camera.posV = D3DXVECTOR3( 0 , 200 , -310 );	//�J�����ʒu
	//g_camera.posR = D3DXVECTOR3( 0 , 50 , -100 );				//�����_�ʒu
	g_camera.vecU = D3DXVECTOR3( 0.0f , 1.0f , 0.0f );			//�J������̈ʒu
	
	g_camera.posVMove = D3DXVECTOR3( 0 , 0 , 0 );
	g_camera.posRMove = D3DXVECTOR3( 0 , 0 , 0 );

	g_camera.distanthModel = 0;

	g_CntTime = 0;

	g_FontCamera = NULL;
	D3DXCreateFont( pDevice , 18 , 0 , 0 , 0 , FALSE , SHIFTJIS_CHARSET , OUT_DEFAULT_PRECIS , DEFAULT_QUALITY , DEFAULT_PITCH , "Terminal" , &g_FontCamera );
}

/******************************************************************************
* �֐����FUninitCamera
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitCamera( void )
{
}

/******************************************************************************
* �֐����FUpdateCamera
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateCamera( void )
{
	MODEL *pModel = GetModel();

	D3DXVECTOR3 posVOld;
	D3DXVECTOR3 posROld;


	posVOld = g_camera.posV;
	posROld = g_camera.posR;

	/*�ړ�*/
	//���_�ړ�
	/*g_camera.posRMove.x = pModel -> posModel.x;
	g_camera.posRMove.z = pModel -> posModel.z;*/

	//�J������](�v���C���[�̔w���)
	/*g_CntTime++;
	if( g_CntTime > 300 )
	{
		g_camera.goalRot.y = pModel -> rotModel.x + D3DX_PI;
		g_CntTime = 0;
	}*/
	//�ڕW�l�v�Z
	//g_camera.goalRot.y = pModel -> rotModel.x + D3DX_PI;

	//�����v�Z
	//dffrncRot.y = g_camera.goalRot.y - g_camera.rot.y;

	//�ڕW�␳
	/*if( g_camera.goalRot.y > D3DX_PI )
	{
		g_camera.goalRot.y -= D3DX_PI * 2.0f;
	}
	else if( g_camera.goalRot.y < -D3DX_PI )
	{
		g_camera.goalRot.y += D3DX_PI * 2.0f;
	}*/


	//��]�̕␳
	//���ݒn
	/*if( g_camera.rot.y > D3DX_PI )
	{
		g_camera.rot.y -= D3DX_PI * 2.0f;
	}
	else if( g_camera.rot.y < -D3DX_PI )
	{
		g_camera.rot.y += D3DX_PI * 2.0f;
	}*/

	//����
	/*if( dffrncRot.y > D3DX_PI )
	{
		dffrncRot.y -= D3DX_PI * 2.0f;
	}
	else if( dffrncRot.y < -D3DX_PI )
	{
		dffrncRot.y += D3DX_PI * 2.0f;
	}*/

	//�J�����ƃ��f���̋����̌v�Z///////////////////////////////////////////////////////////////
	g_camera.distanthModel = g_camera.posR.z - pModel -> posModel.z;

	//�����_���W���/////////////////////////////////////////////////////////////////////
	//g_camera.posR.x = pModel -> posModel.x;

	//�J������O�ɓ�����
	if( g_camera.distanthModel <= - DISTANTH_MODEL_FLONT )
	{
		g_camera.posR.z = pModel -> posModel.z - DISTANTH_MODEL_FLONT;
	}
	//�J���������ɓ�����
	if( g_camera.distanthModel >= DISTANTH_MODEL_BACK )
	{
		g_camera.posR.z = pModel -> posModel.z + DISTANTH_MODEL_BACK;
	}

	

	//g_camera.rot.y += dffrncRot.y * 0.02;

	//�����_���王�_�����߂�
	g_camera.posV.x = g_camera.posR.x + ( sinf( g_camera.rot.y + D3DX_PI ) * 250 );
	g_camera.posV.z = g_camera.posR.z + ( cosf( g_camera.rot.y + D3DX_PI ) * 280 );

	/*if( pModel -> hitModel == true )
	{
		g_camera.posV = posVOld;
		g_camera.posR = posROld;
	}*/

	//�J�����̃f�o�b�O���[�h
	if( GetKeyboardTrigger( DIK_F1 ))
	{
		if( g_camera.cameraDebug )
		{
			g_camera.cameraDebug = false;
		}
		else
		{
			g_camera.cameraDebug = true;
		}
	}
}
/******************************************************************************
* �֐����FDrawCamera
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawCamera( void )
{

	if( g_camera.cameraDebug )
	{
		char posRX[64];
		char posRY[64];
		char posRZ[64];

		char posVX[64];
		char posVY[64];
		char posVZ[64];

		char rot[64];
		char goalRot[64];
		char dfRot[64];

		//���_
		RECT rectposVX = { 0 , 15 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posVX[0] , "���_x���W%f\n" , g_camera.posV.x );
		g_FontCamera ->DrawText( NULL , &posVX[0] , -1 , &rectposVX , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposVY = { 0 , 30 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posVY[0] , "���_y���W%f\n" , g_camera.posV.y );
		g_FontCamera ->DrawText( NULL , &posVY[0] , -1 , &rectposVY , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposVZ = { 0 , 45 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posVZ[0] , "���_z���W%f\n" , g_camera.posV.z );
		g_FontCamera ->DrawText( NULL , &posVZ[0] , -1 , &rectposVZ , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));
	
		//�����_
		RECT rectposRX = { 0 , 60 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posRX[0] , "�����_x���W%f\n" , g_camera.posR.x );
		g_FontCamera ->DrawText( NULL , &posRX[0] , -1 , &rectposRX , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposRY = { 0 , 75 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posRY[0] , "�����_y���W%f\n" , g_camera.posR.y );
		g_FontCamera ->DrawText( NULL , &posRY[0] , -1 , &rectposRY , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectposRZ = { 0 , 90 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &posRZ[0] , "�����_z���W%f\n" , g_camera.posR.z );
		g_FontCamera ->DrawText( NULL , &posRZ[0] , -1 , &rectposRZ , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		//�p�x
		RECT rectrot = { 0 , 115 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &rot[0] , "��]�p�x%f\n" , g_camera.rot.y );
		g_FontCamera ->DrawText( NULL , &rot[0] , -1 , &rectrot , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectgoalRot = { 0 , 130 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &goalRot[0] , "�ڕW��]�p�x%f\n" , g_camera.goalRot.y );
		g_FontCamera ->DrawText( NULL , &goalRot[0] , -1 , &rectgoalRot , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));

		RECT rectdfRot = { 0 , 145 , SCREEN_WIDTH , SCREEN_HEIGHT };
		sprintf( &dfRot[0] , "��]�p�x����%f\n" , g_camera.distanthModel );
		g_FontCamera ->DrawText( NULL , &dfRot[0] , -1 , &rectdfRot , DT_LEFT , D3DCOLOR_RGBA( 255 , 255 , 255 , 255 ));
	}
	
}

/******************************************************************************
* �֐����FSetCamera
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetCamera( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &g_camera.mtxProjection );

	//�v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH( &g_camera.mtxProjection ,
								D3DX_PI / 4 ,					//����p
								SCREEN_WIDTH / SCREEN_HEIGHT ,	//�A�X�y�N�g��
								CAMERA_NEARZ ,					//NearZ�l
								CAMERA_FARZ );					//FarZ�l

	//�v���W�F�N�V�����}�g���N�X�̐ݒ�
	pDevice -> SetTransform( D3DTS_PROJECTION , &g_camera.mtxProjection );

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &g_camera.mtxView );

	//�r���[�}�g���b�N�X�쐬
	D3DXMatrixLookAtLH( &g_camera.mtxView , &g_camera.posV , &g_camera.posR , &g_camera.vecU );

	//�r���[�}���b�N�X�ݒ�
	pDevice -> SetTransform( D3DTS_VIEW , &g_camera.mtxView );
}
/******************************************************************************
* �֐����FGetCamera
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
CAMERA *GetCamera( void )
{
	return &g_camera;
}
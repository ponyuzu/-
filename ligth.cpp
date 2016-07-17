/******************************************************************************
* �^�C�g��  :
* �t�@�C����:light.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/23
*******************************************************************************
* �X�V����:-2015/10/23 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
D3DLIGHT9 g_aLight[3];

/******************************************************************************
* �֐����FInitLight
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void InitLight( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXVECTOR3 vecDir;

	//������
	ZeroMemory( &g_aLight[0] , sizeof( D3DLIGHT9 ) );

	//���̐ݒ�P
	g_aLight[0].Type = D3DLIGHT_DIRECTIONAL;						//���s����
	g_aLight[0].Diffuse = D3DXCOLOR( 1.0f , 1.0f , 1.0f , 1.5f );	//���̐F
	vecDir = D3DXVECTOR3( 0.1f , -0.5f , 0.8f );					//���̌���
	D3DXVec3Normalize( ( D3DXVECTOR3* )&g_aLight[0].Direction , &vecDir );

	pDevice ->SetLight( 0 , &g_aLight[0] );

	pDevice->LightEnable( 0 , TRUE );			//���P�̗L���A����

	//������
	ZeroMemory( &g_aLight[1] , sizeof( D3DLIGHT9 ) );

	//���̐ݒ�2�i���ˌ��j
	g_aLight[1].Type = D3DLIGHT_DIRECTIONAL;						//���s����
	g_aLight[1].Diffuse = D3DXCOLOR( 0.5f , 0.5f , 0.5f , 1.0f );	//���̐F
	vecDir = D3DXVECTOR3( -0.1f , 0.5f , 0.1f );					//���̌���
	D3DXVec3Normalize( ( D3DXVECTOR3* )&g_aLight[1].Direction , &vecDir );

	pDevice ->SetLight( 1 , &g_aLight[1] );

	pDevice->LightEnable( 1 , TRUE );			//��2�̗L���A����

	//������
	ZeroMemory( &g_aLight[2] , sizeof( D3DLIGHT9 ) );

	//���̐ݒ�3�i�����j
	g_aLight[2].Type = D3DLIGHT_DIRECTIONAL;						//���s����
	g_aLight[2].Diffuse = D3DXCOLOR( 0.1f , 0.1f , 0.1f , 0.5f );	//���̐F
	vecDir = D3DXVECTOR3( 0.0f , 0.0f , -0.1f );					//���̌���
	D3DXVec3Normalize( ( D3DXVECTOR3* )&g_aLight[2].Direction , &vecDir );

	pDevice ->SetLight( 2 , &g_aLight[2] );

	pDevice->LightEnable( 2 , TRUE );			//��3�̗L���A����

	pDevice ->SetRenderState( D3DRS_LIGHTING , TRUE );	//��d��
}

/******************************************************************************
* �֐����FUninitLight
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitLight( void )
{
	
}

/******************************************************************************
* �֐����FUpdateLight
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateLight( void )
{
	
}
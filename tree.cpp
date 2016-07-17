/******************************************************************************
* �^�C�g��  :
* �t�@�C����:billboard.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/11/17
*******************************************************************************
* �X�V����:-2015/11/17 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
D3DXMATRIX g_mtxWorldTree;//billboard�̃��[���h�}�g���b�N�X
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTree = NULL;//���_�o�b�t�@
LPDIRECT3DTEXTURE9 g_pTextureTree = NULL;
TREE g_Tree[TREE_MAX];

/******************************************************************************
* �֐����FInitTree
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitTree( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * TREE_NUM_VTX * TREE_MAX ,
												D3DUSAGE_WRITEONLY ,
												FVF_VERTEX_3D ,
												D3DPOOL_MANAGED ,
												&g_pVtxBuffTree ,
												NULL ) ) )
	{
		return E_FAIL;
	}

	g_pTextureTree = NULL;

	//�e�N�X�`���ǂݍ���
	if( FIELD_USE_TEX )
	{
		D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/tree000.png" , &g_pTextureTree );
	}



	VERTEX_3D *pVtx;
	g_pVtxBuffTree -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

	for( int cntTree = 0 , cntVtx = 0 ; cntTree < TREE_MAX ; cntTree++ , cntVtx += 4 )
	{
		//���W�ݒ�
		pVtx[cntVtx].pos     = D3DXVECTOR3( - TREE_WIDTH / 2 ,   TREE_HEIGHT / 2 , 0.0f );
		pVtx[cntVtx + 1].pos = D3DXVECTOR3(   TREE_WIDTH / 2 ,   TREE_HEIGHT / 2 , 0.0f );
		pVtx[cntVtx + 2].pos = D3DXVECTOR3( - TREE_WIDTH / 2 , - TREE_HEIGHT / 2 , 0.0f );
		pVtx[cntVtx + 3].pos = D3DXVECTOR3(   TREE_WIDTH / 2 , - TREE_HEIGHT / 2 , 0.0f );


		//���_�J���[�ݒ�
		pVtx[cntVtx].col     = D3DCOLOR_RGBA( 255 , 255 , 255, 100 );
		pVtx[cntVtx + 1].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );
		pVtx[cntVtx + 2].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );
		pVtx[cntVtx + 3].col = D3DCOLOR_RGBA( 255 , 255 , 255 , 100 );

		//�e�N�X�`��
		pVtx[cntVtx].tex     = D3DXVECTOR2( 0 , 0 );
		pVtx[cntVtx + 1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[cntVtx + 2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[cntVtx + 3].tex = D3DXVECTOR2( 1 , 1 );
	
		//�@��
		pVtx[cntVtx].nor     = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 1].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 2].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
		pVtx[cntVtx + 3].nor = D3DXVECTOR3( 0.0f , 0.0f , -1.0f );
	}


	g_pVtxBuffTree -> Unlock();


	for( int cntTree = 0  ; cntTree < TREE_MAX ; cntTree++ )
	{
		if( cntTree < TREE_MAX / 2 )
		{
			g_Tree[cntTree].posTree = D3DXVECTOR3( -200.0f , TREE_HEIGHT / 2 , 250.0f + TRE_DISTAICE * cntTree );
			g_Tree[cntTree].rotTree = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Tree[cntTree].sclTree = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		}
		else
		{
			g_Tree[cntTree].posTree = D3DXVECTOR3( 200.0f , TREE_HEIGHT / 2 , 250.0f + TRE_DISTAICE * ( cntTree - TREE_MAX / 2 ) );
			g_Tree[cntTree].rotTree = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
			g_Tree[cntTree].sclTree = D3DXVECTOR3( 1.0f , 1.0f , 1.0f );
		}
	}

	return S_OK;
}

/******************************************************************************
* �֐����FUninitTree
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitTree( void )
{
	if( g_pTextureTree != NULL )
	{
		g_pTextureTree -> Release();
		g_pTextureTree = NULL;
	}

	if( g_pVtxBuffTree !=NULL )
	{
		g_pVtxBuffTree -> Release();
		g_pVtxBuffTree = NULL;
	}

}

/******************************************************************************
* �֐����FUpdateTree
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateTree( void )
{
	
}


/******************************************************************************
* �֐����FDrawTree
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawTree( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	for( int cntTree = 0  ; cntTree < TREE_MAX ; cntTree++ )
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &g_mtxWorldTree );

		//�r���[�}�g���b�N�X�擾
		pDevice -> GetTransform( D3DTS_VIEW , &mtxView );

		//�t�s������߂�
		D3DXMatrixInverse( &g_mtxWorldTree , NULL , &mtxView );

		g_mtxWorldTree._41 = 0.0f;
		g_mtxWorldTree._42 = 0.0f;
		g_mtxWorldTree._43 = 0.0f;

		D3DXMatrixScaling( &mtxScl , 1.0f , 1.0f , 1.0f );
	
		//�X�P�[���𔽉f
		D3DXMatrixMultiply( &g_mtxWorldTree , &g_mtxWorldTree , &mtxScl );

		D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Tree[cntTree].rotTree.x , g_Tree[cntTree].rotTree.y , g_Tree[cntTree].rotTree.z );

		//��]�̔��f
		D3DXMatrixMultiply( &g_mtxWorldTree , &g_mtxWorldTree , &mtxRot );

		D3DXMatrixTranslation( &mtxTrans , g_Tree[cntTree].posTree.x , g_Tree[cntTree].posTree.y , g_Tree[cntTree].posTree.z );

		//�ړ��̔��f
		D3DXMatrixMultiply( &g_mtxWorldTree , &g_mtxWorldTree , &mtxTrans );

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice ->SetTransform( D3DTS_WORLD , &g_mtxWorldTree );

		//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
		pDevice -> SetStreamSource( 0 , g_pVtxBuffTree , 0 , sizeof( VERTEX_3D ));

		//���_�t�H�[�}�b�g
		pDevice -> SetFVF( FVF_VERTEX_3D );

		pDevice -> SetTexture( 0 , g_pTextureTree );

		//�A���t�@�e�X�g
		pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
		pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
		pDevice -> SetRenderState( D3DRS_ALPHAREF,0);

		//�|���S���̕`��
		pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , cntTree * 4 , 2 );

		//�A���t�@�e�X�g�߂�
		pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , FALSE );
		pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_ALWAYS );
		pDevice -> SetRenderState( D3DRS_ALPHAREF,0);
	}
}
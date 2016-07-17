/******************************************************************************
* �^�C�g��  :
* �t�@�C����:effect.cpp
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/02/01
*******************************************************************************
* �X�V����:-2016/02/01 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "result.h"

/******************************************************************************
* �O���[�o���ϐ�
******************************************************************************/
LPDIRECT3DTEXTURE9 g_pTextureEffect = NULL;
D3DXMATRIX g_mtxWorldEffect;

EFFECT g_Effect[EFFECT_MAX];

/******************************************************************************
* �֐����FInitEffect
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
HRESULT InitEffect( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//���_�l��
	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
			if( FAILED ( pDevice -> CreateVertexBuffer( sizeof( VERTEX_3D ) * ( EFFECT_NUM_VTX ),
													D3DUSAGE_WRITEONLY ,
													FVF_VERTEX_3D ,
													D3DPOOL_MANAGED ,
													&g_Effect[cntEffect].pVtxBuffEffect ,
													NULL ) ) )
		{
			return E_FAIL;
		}
	}

	g_pTextureEffect = NULL;

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile( pDevice , "data/TEXTURE/shadow000.jpg" , &g_pTextureEffect );

	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		VERTEX_3D *pVtx;
		g_Effect[cntEffect].pVtxBuffEffect -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

		g_Effect[cntEffect].posEffect    = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Effect[cntEffect].rotEffect    = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Effect[cntEffect].sclEffect    = D3DXVECTOR3( 0.0f , 0.0f , 0.0f );
		g_Effect[cntEffect].effectHeight = EFFECT_ACORN_HEIGHT;
		g_Effect[cntEffect].effectWidht  = EFFECT_ACORN_WIDTH;
		g_Effect[cntEffect].effectR      = 1.0f;
		g_Effect[cntEffect].effectG      = 1.0f;
		g_Effect[cntEffect].effectB      = 1.0f;
		g_Effect[cntEffect].effectAlpha  = 1.0f;
		g_Effect[cntEffect].effectUse    = false;

		//���W�ݒ�
		pVtx[0].pos = D3DXVECTOR3( - g_Effect[cntEffect].effectWidht / 2 ,   g_Effect[cntEffect].effectHeight / 2 , 0.0f );
		pVtx[1].pos = D3DXVECTOR3(   g_Effect[cntEffect].effectWidht / 2 ,   g_Effect[cntEffect].effectHeight / 2 , 0.0f );
		pVtx[2].pos = D3DXVECTOR3( - g_Effect[cntEffect].effectWidht / 2 , - g_Effect[cntEffect].effectHeight / 2 , 0.0f );
		pVtx[3].pos = D3DXVECTOR3(   g_Effect[cntEffect].effectWidht / 2 , - g_Effect[cntEffect].effectHeight / 2 , 0.0f );


		//���_�J���[�ݒ�
		for( int addCol = 0 ; addCol < EFFECT_NUM_VTX ; addCol++ )
		{
			pVtx[addCol + 0].col = D3DXCOLOR( g_Effect[cntEffect].effectR , g_Effect[cntEffect].effectG , g_Effect[cntEffect].effectB , g_Effect[cntEffect].effectAlpha );
		}

		//�e�N�X�`��
		pVtx[0].tex = D3DXVECTOR2( 0 , 0 );
		pVtx[1].tex = D3DXVECTOR2( 1 , 0 );
		pVtx[2].tex = D3DXVECTOR2( 0 , 1 );
		pVtx[3].tex = D3DXVECTOR2( 1 , 1 );
	
		//�@��
		for( int addNor = 0 ; addNor < EFFECT_NUM_VTX ; addNor++ )
		{
			pVtx[addNor + 0].nor = D3DXVECTOR3( 0.0f , 0.0f , 1.0f );
		}

		g_Effect[cntEffect].pVtxBuffEffect -> Unlock();
	}

	return S_OK;
}

/******************************************************************************
* �֐����FIninitEffect
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UninitEffect( void )
{
	if( g_pTextureEffect != NULL )
	{
		g_pTextureEffect -> Release();
		g_pTextureEffect = NULL;
	}

	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
			if( g_Effect[cntEffect].pVtxBuffEffect !=NULL )
		{
			g_Effect[cntEffect].pVtxBuffEffect -> Release();
			g_Effect[cntEffect].pVtxBuffEffect = NULL;
		}
	}
}

/******************************************************************************
* �֐����FUpdateEffect
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void UpdateEffect( void )
{
	//���ʃG�t�F�N�g����(���l�ύX)
	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		if( g_Effect[cntEffect].effectUse == true )
		{
			VERTEX_3D *pVtx;
			g_Effect[cntEffect].pVtxBuffEffect -> Lock( 0 , 0 , ( void** ) &pVtx , 0 );

			//���l���炷�v�Z
			g_Effect[cntEffect].effectAlpha += EFFECT_ALPHA;

			//���_�J���[�X�V
			for( int addCol = 0 ; addCol < EFFECT_NUM_VTX ; addCol++ )
			{
				pVtx[addCol + 0].col = D3DXCOLOR( g_Effect[cntEffect].effectR ,
												  g_Effect[cntEffect].effectG ,
												  g_Effect[cntEffect].effectB ,
												  g_Effect[cntEffect].effectAlpha );
			}

			//�`��I��
			if( g_Effect[cntEffect].effectAlpha <= 0.0f )
			{
				g_Effect[cntEffect].effectUse = false;
			}

			g_Effect[cntEffect].pVtxBuffEffect -> Unlock();
		}
	}

}

/******************************************************************************
* �֐����FDrawEffect
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void DrawEffect( void )
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl , mtxRot , mtxTrans , mtxView;

	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		if( g_Effect[cntEffect].effectUse == true )
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity( &g_mtxWorldEffect );

			D3DXMatrixScaling( &mtxScl , g_Effect[cntEffect].sclEffect.x , g_Effect[cntEffect].sclEffect.y , g_Effect[cntEffect].sclEffect.z );
	
			//�X�P�[���𔽉f
			D3DXMatrixMultiply( &g_mtxWorldEffect , &g_mtxWorldEffect , &mtxScl );

			//�r���[�}�g���b�N�X�擾
			pDevice -> GetTransform( D3DTS_VIEW , &mtxView );

			//�t�s������߂�
			D3DXMatrixInverse( &g_mtxWorldEffect , NULL , &mtxView );

			g_mtxWorldEffect._41 = 0.0f;
			g_mtxWorldEffect._42 = 0.0f;
			g_mtxWorldEffect._43 = 0.0f;

			D3DXMatrixRotationYawPitchRoll( &mtxRot , g_Effect[cntEffect].rotEffect.x , g_Effect[cntEffect].rotEffect.y , g_Effect[cntEffect].rotEffect.z );

			//��]�̔��f
			D3DXMatrixMultiply( &g_mtxWorldEffect , &g_mtxWorldEffect , &mtxRot );

			D3DXMatrixTranslation( &mtxTrans , g_Effect[cntEffect].posEffect.x , g_Effect[cntEffect].posEffect.y , g_Effect[cntEffect].posEffect.z );

			//�ړ��̔��f
			D3DXMatrixMultiply( &g_mtxWorldEffect , &g_mtxWorldEffect , &mtxTrans );

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice ->SetTransform(D3DTS_WORLD , &g_mtxWorldEffect );

			//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
			pDevice -> SetStreamSource( 0 , g_Effect[cntEffect].pVtxBuffEffect , 0 , sizeof( VERTEX_3D ));

			//���_�t�H�[�}�b�g
			pDevice -> SetFVF( FVF_VERTEX_3D );

			pDevice -> SetTexture( 0 , g_pTextureEffect );


			//�A���t�@�e�X�g
			pDevice -> SetRenderState( D3DRS_ALPHATESTENABLE , TRUE );
			pDevice -> SetRenderState( D3DRS_ALPHAFUNC , D3DCMP_GREATER );
			pDevice -> SetRenderState( D3DRS_ALPHAREF,0);

			//�����_�[�X�e�C�g�̐ݒ�ύX
			pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_REVSUBTRACT );
			pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_ONE );

			//�|���S���̕`��
			pDevice -> DrawPrimitive( D3DPT_TRIANGLESTRIP , 0 , 2 );

			//�����_�[�X�e�C�g�̐ݒ�߂�
			pDevice -> SetRenderState( D3DRS_BLENDOP , D3DBLENDOP_ADD );
			pDevice -> SetRenderState( D3DRS_SRCBLEND , D3DBLEND_SRCALPHA );
			pDevice -> SetRenderState( D3DRS_DESTBLEND , D3DBLEND_INVSRCALPHA );
		}
	}
}

/******************************************************************************
* �֐����FSetEffect
* 
* ����  �F
* �߂�l�F
* ����  �F
******************************************************************************/
void SetEffect( D3DXVECTOR3 pos , EFFECTPATTARN pattarn )
{
	for( int cntEffect = 0 ; cntEffect < EFFECT_MAX ; cntEffect++ )
	{
		if( g_Effect[cntEffect].effectUse == false )
		{
			g_Effect[cntEffect].posEffect = pos;
			g_Effect[cntEffect].effectPttrn = pattarn;
			g_Effect[cntEffect].effectAlpha = 1.0f;
			g_Effect[cntEffect].effectUse = true;

			break;
		}
	}
}
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:field.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/10/23
*******************************************************************************
* �X�V����:-2015/10/23 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _FIELD_H_
#define _FIELD_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
#define FIELD_USE_TEX ( true )							//�e�N�X�`���̗L��
#define FIELD_TEX ( "data/TEXTURE/field004.jpg" )		//�e�N�X�`�����O

#define FIELD_MAX (10)//���̐�

#define FIELD_X (2)			//x�̃u���b�N��
#define FIELD_Z (2)			//z�̃u���b�N��
#define FIELD_WIDHT (200)	//1�u���b�N�̉���
#define FIELD_HEIGTH (200)	//1�u���b�N�̏c��

#define FIELD_NUM_INDEX ( ( FIELD_X + 1.0 ) * 2.0 * FIELD_Z + ( FIELD_Z - 1.0 ) * 2.0 )	//�C���f�b�N�X��
#define FIELD_NUM_VTX ( ( FIELD_X + 1.0 ) * ( FIELD_Z + 1.0 ) )							//���_��
#define FIELD_NUM_PORIGON ( FIELD_X * FIELD_Z * 2.0 + 4.0 * ( FIELD_Z - 1.0 ) )			//�|���S����

/******************************************************************************
* �\����
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffField;//���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9 pIdxBuffField;//�C���f�b�N�X�o�b�t�@

	D3DXVECTOR3 posField;		//�ʒu���
	D3DXVECTOR3 rotField;		//��]���
	D3DXVECTOR3 sclField;		//�{�����

	bool useField;		//�����g���Ă邩�ǂ���

}FIELD;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitField( void );
void UninitField( void );
void UpdateField( void );
void DrawField( void );
FIELD *GetField( void );
void SetField( D3DXVECTOR3 pos );


/*���d�C���N���[�h�h�~*/
#endif
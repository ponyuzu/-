/******************************************************************************
* �^�C�g��  :
* �t�@�C����:shadow.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/11/12
*******************************************************************************
* �X�V����:-2015/11/12 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _SHADOW_H_
#define _SHADOW_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
#define SHADOW_USE_TEX ( true )//�e�N�X�`���̗L��
#define SHADOW_MAX (50)//��ʏ�̉e�̐�

#define SHADOW_X (1)//x�̃u���b�N��
#define SHADOW_Z (1)//z�̃u���b�N��

#define SHADOW_NUM_INDEX ( ( SHADOW_X + 1.0 ) * 2.0 * SHADOW_Z + ( SHADOW_Z - 1.0 ) * 2.0 )//�C���f�b�N�X��
#define SHADOW_NUM_VTX ( ( SHADOW_X + 1.0 ) * ( SHADOW_Z + 1.0 ) )//���_��
#define SHADOW_NUM_PORIGON ( SHADOW_X * SHADOW_Z * 2.0 + 4.0 * ( SHADOW_Z - 1.0 ) )//�|���S����

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	SHADOW_PLAYER = 0,
	SHADOW_ENEMY ,
	SHADOW_BOX ,
	SHADOW_ACORN ,
	SHADOW_GOAL ,
	SHADOW_NONE

}SHADOWPATTARN;

/******************************************************************************
* �\����
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffShadow;//���_�o�b�t�@

	D3DXVECTOR3 posShadow;		//�ʒu���
	D3DXVECTOR3 rotShadow;		//��]���
	D3DXVECTOR3 sclShadow;		//�{�����

	float shadowHeight;
	float shadowWidth;

	bool shadowUse;		//�g���Ă邩�ǂ���
	SHADOWPATTARN shadowPattarn;	//�N�̉e��

}SHADOW;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitShadow( void );
void UninitShadow( void );
void UpdateShadow( void );
void DrawShadow( void );
void SetShadow( D3DXVECTOR3 pos , SHADOWPATTARN shadowPattarn );
SHADOW *GetShadow( void );


/*���d�C���N���[�h�h�~*/
#endif
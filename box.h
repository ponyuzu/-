/******************************************************************************
* �^�C�g��  :
* �t�@�C����:box.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/01/21
*******************************************************************************
* �X�V����:-2016/01/21 �n糗M��
*           -v0.01 
******************************************************************************/

/*���d�C���N���[�h�h�~*/
#ifndef _BOX_H_
#define _BOX_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
#define BOX_USE_TEX ( true )//�e�N�X�`���̗L��
#define BOX_TEX_MAX (2) //�e�N�X�`���̖���
#define BOX_SURFACE_MAX (6)//��̔��̖ʂ̐�
#define BOX_MAX (20)//���̐�

#define BOX_WIDTH (40)
#define BOX_HEIGHT (40)

//#define BOX_X (1)//x�̃u���b�N��
//#define BOX_Z (1)//z�̃u���b�N��
//
//#define BOX_NUM_INDEX ( ( BOX_X + 1.0 ) * 2.0 * BOX_Z + ( BOX_Z - 1.0 ) * 2.0 )//�C���f�b�N�X��
#define BOX_NUM_VTX (4)//���_��
//#define BOX_NUM_PORIGON ( BOX_X * BOX_Z * 2.0 + 4.0 * ( BOX_Z - 1.0 ) )//�|���S����

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	BOX_NOMAL = 0,
	BOX_SPRING ,
	BOX_NONE

}BOXPATTARN;

/******************************************************************************
* �\����
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffBox;//���_�o�b�t�@

	D3DXVECTOR3 posBox;		//�ʒu���
	D3DXVECTOR3 rotBox;		//��]���
	D3DXVECTOR3 sclBox;		//�{�����

	D3DXVECTOR3 setPosBox;		//���̒��S�_

	bool boxUse;		//�g���Ă邩�ǂ���
	bool boxSpringHit;		//player����ŃW�����v�������ǂ�����
	BOXPATTARN boxPattarn;	//���

}BOX;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitBox( void );
void UninitBox( void );
void UpdateBox( void );
void DrawBox( void );
void SetBox( D3DXVECTOR3 pos , BOXPATTARN boxPattarn );
BOX *GetBox( void );

/*���d�C���N���[�h�h�~*/
#endif
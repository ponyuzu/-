/******************************************************************************
* �^�C�g��  :
* �t�@�C����:obstacl.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2016/01/21
*******************************************************************************
* �X�V����:-2016/01/21 �n糗M��
*           -v0.01 
******************************************************************************/

/*���d�C���N���[�h�h�~*/
#ifndef _OBSTACL_H_
#define _OBSTACL_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
#define OBSTACL_USE_TEX ( true )//�e�N�X�`���̗L��
#define OBSTACL_SURFACE_MAX (6)//��̔��̖ʂ̐�
#define OBSTACL_MAX (10)//���̐�

#define OBSTACL_WIDTH (40)
#define OBSTACL_HEIGHT (40)

//#define OBSTACL_X (1)//x�̃u���b�N��
//#define OBSTACL_Z (1)//z�̃u���b�N��
//
//#define OBSTACL_NUM_INDEX ( ( OBSTACL_X + 1.0 ) * 2.0 * OBSTACL_Z + ( OBSTACL_Z - 1.0 ) * 2.0 )//�C���f�b�N�X��
#define OBSTACL_NUM_VTX (4)//���_��
//#define OBSTACL_NUM_PORIGON ( OBSTACL_X * OBSTACL_Z * 2.0 + 4.0 * ( OBSTACL_Z - 1.0 ) )//�|���S����

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	OBSTACL_NOMAL = 0,
	OBSTACL_SPRING ,
	OBSTACL_NONE

}OBSTACLPATTARN;

/******************************************************************************
* �\����
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffObstacl;//���_�o�b�t�@

	D3DXVECTOR3 posObstacl;		//�ʒu���
	D3DXVECTOR3 rotObstacl;		//��]���
	D3DXVECTOR3 sclObstacl;		//�{�����

	D3DXVECTOR3 setPosObstacl;		//���̒��S�_

	bool obstaclUse;		//�g���Ă邩�ǂ���
	bool obstaclSpringHit;		//player����ŃW�����v�������ǂ�����
	OBSTACLPATTARN obstaclPattarn;	//���

}OBSTACL;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitObstacl( void );
void UninitObstacl( void );
void UpdateObstacl( void );
void DrawObstacl( void );
void SetObstacl( D3DXVECTOR3 pos , OBSTACLPATTARN obstaclPattarn );
OBSTACL *GetObstacl( void );

/*���d�C���N���[�h�h�~*/
#endif
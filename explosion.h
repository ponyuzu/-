/******************************************************************************
* �^�C�g��  :
* �t�@�C����:explosion.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/11/17
*******************************************************************************
* �X�V����:-2015/11/17 �n糗M��
*           -v0.01 
******************************************************************************/

/******************************************************************************
* �C���N���[�h�錾
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

/******************************************************************************
* �}�N����`
******************************************************************************/
#define EXPLOSION_USE_TEX ( true )//�e�N�X�`���̗L��
#define EXPLOSION_MAX (50)//��ʓ��̒e��

#define EXPLOSION_SPEED (3)//�e�̃X�s�[�h

#define EXPLOSION_X (1)//x�̃u���b�N��
#define EXPLOSION_Z (1)//z�̃u���b�N��

#define EXPLOSION_HEIGHT (40.0f)//�e�̏c��
#define EXPLOSION_WIDTH (40.0f)//�e�̉���
#define EXPLOSION_TEX_WIDTH ( 1.0f / 8.0 )//�e�N�X�`������

#define EXPLOSION_TEX_TIME (10)

#define EXPLOSION_NUM_INDEX ( ( EXPLOSION_X + 1.0 ) * 2.0 * EXPLOSION_Z + ( EXPLOSION_Z - 1.0 ) * 2.0 )//�C���f�b�N�X��
#define EXPLOSION_NUM_VTX ( ( EXPLOSION_X + 1.0 ) * ( EXPLOSION_Z + 1.0 ) )//���_��
#define EXPLOSION_NUM_PORIGON ( EXPLOSION_X * EXPLOSION_Z * 2.0 + 4.0 * ( EXPLOSION_Z - 1.0 ) )//�|���S����

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	D3DXVECTOR3 posExplosion;		//�ʒu���
	D3DXVECTOR3 rotExplosion;		//��]���
	D3DXVECTOR3 sclExplosion;		//�{�����

	bool explosionUse;			//�g���Ă邩�ǂ���

	int nCounterAnim;//�A�j���[�V�����J�E���^�[
	int nPatternAnim;//�A�j���[�V�����p�^�[��NO.


}EXPLOSION;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitExplosion( void );
void UninitExplosion( void );
void UpdateExplosion( void );
void DrawExplosion( void );
void SetExplosion( D3DXVECTOR3 pos );
EXPLOSION *GetExplosion( void );

/*���d�C���N���[�h�h�~*/
#endif
/******************************************************************************
* �^�C�g��  :
* �t�@�C����:pause.h
* �� �� ��  :AT12C245 42 �n糗M��
* �� �� ��  :2015/06/22
*******************************************************************************
* �X�V����:-2015/06/22 �n糗M��
*           -v0.01 
******************************************************************************/
/*���d�C���N���[�h�h�~*/
#ifndef _PAUSE_H_
#define _PAUSE_H_

/******************************************************************************
*�C���N���[�h�錾
******************************************************************************/
#include "main.h"

/******************************************************************************
* �}�N����`
******************************************************************************/
#define PAUSE_BG_NAME "data/TEXTURE/pause_bg.jpg"
#define PAUSE_TEX_MAX (4)

#define PAUSE_BG_WIDTH (300)
#define PAUSE_BG_HEIGHT (400)

#define PAUSE_LOGO1_WIDTH (300)
#define PAUSE_LOGO1_HEIGHT (100)

#define PAUSE_LOGO2_WIDTH (300)
#define PAUSE_LOGO2_HEIGHT (100)

#define PAUSE_LOGO3_WIDTH (300)
#define PAUSE_LOGO3_HEIGHT (100)

/******************************************************************************
* �\���̒�`
******************************************************************************/
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuffPause ;

	D3DXVECTOR3 pos;		//�|���S���̒��S�_
	float width;			//�|���S�����S�_����̉���
	float height;			//�|���S�����S�_����̏c��

}PAUSE;

/******************************************************************************
* �񋓌^
******************************************************************************/
typedef enum
{
	PAUSE_CONTINUE = 0,
	PAUSE_RETRY,
	PAUSE_QUIT,
	PAUSE_MAX,
}PAUSEPATTARN;

/******************************************************************************
* �v���g�^�C�v�錾
******************************************************************************/
HRESULT InitPause( void );
void UninitPause( void );
void UpdatePause( void );
void DrawPause( void );
void SetPause( void );
bool GetPause( void );
void SetPause( bool pause );

#endif
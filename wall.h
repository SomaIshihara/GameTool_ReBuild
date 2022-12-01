//==========================================
//
//�|���S���v���O�����̃w�b�_[wall.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _WALL_H_
#define _WALL_H_

//�}�N��
#define MAX_WALL		(16)	//�Ǎő吔
#define WALL_WIDTH		(600)
#define WALL_DEPTH		(600)

//�Ǎ\����
typedef struct
{
	D3DXVECTOR3 pos;				//���S�ʒu
	D3DXVECTOR3 rot;					//����
	float fWidth;						//��
	float fHeight;						//����
	D3DXMATRIX mtxWorld;				//���[���h�}�g���b�N�X
	bool bUse;
} Wall;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
Wall *GetWall(void);

#endif // !_WALL_H_
//==========================================
//
//���f���v���O�����̃w�b�_[object.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//�}�N��
#define MAX_OBJECT			(16)

//�I�u�W�F�N�g�\����
typedef struct
{
	LPD3DXMESH pMesh = NULL;				//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat = NULL;			//�}�e���A���ւ̃|�C���^
	DWORD dwNumMat = 0;						//�}�e���A����
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	LPDIRECT3DTEXTURE9 apTexture[16] = {};	//�e�N�X�`���|�C���^
	D3DXVECTOR3 vtxMin, vtxMax;				//
	int nIdxShadow = -1;					//�e�ԍ�
	bool bUse;								//�g�p�̗L��
} Object;

//�v���g�^�C�v�錾
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
Object *GetObj(void);

#endif // !_OBJECT_H_
//==========================================
//
//���f���v���O�����̃w�b�_[cModel.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_MODEL_H_
#define _CLASS_MODEL_H_

#include "..\..\Core\Main\main.h"

struct cModelStruct
{
	//�`��֌W
	LPD3DXMESH pMesh;		//���b�V��
	LPD3DXBUFFER pBuffMat;	//�}�e���A���|�C���^
	DWORD dwNumMatModel;	//�}�e��
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	D3DXVECTOR3 posOffset;	//�ʒu�i�I�t�Z�b�g�j
	D3DXVECTOR3 rotOffset;	//�����i�I�t�Z�b�g�j
	LPDIRECT3DTEXTURE9 apTexture[16];	//�e�N�X�`���|�C���^
	int mIdxModelParent;	//�e���f���C���f�b�N�X
};

class cModel
{
public:
	cModel();
	~cModel();
	void LoadModel(const char* pPath);
	void SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale);
	cModelStruct GetModel(void);
private:
	cModelStruct m_cModelStr;
};

#endif // !_MODEL_H_

//==========================================
//
//���b�V���t�B�[���h�v���O�����̃w�b�_[meshfield.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "..\..\Core\Main\main.h"

//���b�V���t�B�[���h�\����
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//���_�o�b�t�@�|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;		//�e�N�X�`���|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@
	D3DXVECTOR3 m_pos;					//�ʒu
	D3DXVECTOR3 m_rot;					//����
	int m_width, m_height;				//�c���̕�����
	float m_length;						//����
	D3DXMATRIX m_mtxWorld;				//���[���h�}�g���b�N�X
} Meshfield;

//���b�V���t�B�[���h�N���X
class cMeshfield	
{
public:
	cMeshfield();
	~cMeshfield();
	void Update();
	void Draw();
	void SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pPath, int width, int height,float length);
private:
	Meshfield m_meshData;
};

#endif // !_MESHFIELD_H_

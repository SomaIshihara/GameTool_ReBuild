//==========================================
//
//�e�N�X�`���v���O�����̃w�b�_[cTexture.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_TEXTURE_H_
#define _CLASS_TEXTURE_H_

#include "..\..\Core\Main\main.h"

//�N���X
class cTexture
{
public:
	cTexture();
	~cTexture();
	void LoadTexture(const char* pPath);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���|�C���^
};

#endif // !_CLASS_TEXTURE_H_

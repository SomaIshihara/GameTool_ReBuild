//==========================================
//
//�e�N�X�`���֌W�v���O����[cTexture.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "main.h"
#include "cTexture.h"

cTexture::cTexture()
{
	
}

cTexture::~cTexture()
{
	//�e�N�X�`���̔j��
	if (this->m_pTexture != NULL)
	{
		this->m_pTexture->Release();
		this->m_pTexture = NULL;
	}
}

void cTexture::LoadTexture(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		pPath,
		&this->m_pTexture);
}
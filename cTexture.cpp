//==========================================
//
//テクスチャ関係プログラム[cTexture.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "cTexture.h"

cTexture::cTexture()
{
	
}

cTexture::~cTexture()
{
	//テクスチャの破棄
	if (this->m_pTexture != NULL)
	{
		this->m_pTexture->Release();
		this->m_pTexture = NULL;
	}
}

void cTexture::LoadTexture(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		pPath,
		&this->m_pTexture);
}
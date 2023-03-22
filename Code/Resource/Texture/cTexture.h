//==========================================
//
//テクスチャプログラムのヘッダ[cTexture.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_TEXTURE_H_
#define _CLASS_TEXTURE_H_

#include "..\..\Core\Main\main.h"

//クラス
class cTexture
{
public:
	cTexture();
	~cTexture();
	void LoadTexture(const char* pPath);
private:
	LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャポインタ
};

#endif // !_CLASS_TEXTURE_H_

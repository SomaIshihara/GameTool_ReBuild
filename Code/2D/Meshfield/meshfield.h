//==========================================
//
//メッシュフィールドプログラムのヘッダ[meshfield.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "..\..\Core\Main\main.h"

//メッシュフィールド構造体
typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 m_pVtxbuff;	//頂点バッファポインタ
	LPDIRECT3DTEXTURE9 m_pTexture;		//テクスチャポインタ
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//インデックスバッファ
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_rot;					//向き
	int m_width, m_height;				//縦横の分割数
	float m_length;						//長さ
	D3DXMATRIX m_mtxWorld;				//ワールドマトリックス
} Meshfield;

//メッシュフィールドクラス
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

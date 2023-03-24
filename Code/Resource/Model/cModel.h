//==========================================
//
//モデルプログラムのヘッダ[cModel.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_MODEL_H_
#define _CLASS_MODEL_H_

#include "..\..\Core\Main\main.h"

struct cModelStruct
{
	//描画関係
	LPD3DXMESH pMesh;		//メッシュ
	LPD3DXBUFFER pBuffMat;	//マテリアルポインタ
	DWORD dwNumMatModel;	//マテ数
	D3DXMATRIX mtxWorld;	//ワールドマトリ
	D3DXVECTOR3 posOffset;	//位置（オフセット）
	D3DXVECTOR3 rotOffset;	//向き（オフセット）
	LPDIRECT3DTEXTURE9 apTexture[16];	//テクスチャポインタ
	int mIdxModelParent;	//親モデルインデックス
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

//==========================================
//
//モデルプログラムのヘッダ[cModel.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_MODEL_H_
#define _CLASS_MODEL_H_

#include "..\..\Core\Main\main.h"

struct ModelStruct
{
	//描画関係
	LPD3DXMESH pMesh;		//メッシュ
	LPD3DXBUFFER pBuffMat;	//マテリアルポインタ
	DWORD dwNumMatModel;	//マテ数
	LPDIRECT3DTEXTURE9 apTexture[16];	//テクスチャポインタ
	D3DXMATRIX mtxWorld;	//ワールドマトリ

	//変更可能
	D3DXVECTOR3 posOffset;	//位置（オフセット）
	D3DXVECTOR3 rotOffset;	//向き（オフセット）
	int m_IdxModelParent;	//親モデルインデックス

	//使用有無
	bool m_bUse;			//使用の有無
};

//========================
//モデル単体
//========================
class cModel
{
public:
	cModel();
	~cModel();
	void LoadModel(const char* pPath);
	void SetModelSetup(ModelStruct modelstr);
	void DrawModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXMATRIX *pMtxBace, D3DXMATRIX *mtxParent = NULL);
	ModelStruct GetModel(void);
protected:
	ModelStruct m_cModelStr;
};

#endif // !_MODEL_H_

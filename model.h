//==========================================
//
//モデルプログラムのヘッダ[model.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_

//モデル構造体
typedef struct
{
	LPD3DXMESH pMesh;		//メッシュ
	LPD3DXBUFFER pBuffMat;	//マテリアルポインタ
	DWORD dwNumMatModel;	//マテ数
	D3DXVECTOR3 pos;		//位置（オフセット）
	D3DXVECTOR3 rot;		//向き
	D3DXMATRIX mtxWorld;	//ワールドマトリ
	LPDIRECT3DTEXTURE9 apTexture[16];	//テクスチャポインタ
	int nIdxModelParent;	//親モデルインデックス
} Model;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);

#endif // !_MODEL_H_

//==========================================
//
//モデルプログラムのヘッダ[object.h]
//Author:石原颯馬
//
//==========================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//マクロ
#define MAX_OBJECT			(16)

//オブジェクト構造体
typedef struct
{
	LPD3DXMESH pMesh = NULL;				//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat = NULL;			//マテリアルへのポインタ
	DWORD dwNumMat = 0;						//マテリアル数
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	LPDIRECT3DTEXTURE9 apTexture[16] = {};	//テクスチャポインタ
	D3DXVECTOR3 vtxMin, vtxMax;				//
	int nIdxShadow = -1;					//影番号
	bool bUse;								//使用の有無
} Object;

//プロトタイプ宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
Object *GetObj(void);

#endif // !_OBJECT_H_

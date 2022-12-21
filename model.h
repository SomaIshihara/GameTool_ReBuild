//==========================================
//
//モデルプログラムのヘッダ[model.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MODEL_H_
#define _MODEL_H_

//マクロ
#define EXITHUMAN_MODEL_NUM	(10)	//非常口の人に使われているモデル数
#define PUSHING_BACK		(1.0f)	//オブジェクトに当たった時の押し戻し

//非常口の人の幅高さ
#define EXITHUMAN_WIDTH		(30.0f)
#define EXITHUMAN_HEIGHT	(30.0f)

//モデル名列挙
typedef enum
{
	MODELNAME_EXITHUMAN = 0,
	MODELNAME_MAX
} MODELNAME;

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
Model *GetModel(MODELNAME name);

#endif // !_MODEL_H_

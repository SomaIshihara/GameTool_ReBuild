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
//オブジェクト状態列挙
typedef enum
{
	OBJSTATE_NONE = 0,
	OBJSTATE_DAMAGE,
	OBJSTATE_BROKEN,
	OBJSTATE_MAX
} OBJSTATE;

//オブジェクト構造体
typedef struct
{
	//オブジェクト見た目関係
	LPD3DXMESH pMesh = NULL;				//メッシュへのポインタ
	LPD3DXBUFFER pBuffMat = NULL;			//マテリアルへのポインタ
	DWORD dwNumMat = 0;						//マテリアル数
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXMATRIX mtxWorld;					//ワールドマトリックス
	LPDIRECT3DTEXTURE9 apTexture[16] = {};	//テクスチャポインタ
	D3DXVECTOR3 vtxMin, vtxMax;				//小さい頂点・大きい頂点
	int nIdxShadow = -1;					//影番号

	//ステータス関係
	int nLife;			//体力
	OBJSTATE state;		//状態
	int nCounterState;

	//使用の有無
	bool bUse;								//使用の有無
} Object;

//プロトタイプ宣言
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
Object *GetObj(void);
void HitObj(int nNumObj);
void DestroyObj(int nNumObj);

#endif // !_OBJECT_H_

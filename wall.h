//==========================================
//
//ポリゴンプログラムのヘッダ[wall.h]
//Author:石原颯馬
//
//==========================================
#ifndef _WALL_H_
#define _WALL_H_

//マクロ
#define MAX_WALL		(16)	//壁最大数
#define WALL_WIDTH		(600)
#define WALL_DEPTH		(600)

//壁構造体
typedef struct
{
	D3DXVECTOR3 pos;					//中心位置
	D3DXVECTOR3 rot;					//向き
	float fWidth;						//幅
	float fHeight;						//高さ
	D3DXMATRIX mtxWorld;				//ワールドマトリックス
	bool bUse;
} Wall;

//プロトタイプ宣言
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);
void SetWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight);
Wall *GetWall(void);

#endif // !_WALL_H_

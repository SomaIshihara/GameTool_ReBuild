//==========================================
//
//当たり判定プログラムのヘッダ[collision.h]
//Author:石原颯馬
//
//==========================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "..\..\Core\Main\main.h"

//当たり判定範囲構造体
typedef struct
{
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
} CollisionPos;

typedef struct
{
	CollisionPos m_collPos;		//当たり判定に使う点
	D3DXVECTOR3 m_pos;			//中心位置
	D3DXVECTOR3 m_rot;			//当たり判定の向き
	D3DXVECTOR3 m_vecNor;		//法線ベクトル
} Collision;

//板の当たり判定
class cCollision
{
public:
	void SetCollision(D3DXVECTOR3 rot, CollisionPos collPos);
	bool CollisionCheck(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *posCloss = NULL);
private:
	Collision m_coll;
};

//箱の当たり判定
class cBoxCollider
{
public:
	void SetBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth);
private:
	cCollision m_collPlane[6];
};

//プロトタイプ宣言
#if 0
bool CollisionPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth);										//プレイヤー同士の衝突判定
bool CollisionHipDropPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth, float fRadius, float fPower);	//ヒップドロップ時の衝突判定
bool CollisionFence(Player *pPlayer, float fFenceWidth, float fPlayerHeight, float fFenceDepth, float fenceSize);		//フェンスの衝突処理
#endif

#endif // !_COLLISION_H_

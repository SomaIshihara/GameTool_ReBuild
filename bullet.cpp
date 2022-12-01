//==========================================
//
//弾表示プログラム[bullet.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "bullet.h"
#include "shadow.h"
#include "wall.h"
#include "player.h"
#include "object.h"

//マクロ
#define MAX_BULLET				(128)	//弾の最大数
#define BULLET_TEXSIZE_WIDTH	(12)	//弾のサイズ（幅）
#define BULLET_TEXSIZE_HEIGHT	(12)	//弾のサイズ（高さ）

//仮
#define POS0	D3DXVECTOR3(-100.0f,0.0f,100.0f)
#define POS1	D3DXVECTOR3(100.0f,0.0f,100.0f)

//弾構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//前回の位置
	D3DXVECTOR3 move;	//移動量
	D3DXCOLOR col;		//弾の色
	int nLife;			//寿命
	int nIdxShadow;		//影番号
	bool bUse;			//使っているかどうか
} Bullet;

void CollisionWallBullet(int nCount);
void CollisionObjBullet(int nCount);

LPDIRECT3DTEXTURE9 g_pTextureBullet;	//テクスチャポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffBullet;	//頂点バッファポインタ
D3DXMATRIX g_mtxWorldBullet[MAX_BULLET];	//ワールドマトリックス
Bullet g_aBullet[MAX_BULLET];			//弾構造体

//========================
//弾初期化処理
//========================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;	//デバイスのポインタ
	int nCntBullet;				//カウンタ

	pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	//弾構造体の中身初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nLife = 100;
		g_aBullet[nCntBullet].nIdxShadow = -1;
		g_aBullet[nCntBullet].bUse = false;
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffBullet,
		NULL);

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++,pVtx += 4)
	{
		//頂点座標（相対座標）
		pVtx[0].pos = D3DXVECTOR3(-2.0f, 2.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(2.0f, 2.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-2.0f, -2.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(2.0f, -2.0f, 0.0f);

		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点バッファをアンロック
	g_pVtxbuffBullet->Unlock();
}

//========================
//弾終了処理
//========================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffBullet != NULL)
	{
		g_pVtxbuffBullet->Release();
		g_pVtxbuffBullet = NULL;
	}
}

//========================
//弾更新処理
//========================
void UpdateBullet(void)
{
	int nCntBullet;		//カウンタ
	VERTEX_3D *pVtx;	//設定用ポインタ

	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffBullet->Lock(0, 0, (void **)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pVtx += 4)
	{
		if (g_aBullet[nCntBullet].bUse)
		{//弾が使用されている
			//今いる位置を前回の位置にする
			g_aBullet[nCntBullet].posOld = g_aBullet[nCntBullet].pos;

			//位置更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			//当たり判定
			CollisionWallBullet(nCntBullet);
			CollisionObjBullet(nCntBullet);

			//影位置設定
			SetPositionShadow(g_aBullet[nCntBullet].nIdxShadow, g_aBullet[nCntBullet].pos);

			g_aBullet[nCntBullet].nLife--;
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//寿命尽きた
				g_aBullet[nCntBullet].bUse = false;
				ReleaseIdxShadow(g_aBullet[nCntBullet].nIdxShadow);
			}
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffBullet->Unlock();
}

//========================
//弾描画処理
//========================
void DrawBullet(void)
{
	int nCntBullet;				//カウンタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxTrans;	//計算用
	D3DXMATRIX mtxView;		//ビューマトリ取得用

	//Zテスト無効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);	//Zテストを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);	//Zバッファの有効・無効設定

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_mtxWorldBullet[nCntBullet]);

			//ビューマトリ取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_mtxWorldBullet[nCntBullet], NULL, &mtxView);
			//修正
			g_mtxWorldBullet[nCntBullet]._41 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._42 = 0.0f;
			g_mtxWorldBullet[nCntBullet]._43 = 0.0f;

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aBullet[nCntBullet].pos.x, g_aBullet[nCntBullet].pos.y, g_aBullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_mtxWorldBullet[nCntBullet], &g_mtxWorldBullet[nCntBullet], &mtxTrans);
		}
	}

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffBullet, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureBullet);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse)
		{
			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBullet[nCntBullet]);

			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntBullet, 2);
		}
	}

	//Zテスト有効化
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);	//Zテストを行わない
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	//Zバッファの有効・無効設定
}

//========================
//弾設定処理
//========================
void SetBullet(D3DXVECTOR3 pos, float fSpeed,float fRot, D3DXCOLOR col)
{
	int nCntBullet;		//カウンタ

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (!g_aBullet[nCntBullet].bUse)
		{
			//座標（中心）設定
			g_aBullet[nCntBullet].pos = pos;

			//色設定
			g_aBullet[nCntBullet].col = col;

			//移動量計算
			g_aBullet[nCntBullet].move.x = -sinf(fRot) * fSpeed;
			g_aBullet[nCntBullet].move.z = -cosf(fRot) * fSpeed;

			//寿命設定
			g_aBullet[nCntBullet].nLife = 1000;

			//影番号設定
			g_aBullet[nCntBullet].nIdxShadow = SetShadow();

			//使用していることにする
			g_aBullet[nCntBullet].bUse = true;

			//抜ける
			break;
		}
	}
}

//========================
//弾当たり判定処理
//========================
void CollisionWallBullet(int nCount)
{
	Wall *wall = GetWall();
	D3DXVECTOR3 pos0, pos1;
	D3DXVECTOR3 vecLine;
	D3DXVECTOR3 vecToPos;

	for (int nCntWall = 0; nCntWall < MAX_WALL; nCntWall++, wall++)
	{
		//使っているときだけ処理
		if (wall->bUse == true)
		{
			//位置計算
			pos0.x = wall->pos.x - (wall->fWidth / 2) * cosf(wall->rot.y);
			pos0.y = 0.0f;
			pos0.z = wall->pos.z + (wall->fWidth / 2) * sinf(wall->rot.y);

			pos1.x = wall->pos.x + (wall->fWidth / 2) * cosf(wall->rot.y);
			pos1.y = 0.0f;
			pos1.z = wall->pos.z - (wall->fWidth / 2) * sinf(wall->rot.y);

			vecLine = pos1 - pos0;	//境界線ベクトル
			vecToPos = g_aBullet[nCount].pos - pos0;

			if ((vecLine.z * vecToPos.x) - (vecLine.x * vecToPos.z) <= 0)
			{
				g_aBullet[nCount].bUse = false;
				ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
			}
		}
	}
}

//========================
//弾当たり判定処理
//========================
void CollisionObjBullet(int nCount)
{
	Object *obj = GetObj();
	D3DXVECTOR3 pos0x, pos1x, pos0z, pos1z;
	D3DXVECTOR3 vecLinex, vecToPosx, vecLinez, vecToPosz;
	D3DXVECTOR3 vecMove;
	float fAreaA, fAreaB;

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++, obj++)
	{
		if (obj->bUse == true)
		{
			//各2頂点求める
			pos0x = obj->pos + D3DXVECTOR3(obj->vtxMin.x, 0.0f, 0.0f);
			pos1x = obj->pos + D3DXVECTOR3(obj->vtxMax.x, 0.0f, 0.0f);
			pos0z = obj->pos + D3DXVECTOR3(0.0f, 0.0f, obj->vtxMax.z);
			pos1z = obj->pos + D3DXVECTOR3(0.0f, 0.0f, obj->vtxMin.z);

			//ベクトル求める
			//move
			vecMove = g_aBullet[nCount].pos - g_aBullet[nCount].posOld;

			//X
			vecLinex = pos1x - pos0x;
			vecToPosx = g_aBullet[nCount].pos - pos0x;

			//Z
			vecLinez = pos1z - pos0z;
			vecToPosz = g_aBullet[nCount].pos - pos0z;

			//当たり判定本番
			for (int nCount = 0; nCount < 2; nCount++)//仮
			{
				//X
				//面積求める
				fAreaA = (vecToPosx.z * vecMove.x) - (vecToPosx.x * vecMove.z);
				fAreaB = (vecLinex.z * vecMove.x) - (vecLinex.x * vecMove.z);

				//左側AND範囲内
				if ((vecLinex.z * vecToPosx.x) - (vecLinex.x * vecToPosx.z) <= 0 && fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
				}

				//Z
				//面積求める
				fAreaA = (vecToPosz.z * vecMove.x) - (vecToPosz.x * vecMove.z);
				fAreaB = (vecLinez.z * vecMove.x) - (vecLinez.x * vecMove.z);

				//左側AND範囲内
				if ((vecLinez.z * vecToPosz.x) - (vecLinez.x * vecToPosz.z) <= 0 && fAreaA / fAreaB >= 0.0f && fAreaA / fAreaB <= 1.0f)
				{
					g_aBullet[nCount].bUse = false;
					ReleaseIdxShadow(g_aBullet[nCount].nIdxShadow);
				}

				//ベクトル反転
				//X
				vecLinex.x *= -1.0f;
				vecLinex.y *= -1.0f;
				vecLinex.z *= -1.0f;
				vecToPosx.x *= -1.0f;
				vecToPosx.y *= -1.0f;
				vecToPosx.z *= -1.0f;

				//Z
				vecLinez.x *= -1.0f;
				vecLinez.y *= -1.0f;
				vecLinez.z *= -1.0f;
				vecToPosz.x *= -1.0f;
				vecToPosz.y *= -1.0f;
				vecToPosz.z *= -1.0f;
			}
		}
	}
}
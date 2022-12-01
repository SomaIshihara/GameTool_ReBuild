//==========================================
//
//プレイヤープログラム[player.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "player.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//マクロ
#define PLAYER_MOVE_SPEED	(5.0f)	//プレイヤー移動速度
#define DUMP_COEF			(0.4f)	//減衰係数

//仮
#define PLAYER_WIDTH		(20.0f)
#define PLAYER_DEPTH		(15.0f)

//向き
#define ROT_WA	(-0.75f * D3DX_PI)	//左上
#define ROT_WD	(0.75f * D3DX_PI)	//右上
#define ROT_SA	(-0.25f * D3DX_PI)	//左下
#define ROT_SD	(0.25f * D3DX_PI)	//右下
#define ROT_W	(1.0f * D3DX_PI)	//上
#define ROT_A	(-0.5f * D3DX_PI)	//左
#define ROT_S	(0.0f * D3DX_PI)	//下
#define ROT_D	(0.5f * D3DX_PI)	//右

//プロト
void CollisionWallPlayer(int nNumber);
void CollisionObjPlayer(void);

//グローバル変数
LPD3DXMESH g_pMeshPlayer = NULL;			//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatPlayer = NULL;		//マテリアルへのポインタ
DWORD g_dwNumMatPlayer = 0;					//マテリアル数
Player g_player;
D3DXMATRIX g_mtxWorldPlayer;				//ワールドマトリックス
LPDIRECT3DTEXTURE9 g_apTexturemodel[16] = {};	//テクスチャポインタ
int g_nIdxShadow = -1;

//========================
//初期化処理
//========================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	g_player.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.summitOld[0] = g_player.pos + D3DXVECTOR3(-PLAYER_WIDTH / 2, 0.0f, PLAYER_DEPTH / 2);
	g_player.summitOld[1] = g_player.pos + D3DXVECTOR3(PLAYER_WIDTH / 2, 0.0f, PLAYER_DEPTH / 2);
	g_player.summitOld[2] = g_player.pos + D3DXVECTOR3(-PLAYER_WIDTH / 2, 0.0f, -PLAYER_DEPTH / 2);
	g_player.summitOld[3] = g_player.pos + D3DXVECTOR3(PLAYER_WIDTH / 2, 0.0f, -PLAYER_DEPTH / 2);

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nIdxShadow = -1;

	//対角線の長さ・角度
	g_player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_DEPTH * PLAYER_DEPTH) * 0.5f;
	g_player.fAngle = atan2f(PLAYER_WIDTH, PLAYER_DEPTH);

	//Xファイル読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\car000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatPlayer,
		NULL,
		&g_dwNumMatPlayer,
		&g_pMeshPlayer);

	//（本来は読み込めたかチェックがいる）

	//テクスチャ読み込み
	D3DXMATERIAL *pMat;	//マテリアルポインタ

	//マテリアル情報に対するポインタ取得
	pMat = (D3DXMATERIAL *)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntTex = 0; nCntTex < (int)g_dwNumMatPlayer; nCntTex++)
	{
		if (pMat[nCntTex].pTextureFilename != NULL)
		{
			//テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntTex].pTextureFilename,
				&g_apTexturemodel[nCntTex]);
		}
	}

	//影設定
	g_nIdxShadow = SetShadow();
}

//========================
//終了処理
//========================
void UninitPlayer(void)
{
	//メッシュの破棄
	if (g_pMeshPlayer != NULL)
	{
		g_pMeshPlayer->Release();
		g_pMeshPlayer = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatPlayer != NULL)
	{
		g_pBuffMatPlayer->Release();
		g_pBuffMatPlayer = NULL;
	}
}

//========================
//更新処理
//========================
void UpdatePlayer(void)
{
	//現在の位置を前回の位置にする
	g_player.posOld = g_player.pos;

	//カメラ向きに応じてプレイヤーの向き旋回
	if (GetMouseClickPress(MOUSE_CLICK_LEFT) == true)
	{
		g_player.rot.y = -(float)fmod(GetCamera()->rot.y + 1.0f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
	}

	//モデル移動
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
			g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
			g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		}
		else
		{
			g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_W + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
			g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
			g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
			g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		}
		else
		{
			g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_S + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
			g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{
		g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_A + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
		g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_player.rot.y = -(float)fmod(GetCamera()->rot.y + ROT_D + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
		g_player.move.x = sinf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
		g_player.move.z = cosf((float)fmod((g_player.rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * PLAYER_MOVE_SPEED;
	}

	//ボタン操作に応じてプレイヤー・カメラ視点・注視点移動
	g_player.pos.x += g_player.move.x;
	g_player.pos.z += g_player.move.z;

	//壁当たり判定
	CollisionWallPlayer(0);

	//オブジェクト当たり判定
	CollisionObjPlayer();

	GetCamera()->posV.x += g_player.pos.x - g_player.posOld.x;
	GetCamera()->posV.z += g_player.pos.z - g_player.posOld.z;
	GetCamera()->posR.x += g_player.pos.x - g_player.posOld.x;
	GetCamera()->posR.z += g_player.pos.z - g_player.posOld.z;

	//移動量減衰
	g_player.move.x += (0 - g_player.move.x) * DUMP_COEF;
	g_player.move.z += (0 - g_player.move.z) * DUMP_COEF;

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_player.pos, 5.0f, g_player.rot.y, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//影位置設定
	SetPositionShadow(g_nIdxShadow, g_player.pos);
}

//========================
//描画処理
//========================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldPlayer);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_mtxWorldPlayer, &g_mtxWorldPlayer, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPlayer);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)g_pBuffMatPlayer->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatPlayer; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャ設定
		pDevice->SetTexture(0, g_apTexturemodel[nCntMat]);

		//モデル描画
		g_pMeshPlayer->DrawSubset(nCntMat);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//壁当たり判定処理
//========================
void CollisionWallPlayer(int nNumber)
{
	if (g_player.pos.x + PLAYER_WIDTH / 2 > WALL_WIDTH / 2)
	{
		g_player.pos.x = WALL_WIDTH / 2 - PLAYER_WIDTH / 2;
	}
	else if (g_player.pos.x - PLAYER_WIDTH / 2 < -WALL_WIDTH / 2)
	{
		g_player.pos.x = -WALL_WIDTH / 2 + PLAYER_WIDTH / 2;
	}

	if (g_player.pos.z + PLAYER_DEPTH / 2 > WALL_DEPTH / 2)
	{
		g_player.pos.z = WALL_DEPTH / 2 - PLAYER_DEPTH / 2;
	}
	else if (g_player.pos.z - PLAYER_DEPTH / 2 < -WALL_DEPTH / 2)
	{
		g_player.pos.z = -WALL_DEPTH / 2 + PLAYER_DEPTH / 2;
	}
}

//========================
//オブジェクト当たり判定処理
//========================
void CollisionObjPlayer(void)
{
	Object *obj = GetObj();

	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++, obj++)
	{
		if (obj->bUse == true)
		{
			if (g_player.pos.z >= obj->pos.z + obj->vtxMin.z && g_player.pos.z <= obj->pos.z + obj->vtxMax.z)
			{
				if (g_player.posOld.x <= obj->pos.x + obj->vtxMin.x && g_player.pos.x > obj->pos.x + obj->vtxMin.x)
				{
					g_player.pos.x = obj->pos.x + obj->vtxMin.x;
				}
				if (g_player.posOld.x >= obj->pos.x + obj->vtxMax.x && g_player.pos.x < obj->pos.x + obj->vtxMax.x)
				{
					g_player.pos.x = obj->pos.x + obj->vtxMax.x;
				}
			}

			if (g_player.pos.x >= obj->pos.x + obj->vtxMin.x && g_player.pos.x <= obj->pos.x + obj->vtxMax.x)
			{
				if (g_player.posOld.z <= obj->pos.z + obj->vtxMin.z && g_player.pos.z > obj->pos.z + obj->vtxMin.z)
				{
					g_player.pos.z = obj->pos.z + obj->vtxMin.z;
				}
				if (g_player.posOld.z >= obj->pos.z + obj->vtxMax.z && g_player.pos.z < obj->pos.z + obj->vtxMax.z)
				{
					g_player.pos.z = obj->pos.z + obj->vtxMax.z;
				}
			}
		}
	}
}

//========================
//取得処理
//========================
Player *GetPlayer(void)
{
	return &g_player;
}
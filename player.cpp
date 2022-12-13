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
#include "meshfield.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//マクロ
#define PLAYER_MOVE_SPEED	(7.0f)	//プレイヤー移動速度
#define DUMP_COEF			(0.4f)	//減衰係数
#define BULLET_SPEED		(15.0f)	//弾の速さ

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
Player g_player;
int g_nIdxShadow = -1;

//ファイル名
const char *c_pFileNamePlayer[] =
{
	"data\\MODEL\\exithuman_x\\01_Body.x",
	"data\\MODEL\\exithuman_x\\02_Head.x",
	"data\\MODEL\\exithuman_x\\03_Left_Arm.x",
	"data\\MODEL\\exithuman_x\\04_Left_Hand.x",
	"data\\MODEL\\exithuman_x\\05_Right_Arm.x",
	"data\\MODEL\\exithuman_x\\06_Right_Hand.x",
	"data\\MODEL\\exithuman_x\\07_Left_Leg.x",
	"data\\MODEL\\exithuman_x\\08_Left_Foot.x",
	"data\\MODEL\\exithuman_x\\09_Right_Leg.x",
	"data\\MODEL\\exithuman_x\\10_Right_Foot.x"
};

//========================
//初期化処理
//========================
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	g_player.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_player.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nIdxShadow = -1;

	for (int nCntInitModel = 0; nCntInitModel < EXITHUMAN_MODEL_NUM; nCntInitModel++)
	{
		g_player.aModel[nCntInitModel] = {};
	}
	g_player.nNumModel = 0;

	//対角線の長さ・角度
	g_player.fLength = sqrtf(PLAYER_WIDTH * PLAYER_WIDTH + PLAYER_DEPTH * PLAYER_DEPTH) * 0.5f;
	g_player.fAngle = atan2f(PLAYER_WIDTH, PLAYER_DEPTH);

	//Xファイル読み込み
	for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
	{
		D3DXLoadMeshFromX(
			c_pFileNamePlayer[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_player.aModel[nCntModel].pBuffMat,
			NULL,
			&g_player.aModel[nCntModel].dwNumMatModel,
			&g_player.aModel[nCntModel].pMesh);

		//テクスチャ読み込み
		D3DXMATERIAL *pMat;	//マテリアルポインタ

		//マテリアル情報に対するポインタ取得
		pMat = (D3DXMATERIAL *)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntTex = 0; nCntTex < (int)g_player.aModel[nCntModel].dwNumMatModel; nCntTex++)
		{
			if (pMat[nCntTex].pTextureFilename != NULL)
			{
				//テクスチャ読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntTex].pTextureFilename,
					&g_player.aModel[nCntModel].apTexture[nCntTex]);
			}
		}
	}

	//階層構造設定
	//体
	g_player.aModel[0].nIdxModelParent = -1;
	g_player.aModel[0].pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
	g_player.aModel[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//頭
	g_player.aModel[1].nIdxModelParent = 0;
	g_player.aModel[1].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_player.aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左腕
	g_player.aModel[2].nIdxModelParent = 0;
	g_player.aModel[2].pos = D3DXVECTOR3(-5.0f, 7.0f, 0.0f);
	g_player.aModel[2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左手
	g_player.aModel[3].nIdxModelParent = 2;
	g_player.aModel[3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_player.aModel[3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右腕
	g_player.aModel[4].nIdxModelParent = 0;
	g_player.aModel[4].pos = D3DXVECTOR3(5.0f, 7.0f, 0.0f);
	g_player.aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右手
	g_player.aModel[5].nIdxModelParent = 4;
	g_player.aModel[5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_player.aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左腿
	g_player.aModel[6].nIdxModelParent = 0;
	g_player.aModel[6].pos = D3DXVECTOR3(-3.0f, -8.0f, 0.0f);
	g_player.aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左足
	g_player.aModel[7].nIdxModelParent = 6;
	g_player.aModel[7].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);
	g_player.aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右腿
	g_player.aModel[8].nIdxModelParent = 0;
	g_player.aModel[8].pos = D3DXVECTOR3(3.0f, -8.0f, 0.0f);
	g_player.aModel[8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右足
	g_player.aModel[9].nIdxModelParent = 8;
	g_player.aModel[9].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);
	g_player.aModel[9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影設定
	g_nIdxShadow = SetShadow();
}

//========================
//終了処理
//========================
void UninitPlayer(void)
{
	for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
	{
		//メッシュの破棄
		if (g_player.aModel[nCntModel].pMesh != NULL)
		{
			g_player.aModel[nCntModel].pMesh->Release();
			g_player.aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_player.aModel[nCntModel].pBuffMat != NULL)
		{
			g_player.aModel[nCntModel].pBuffMat->Release();
			g_player.aModel[nCntModel].pBuffMat = NULL;
		}
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

	if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		SetBullet(g_player.pos + D3DXVECTOR3(0.0f, 40.0f, 0.0f) , BULLET_SPEED, g_player.rot.y, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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

	//プレイヤー位置表示
	PrintDebugProc("Player.Pos = (x = %f, y = %f, z = %f)", g_player.pos.x, g_player.pos.y, g_player.pos.z);

	//"プレイヤーの"ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//"プレイヤーの"ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_player.mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用
		D3DXMATRIX mtxParent;					//親のマトリ

		//"モデルの"ワールドマトリックス初期化
		D3DXMatrixIdentity(&g_player.aModel[nCntModel].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_player.aModel[nCntModel].rot.y, g_player.aModel[nCntModel].rot.x, g_player.aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxRotModel);

		//位置反映
		D3DXMatrixTranslation(&mtxTransModel, g_player.aModel[nCntModel].pos.x, g_player.aModel[nCntModel].pos.y, g_player.aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxTransModel);

		//パーツの親マトリ設定
		if (g_player.aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_player.aModel[g_player.aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_player.mtxWorld;
		}

		//パーツのマトリと親マトリをかけ合わせる
		D3DXMatrixMultiply(&g_player.aModel[nCntModel].mtxWorld, &g_player.aModel[nCntModel].mtxWorld, &mtxParent);

		//"プレイヤーの"ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_player.aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタ取得
		pMat = (D3DXMATERIAL*)g_player.aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_player.aModel[nCntModel].dwNumMatModel; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_player.aModel[nCntModel].apTexture[nCntMat]);

			//モデル描画
			g_player.aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//壁当たり判定処理
//========================
void CollisionWallPlayer(int nNumber)
{
	if (g_player.pos.x + PLAYER_WIDTH / 2 > MESHFIELD_WIDTH * MESHFIELD_LENGTH / 2)
	{
		g_player.pos.x = MESHFIELD_WIDTH * MESHFIELD_LENGTH / 2 - PLAYER_WIDTH / 2;
	}
	else if (g_player.pos.x - PLAYER_WIDTH / 2 < -MESHFIELD_WIDTH * MESHFIELD_LENGTH / 2)
	{
		g_player.pos.x = -MESHFIELD_WIDTH * MESHFIELD_LENGTH / 2 + PLAYER_WIDTH / 2;
	}

	if (g_player.pos.z + PLAYER_DEPTH / 2 > MESHFIELD_HEIGHT * MESHFIELD_LENGTH / 2)
	{
		g_player.pos.z = MESHFIELD_HEIGHT * MESHFIELD_LENGTH / 2 - PLAYER_DEPTH / 2;
	}
	else if (g_player.pos.z - PLAYER_DEPTH / 2 < -MESHFIELD_HEIGHT * MESHFIELD_LENGTH / 2)
	{
		g_player.pos.z = -MESHFIELD_HEIGHT * MESHFIELD_LENGTH / 2 + PLAYER_DEPTH / 2;
	}
}

//========================
//オブジェクト当たり判定処理
//========================
void CollisionObjPlayer(void)
{
	Object *obj = GetObj();
	BluePrint *pBPrint = GetBluePrint();

	for (int nCntObj = 0; nCntObj < BLUEPRINTIDX_MAX; nCntObj++, obj++)
	{
		if (obj->bUse == true)
		{
			if (g_player.pos.z >= obj->pos.z + (pBPrint + obj->bpidx)->vtxMin.z && g_player.pos.z <= obj->pos.z + (pBPrint + obj->bpidx)->vtxMax.z)
			{
				if (g_player.posOld.x <= obj->pos.x + (pBPrint + obj->bpidx)->vtxMin.x && g_player.pos.x > obj->pos.x + (pBPrint + obj->bpidx)->vtxMin.x)
				{
					g_player.pos.x = obj->pos.x + (pBPrint + obj->bpidx)->vtxMin.x;
				}
				if (g_player.posOld.x >= obj->pos.x + (pBPrint + obj->bpidx)->vtxMax.x && g_player.pos.x < obj->pos.x + (pBPrint + obj->bpidx)->vtxMax.x)
				{
					g_player.pos.x = obj->pos.x + (pBPrint + obj->bpidx)->vtxMax.x;
				}
			}

			if (g_player.pos.x >= obj->pos.x + (pBPrint + obj->bpidx)->vtxMin.x && g_player.pos.x <= obj->pos.x + (pBPrint + obj->bpidx)->vtxMax.x)
			{
				if (g_player.posOld.z <= obj->pos.z + (pBPrint + obj->bpidx)->vtxMin.z && g_player.pos.z > obj->pos.z + (pBPrint + obj->bpidx)->vtxMin.z)
				{
					g_player.pos.z = obj->pos.z + (pBPrint + obj->bpidx)->vtxMin.z;
				}
				if (g_player.posOld.z >= obj->pos.z + (pBPrint + obj->bpidx)->vtxMax.z && g_player.pos.z < obj->pos.z + (pBPrint + obj->bpidx)->vtxMax.z)
				{
					g_player.pos.z = obj->pos.z + (pBPrint + obj->bpidx)->vtxMax.z;
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
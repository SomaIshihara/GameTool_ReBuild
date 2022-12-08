//==========================================
//
//プレイヤープログラム[enemy.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "enemy.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"
#include "wall.h"
#include "object.h"
#include "debugproc.h"
#include <assert.h>

//マクロ
#define ENEMY_MOVE_SPEED	(5.0f)	//プレイヤー移動速度
#define DUMP_COEF			(0.4f)	//減衰係数

//仮
#define ENEMY_WIDTH		(20.0f)
#define ENEMY_DEPTH		(15.0f)

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
void CollisionWallEnemy(int nNumber);
void CollisionObjEnemy(void);

//グローバル変数
Enemy g_enemy[MAX_ENEMY];

//ファイル名
const char *c_pFileNameEnemy[] =
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
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//敵に情報を追加
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//変数初期化
		g_enemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_enemy[nCntEnemy].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_enemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_enemy[nCntEnemy].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//使用モデル取得
		g_enemy[nCntEnemy].pModel = GetModel(MODELNAME_EXITHUMAN);

		//対角線の長さ・角度
		g_enemy[nCntEnemy].fLength = sqrtf(ENEMY_WIDTH * ENEMY_WIDTH + ENEMY_DEPTH * ENEMY_DEPTH) * 0.5f;
		g_enemy[nCntEnemy].fAngle = atan2f(ENEMY_WIDTH, ENEMY_DEPTH);

		//影設定
		g_enemy[nCntEnemy].nIdxShadow = SetShadow();
	}
}

//========================
//終了処理
//========================
void UninitEnemy(void)
{
	for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
	{
		//メッシュの破棄
		if (g_enemy[].aModel[nCntModel].pMesh != NULL)
		{
			g_enemy[].aModel[nCntModel].pMesh->Release();
			g_enemy[].aModel[nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_enemy[].aModel[nCntModel].pBuffMat != NULL)
		{
			g_enemy[].aModel[nCntModel].pBuffMat->Release();
			g_enemy[].aModel[nCntModel].pBuffMat = NULL;
		}
	}
}

//========================
//更新処理
//========================
void UpdateEnemy(void)
{
	//現在の位置を前回の位置にする
	g_enemy[].posOld = g_enemy[].pos;

	//カメラ向きに応じてプレイヤーの向き旋回
	if (GetMouseClickPress(MOUSE_CLICK_LEFT) == true)
	{
		g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + 1.0f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
	}

	//モデル移動
	if (GetKeyboardPress(DIK_W) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_WD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		}
		else
		{
			g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_W + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{
		if (GetKeyboardPress(DIK_A) == true)
		{
			g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SA + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		}
		else if (GetKeyboardPress(DIK_D) == true)
		{
			g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_SD + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		}
		else
		{
			g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_S + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
			g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		}
	}
	else if (GetKeyboardPress(DIK_A) == true)
	{
		g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_A + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
		g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_enemy[].rot.y = -(float)fmod(GetCamera()->rot.y + ROT_D + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
		g_enemy[].move.x = sinf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
		g_enemy[].move.z = cosf((float)fmod((g_enemy[].rot.y + D3DX_PI) + (D3DX_PI + (D3DX_PI * 2)), D3DX_PI * 2) - D3DX_PI) * ENEMY_MOVE_SPEED;
	}

	//ボタン操作に応じてプレイヤー・カメラ視点・注視点移動
	g_enemy[].pos.x += g_enemy[].move.x;
	g_enemy[].pos.z += g_enemy[].move.z;

	//壁当たり判定
	//CollisionWallEnemy(0);

	//オブジェクト当たり判定
	CollisionObjEnemy();

	GetCamera()->posV.x += g_enemy[].pos.x - g_enemy[].posOld.x;
	GetCamera()->posV.z += g_enemy[].pos.z - g_enemy[].posOld.z;
	GetCamera()->posR.x += g_enemy[].pos.x - g_enemy[].posOld.x;
	GetCamera()->posR.z += g_enemy[].pos.z - g_enemy[].posOld.z;

	//移動量減衰
	g_enemy[].move.x += (0 - g_enemy[].move.x) * DUMP_COEF;
	g_enemy[].move.z += (0 - g_enemy[].move.z) * DUMP_COEF;

	if (GetMouseClickTrigger(MOUSE_CLICK_LEFT) == true)
	{
		SetBullet(g_enemy[].pos + D3DXVECTOR3(0.0f, 40.0f, 0.0f) , 5.0f, g_enemy[].rot.y, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//影位置設定
	SetPositionShadow(g_nIdxShadow, g_enemy[].pos);
}

//========================
//描画処理
//========================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//"プレイヤーの"ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_enemy[].mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_enemy[].rot.y, g_enemy[].rot.x, g_enemy[].rot.z);
	D3DXMatrixMultiply(&g_enemy[].mtxWorld, &g_enemy[].mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_enemy[].pos.x, g_enemy[].pos.y, g_enemy[].pos.z);
	D3DXMatrixMultiply(&g_enemy[].mtxWorld, &g_enemy[].mtxWorld, &mtxTrans);

	//"プレイヤーの"ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_enemy[].mtxWorld);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
	{
		D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用
		D3DXMATRIX mtxParent;					//親のマトリ

		//"モデルの"ワールドマトリックス初期化
		D3DXMatrixIdentity(&g_enemy[].aModel[nCntModel].mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_enemy[].aModel[nCntModel].rot.y, g_enemy[].aModel[nCntModel].rot.x, g_enemy[].aModel[nCntModel].rot.z);
		D3DXMatrixMultiply(&g_enemy[].aModel[nCntModel].mtxWorld, &g_enemy[].aModel[nCntModel].mtxWorld, &mtxRotModel);

		//位置反映
		D3DXMatrixTranslation(&mtxTransModel, g_enemy[].aModel[nCntModel].pos.x, g_enemy[].aModel[nCntModel].pos.y, g_enemy[].aModel[nCntModel].pos.z);
		D3DXMatrixMultiply(&g_enemy[].aModel[nCntModel].mtxWorld, &g_enemy[].aModel[nCntModel].mtxWorld, &mtxTransModel);

		//パーツの親マトリ設定
		if (g_enemy[].aModel[nCntModel].nIdxModelParent != -1)
		{
			mtxParent = g_enemy[].aModel[g_enemy[].aModel[nCntModel].nIdxModelParent].mtxWorld;
		}
		else
		{
			mtxParent = g_enemy[].mtxWorld;
		}

		//パーツのマトリと親マトリをかけ合わせる
		D3DXMatrixMultiply(&g_enemy[].aModel[nCntModel].mtxWorld, &g_enemy[].aModel[nCntModel].mtxWorld, &mtxParent);

		//"プレイヤーの"ワールドマトリックス設定
		pDevice->SetTransform(D3DTS_WORLD, &g_enemy[].aModel[nCntModel].mtxWorld);

		//マテリアルデータへのポインタ取得
		pMat = (D3DXMATERIAL*)g_enemy[].aModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_enemy[].aModel[nCntModel].dwNumMatModel; nCntMat++)
		{
			//マテリアル設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャ設定
			pDevice->SetTexture(0, g_enemy[].aModel[nCntModel].apTexture[nCntMat]);

			//モデル描画
			g_enemy[].aModel[nCntModel].pMesh->DrawSubset(nCntMat);
		}
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//壁当たり判定処理
//========================
void CollisionWallEnemy(int nNumber)
{
	if (g_enemy[].pos.x + ENEMY_WIDTH / 2 > WALL_WIDTH / 2)
	{
		g_enemy[].pos.x = WALL_WIDTH / 2 - ENEMY_WIDTH / 2;
	}
	else if (g_enemy[].pos.x - ENEMY_WIDTH / 2 < -WALL_WIDTH / 2)
	{
		g_enemy[].pos.x = -WALL_WIDTH / 2 + ENEMY_WIDTH / 2;
	}

	if (g_enemy[].pos.z + ENEMY_DEPTH / 2 > WALL_DEPTH / 2)
	{
		g_enemy[].pos.z = WALL_DEPTH / 2 - ENEMY_DEPTH / 2;
	}
	else if (g_enemy[].pos.z - ENEMY_DEPTH / 2 < -WALL_DEPTH / 2)
	{
		g_enemy[].pos.z = -WALL_DEPTH / 2 + ENEMY_DEPTH / 2;
	}
}

//========================
//オブジェクト当たり判定処理
//========================
void CollisionObjEnemy(void)
{
	Object *obj = GetObj();
	BluePrint *pBPrint = GetBluePrint();

	for (int nCntObj = 0; nCntObj < MAX_BLUEPRINT; nCntObj++, obj++)
	{
		if (obj->bUse == true)
		{
			if (g_enemy[].pos.z >= obj->pos.z + pBPrint->vtxMin.z && g_enemy[].pos.z <= obj->pos.z + pBPrint->vtxMax.z)
			{
				if (g_enemy[].posOld.x <= obj->pos.x + pBPrint->vtxMin.x && g_enemy[].pos.x > obj->pos.x + pBPrint->vtxMin.x)
				{
					g_enemy[].pos.x = obj->pos.x + pBPrint->vtxMin.x;
				}
				if (g_enemy[].posOld.x >= obj->pos.x + pBPrint->vtxMax.x && g_enemy[].pos.x < obj->pos.x + pBPrint->vtxMax.x)
				{
					g_enemy[].pos.x = obj->pos.x + pBPrint->vtxMax.x;
				}
			}

			if (g_enemy[].pos.x >= obj->pos.x + pBPrint->vtxMin.x && g_enemy[].pos.x <= obj->pos.x + pBPrint->vtxMax.x)
			{
				if (g_enemy[].posOld.z <= obj->pos.z + pBPrint->vtxMin.z && g_enemy[].pos.z > obj->pos.z + pBPrint->vtxMin.z)
				{
					g_enemy[].pos.z = obj->pos.z + pBPrint->vtxMin.z;
				}
				if (g_enemy[].posOld.z >= obj->pos.z + pBPrint->vtxMax.z && g_enemy[].pos.z < obj->pos.z + pBPrint->vtxMax.z)
				{
					g_enemy[].pos.z = obj->pos.z + pBPrint->vtxMax.z;
				}
			}
		}
	}
}

//========================
//取得処理
//========================
Enemy *GetEnemy(void)
{
	return &g_enemy[];
}
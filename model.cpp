//==========================================
//
//モデル関係プログラム[model.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "model.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//マクロ
#define MODEL_MOVE_SPEED	(1.0f)	//モデル移動速度

//グローバル変数
Model g_aModel[MODELNAME_MAX][EXITHUMAN_MODEL_NUM];	//モデル構造体

//ファイルパス
const char *c_pFileNameModel[] =
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
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	for (int nCntInitModel = 0; nCntInitModel < MODELNAME_MAX; nCntInitModel++)
	{
		for (int nCntInitParts = 0; nCntInitParts < EXITHUMAN_MODEL_NUM; nCntInitParts++)
		{
			g_aModel[nCntInitModel][nCntInitParts] = {};
		}
	}

	//Xファイル読み込み
	for (int nCntParts = 0; nCntParts < EXITHUMAN_MODEL_NUM; nCntParts++)
	{
		D3DXLoadMeshFromX(
			c_pFileNameModel[nCntParts],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aModel[0][nCntParts].pBuffMat,
			NULL,
			&g_aModel[0][nCntParts].dwNumMatModel,
			&g_aModel[0][nCntParts].pMesh);

		//テクスチャ読み込み
		D3DXMATERIAL *pMat;	//マテリアルポインタ

		//マテリアル情報に対するポインタ取得
		pMat = (D3DXMATERIAL *)g_aModel[0][nCntParts].pBuffMat->GetBufferPointer();

		for (int nCntTex = 0; nCntTex < (int)g_aModel[0][nCntParts].dwNumMatModel; nCntTex++)
		{
			if (pMat[nCntTex].pTextureFilename != NULL)
			{
				//テクスチャ読み込み
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntTex].pTextureFilename,
					&g_aModel[0][nCntParts].apTexture[nCntTex]);
			}
		}
	}

	//階層構造設定
	//体
	g_aModel[0][0].nIdxModelParent = -1;
	g_aModel[0][0].pos = D3DXVECTOR3(0.0f, 35.0f, 0.0f);
	g_aModel[0][0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//頭
	g_aModel[0][1].nIdxModelParent = 0;
	g_aModel[0][1].pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_aModel[0][1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左腕
	g_aModel[0][2].nIdxModelParent = 0;
	g_aModel[0][2].pos = D3DXVECTOR3(-5.0f, 7.0f, 0.0f);
	g_aModel[0][2].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左手
	g_aModel[0][3].nIdxModelParent = 2;
	g_aModel[0][3].pos = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	g_aModel[0][3].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右腕
	g_aModel[0][4].nIdxModelParent = 0;
	g_aModel[0][4].pos = D3DXVECTOR3(5.0f, 7.0f, 0.0f);
	g_aModel[0][4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右手
	g_aModel[0][5].nIdxModelParent = 4;
	g_aModel[0][5].pos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	g_aModel[0][5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左腿
	g_aModel[0][6].nIdxModelParent = 0;
	g_aModel[0][6].pos = D3DXVECTOR3(-3.0f, -8.0f, 0.0f);
	g_aModel[0][6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//左足
	g_aModel[0][7].nIdxModelParent = 6;
	g_aModel[0][7].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);
	g_aModel[0][7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右腿
	g_aModel[0][8].nIdxModelParent = 0;
	g_aModel[0][8].pos = D3DXVECTOR3(3.0f, -8.0f, 0.0f);
	g_aModel[0][8].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//右足
	g_aModel[0][9].nIdxModelParent = 8;
	g_aModel[0][9].pos = D3DXVECTOR3(0.0f, -12.0f, 0.0f);
	g_aModel[0][9].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//========================
//終了処理
//========================
void UninitModel(void)
{
	for (int nCntModel = 0; nCntModel < EXITHUMAN_MODEL_NUM; nCntModel++)
	{
		//メッシュの破棄
		if (g_aModel[0][nCntModel].pMesh != NULL)
		{
			g_aModel[0][nCntModel].pMesh->Release();
			g_aModel[0][nCntModel].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aModel[0][nCntModel].pBuffMat != NULL)
		{
			g_aModel[0][nCntModel].pBuffMat->Release();
			g_aModel[0][nCntModel].pBuffMat = NULL;
		}
	}
}

//========================
//更新処理
//========================
void UpdateModel(void)
{
	
}

//========================
//描画処理
//========================
void DrawModel(void)
{
	
}

//========================
//取得処理
//========================
Model *GetModel(MODELNAME name)
{
	return &g_aModel[name][0];
}
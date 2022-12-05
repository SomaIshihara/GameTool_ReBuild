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
LPD3DXMESH g_pMeshModel = NULL;			//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;	//マテリアルへのポインタ
DWORD g_dwNumMatModel = 0;				//マテリアル数
D3DXVECTOR3 g_posModel;					//位置
D3DXVECTOR3 g_rotModel;					//向き
D3DXMATRIX g_mtxWorldModel;				//ワールドマトリックス
LPDIRECT3DTEXTURE9 g_apTexturemodel[16] = {};	//テクスチャポインタ
//int g_nIdxShadow = -1;

//========================
//初期化処理
//========================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	g_posModel = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//g_nIdxShadow = -1;

	//Xファイル読み込み
	D3DXLoadMeshFromX(
		"data\\MODEL\\car000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	//（本来は読み込めたかチェックがいる）

	//テクスチャ読み込み
	D3DXMATERIAL *pMat;	//マテリアルポインタ

	//マテリアル情報に対するポインタ取得
	pMat = (D3DXMATERIAL *)g_pBuffMatModel->GetBufferPointer();

	for (int nCntTex = 0; nCntTex < (int)g_dwNumMatModel; nCntTex++)
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
	//g_nIdxShadow = SetShadow();
}

//========================
//終了処理
//========================
void UninitModel(void)
{
	//メッシュの破棄
	if (g_pMeshModel != NULL)
	{
		g_pMeshModel->Release();
		g_pMeshModel = NULL;
	}

	//マテリアルの破棄
	if (g_pBuffMatModel != NULL)
	{
		g_pBuffMatModel->Release();
		g_pBuffMatModel = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateModel(void)
{
	//モデル移動
	if (GetKeyboardPress(DIK_A) == true)
	{//-0.5pi[rad]
		g_posModel.x += -cosf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_posModel.z += -sinf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_rotModel.y = -(float)fmod(GetCamera()->rot.y - 0.5f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_D) == true)
	{//0.5pi[rad]
		g_posModel.x += cosf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_posModel.z += sinf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_rotModel.y = -(float)fmod(GetCamera()->rot.y + 0.5f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
	}

	if (GetKeyboardPress(DIK_W) == true)
	{//1.0pi[rad]
		g_posModel.x += -sinf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_posModel.z += cosf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_rotModel.y = -(float)fmod(GetCamera()->rot.y + 1.0f * D3DX_PI + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
	}
	else if (GetKeyboardPress(DIK_S) == true)
	{//0.0pi[rad]
		g_posModel.x += sinf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_posModel.z += -cosf(GetCamera()->rot.y) * MODEL_MOVE_SPEED;
		g_rotModel.y = -(float)fmod(GetCamera()->rot.y + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_posModel, 5.0f, g_rotModel.y, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	//影位置設定
	//SetPositionShadow(g_nIdxShadow, g_posModel);
}

//========================
//描画処理
//========================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotModel.y, g_rotModel.x, g_rotModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posModel.x, g_posModel.y, g_posModel.z);
	D3DXMatrixMultiply(&g_mtxWorldModel, &g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldModel);

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャ設定
		pDevice->SetTexture(0, g_apTexturemodel[nCntMat]);

		//モデル描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}
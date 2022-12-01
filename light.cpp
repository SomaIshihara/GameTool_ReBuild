//==========================================
//
//ライト関係プログラム[light.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "light.h"

//プロト
D3DLIGHT9 g_light;	//ライト情報

//========================
//初期化処理
//========================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXVECTOR3 vecDir;	//設定用

	//ライト情報クリア
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//ライト種類設定
	g_light.Type = D3DLIGHT_DIRECTIONAL;

	//ライト拡散光設定
	g_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向
	//vecDir = D3DXVECTOR3(0.2f, -0.8f, -0.4f);
	vecDir = D3DXVECTOR3(0.0f, -1.5f, 0.5f);
	D3DXVec3Normalize(&vecDir, &vecDir);

	g_light.Direction = vecDir;

	//ライト設定
	pDevice->SetLight(0, &g_light);

	//ライト有効化
	pDevice->LightEnable(0, TRUE);
}

//========================
//終了処理
//========================
void UninitLight(void)
{
	//無
}

//========================
//更新処理
//========================
void UpdateLight(void)
{
	//無
}
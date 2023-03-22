//==========================================
//
//ライト関係プログラム[light.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "cLight.h"

//========================
//コンストラクタ
//========================
cLight::cLight()
{
	//番号割り振り
	this->m_thisLightNum = cLight::m_allLightNum;

	//ライト個数加算
	cLight::m_allLightNum++;
}

//========================
//デストラクタ
//========================
cLight::~cLight()
{

}

//========================
//設定処理
//========================
void cLight::SetLight(D3DLIGHTTYPE type,D3DCOLORVALUE col,D3DXVECTOR3 vecDir)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//ライト情報クリア
	ZeroMemory(&this->m_light, sizeof(D3DLIGHT9));

	//ライト種類設定
	this->m_light.Type = type;

	//ライト拡散光設定
	this->m_light.Diffuse = col;

	//ライトの方向
	D3DXVec3Normalize(&vecDir, &vecDir);

	this->m_light.Direction = vecDir;

	//ライト設定
	pDevice->SetLight(this->m_thisLightNum, &this->m_light);

	//ライト有効化
	pDevice->LightEnable(this->m_thisLightNum, TRUE);
}

//========================
//有効・無効化処理
//========================
void cLight::EnableLight(bool bEnable)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	
	//ライト有効・無効化
	pDevice->LightEnable(0, bEnable ? TRUE : FALSE);
}
//==========================================
//
//モデル関係プログラム[cModel.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "cModel.h"

cModel::cModel()
{
	this->m_cModelStr = {};
}

cModel::~cModel()
{
	//メッシュの破棄
	if (this->m_cModelStr.pMesh != NULL)
	{
		this->m_cModelStr.pMesh->Release();
		this->m_cModelStr.pMesh = NULL;
	}

	//マテリアルの破棄
	if (this->m_cModelStr.pBuffMat != NULL)
	{	
		this->m_cModelStr.pBuffMat->Release();
		this->m_cModelStr.pBuffMat = NULL;
	}
}

void cModel::LoadModel(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&this->m_cModelStr.pBuffMat,
		NULL,
		&this->m_cModelStr.dwNumMatModel,
		&this->m_cModelStr.pMesh);

	//テクスチャ読み込み
	D3DXMATERIAL* pMat;	//マテリアルポインタ

	//マテリアル情報に対するポインタ取得
	pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

	for (int nCntTex = 0; nCntTex < (int)this->m_cModelStr.dwNumMatModel; nCntTex++)
	{
		if (pMat[nCntTex].pTextureFilename != NULL)
		{
			//テクスチャ読み込み
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntTex].pTextureFilename,
				&this->m_cModelStr.apTexture[nCntTex]);
		}
	}
}

void cModel::SetModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//モデル取得
	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&this->m_cModelStr.mtxWorld);

	//オフセットを足す
	//pos = this->m_cModelStr.posOffset;
	//rot = this->m_cModelStr.rotOffset;

	//拡縮を反映
	//D3DXMatrixScaling(&mtxScall, FENCE_SCALE, FENCE_SCALE, FENCE_SCALE);
	//D3DXMatrixMultiply(&g_aFence[nCount].mtxWorld, &g_aFence[nCount].mtxWorld, &mtxScall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &this->m_cModelStr.mtxWorld);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)this->m_cModelStr.dwNumMatModel; nCntMat++)
	{
		//マテリアル設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャ設定
		pDevice->SetTexture(0, this->m_cModelStr.apTexture[nCntMat]);

		//モデル描画
		this->m_cModelStr.pMesh->DrawSubset(nCntMat);
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

cModelStruct cModel::GetModel(void)
{
	return this->m_cModelStr;
}
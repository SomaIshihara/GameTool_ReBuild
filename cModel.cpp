//==========================================
//
//モデル関係プログラム[cModel.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
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

cModelStruct cModel::GetModel(void)
{
	return this->m_cModelStr;
}
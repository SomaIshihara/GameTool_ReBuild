//==========================================
//
//モデル関係プログラム[cModel.cpp]
//Author:石原颯馬
//
//==========================================
#include "Model.h"

//*******************************************************************
//単体モデル
//*******************************************************************
//==========================================
//コンストラクタ
//==========================================
CModel::CModel()
{
	this->m_cModelStr = {};
}

//==========================================
//デストラクタ
//==========================================
CModel::~CModel()
{

}

//==========================================
//初期化処理
//==========================================
void CModel::Init(void)
{
	this->m_cModelStr = {};
}

//==========================================
//終了処理
//==========================================
void CModel::Uninit(void)
{

}

//==========================================
//生成処理
//==========================================
void CModel::Create(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	if (SUCCEEDED(D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&this->m_cModelStr.pBuffMat,
		NULL,
		&this->m_cModelStr.dwNumMatModel,
		&this->m_cModelStr.pMesh)))
	{
		//テクスチャ読み込み
		D3DXMATERIAL* pMat;	//マテリアルポインタ

		//マテリアル情報に対するポインタ取得
		pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

		//テクスチャ読み込み
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

		//使用している状態にする
		this->m_cModelStr.m_bUse = true;
	}
	else
	{
		//使用していない
		this->m_cModelStr.m_bUse = false;
	}
}

//==========================================
//破棄処理
//==========================================
void CModel::Release(void)
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

//==========================================
//描画処理
//==========================================
void CModel::DrawModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXMATRIX *pMtxBace, D3DXMATRIX *mtxParent = NULL)
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

	//拡縮を反映
	//D3DXMatrixScaling(&mtxScall, FENCE_SCALE, FENCE_SCALE, FENCE_SCALE);
	//D3DXMatrixMultiply(&g_aFence[nCount].mtxWorld, &g_aFence[nCount].mtxWorld, &mtxScall);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxTrans);

	//パーツの親マトリ設定
	if (mtxParent != NULL)
	{
		//パーツのマトリと親マトリをかけ合わせる
		D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, mtxParent);
	}
	else
	{
		//パーツのマトリとベースマトリをかけ合わせる
		D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, pMtxBace);
	}

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

//*******************************************************************
//モーション付きモデル
//*******************************************************************
//==========================================
//コンストラクタ
//==========================================
cMotionModel::cMotionModel()
{
	
}

//==========================================
//デストラクタ
//==========================================
cMotionModel::~cMotionModel()
{

}

//==========================================
//初期化処理
//==========================================
void cMotionModel::Init(void)
{
	
}

//==========================================
//終了処理
//==========================================
void cMotionModel::Uninit(void)
{

}
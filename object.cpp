//==========================================
//
//モデル関係プログラム[object.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "object.h"
#include "input.h"
#include "shadow.h"
#include "camera.h"
#include "bullet.h"

//マクロ
#define MODEL_MOVE_SPEED	(1.0f)	//モデル移動速度

//グローバル変数
Object g_aObject[MAX_OBJECT];

//ファイルパス
const char* c_apFilePathObject[] =
{
	"data\\MODEL\\obj_branco_01.x",
	"data\\MODEL\\takibi001.x"
};

//========================
//初期化処理
//========================
void InitObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATERIAL *pMat;	//マテリアルポインタ
	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファポインタ

	//変数初期化
	for (int nCntModel = 0; nCntModel < MAX_OBJECT && nCntModel < (sizeof c_apFilePathObject / sizeof(char *)); nCntModel++)
	{
		g_aObject[nCntModel].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aObject[nCntModel].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//Xファイル読み込み		
		if (SUCCEEDED(D3DXLoadMeshFromX(
			c_apFilePathObject[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&g_aObject[nCntModel].pBuffMat,
			NULL,
			&g_aObject[nCntModel].dwNumMat,
			&g_aObject[nCntModel].pMesh)))
		{
			//頂点数を取得
			nNumVtx = g_aObject[nCntModel].pMesh->GetNumVertices();

			//頂点フォーマット
			dwSizeFVF = D3DXGetFVFVertexSize(g_aObject[nCntModel].pMesh->GetFVF());

			//頂点バッファロック
			g_aObject[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void **)&pVtxBuff);

			//最初だけ全部入れる
			D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

			g_aObject[nCntModel].vtxMax = vtx;
			g_aObject[nCntModel].vtxMin = vtx;

			pVtxBuff += dwSizeFVF;

			for (int nCntVtx = 1; nCntVtx < nNumVtx; nCntVtx++, pVtxBuff += dwSizeFVF)
			{
				D3DXVECTOR3 vtx = *(D3DXVECTOR3 *)pVtxBuff;

				if (g_aObject[nCntModel].vtxMax.x < vtx.x)
				{
					g_aObject[nCntModel].vtxMax.x = vtx.x;
				}
				if (g_aObject[nCntModel].vtxMax.z < vtx.z)
				{
					g_aObject[nCntModel].vtxMax.z = vtx.z;
				}
				if (g_aObject[nCntModel].vtxMin.x > vtx.x)
				{
					g_aObject[nCntModel].vtxMin.x = vtx.x;
				}
				if (g_aObject[nCntModel].vtxMin.z > vtx.z)
				{
					g_aObject[nCntModel].vtxMin.z = vtx.z;
				}
			}

			//頂点バッファアンロック
			g_aObject[nCntModel].pMesh->UnlockVertexBuffer();

			//テクスチャ読み込み
			//マテリアル情報に対するポインタ取得
			pMat = (D3DXMATERIAL *)g_aObject[nCntModel].pBuffMat->GetBufferPointer();

			for (int nCntTex = 0; nCntTex < (int)g_aObject[nCntModel].dwNumMat; nCntTex++)
			{
				if (pMat[nCntTex].pTextureFilename != NULL)
				{
					//テクスチャ読み込み
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntTex].pTextureFilename,
						&g_aObject[nCntModel].apTexture[nCntTex]);
				}
			}

			//影設定
			g_aObject[nCntModel].nIdxShadow = SetShadow();

			//表示
			g_aObject[nCntModel].bUse = true;
		}
		else
		{
			//非表示
			g_aObject[nCntModel].bUse = false;
		}
	}
	g_aObject[0].pos = D3DXVECTOR3(100.0f, 7.0f, 100.0f);
	g_aObject[1].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
}

//========================
//終了処理
//========================
void UninitObject(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//メッシュの破棄
		if (g_aObject[nCount].pMesh != NULL)
		{
			g_aObject[nCount].pMesh->Release();
			g_aObject[nCount].pMesh = NULL;
		}

		//マテリアルの破棄
		if (g_aObject[nCount].pBuffMat != NULL)
		{
			g_aObject[nCount].pBuffMat->Release();
			g_aObject[nCount].pBuffMat = NULL;
		}
	}
}

//========================
//更新処理
//========================
void UpdateObject(void)
{
	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		//影位置設定
		SetPositionShadow(g_aObject[nCount].nIdxShadow, g_aObject[nCount].pos);
	}
}

//========================
//描画処理
//========================
void DrawObject(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
	{
		if (g_aObject[nCount].bUse == true)
		{
			//ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aObject[nCount].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aObject[nCount].rot.y, g_aObject[nCount].rot.x, g_aObject[nCount].rot.z);
			D3DXMatrixMultiply(&g_aObject[nCount].mtxWorld, &g_aObject[nCount].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aObject[nCount].pos.x, g_aObject[nCount].pos.y, g_aObject[nCount].pos.z);
			D3DXMatrixMultiply(&g_aObject[nCount].mtxWorld, &g_aObject[nCount].mtxWorld, &mtxTrans);

			//ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aObject[nCount].mtxWorld);

			//マテリアルデータへのポインタ取得
			pMat = (D3DXMATERIAL*)g_aObject[nCount].pBuffMat->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_aObject[nCount].dwNumMat; nCntMat++)
			{
				//マテリアル設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				//テクスチャ設定
				pDevice->SetTexture(0, g_aObject[nCount].apTexture[nCntMat]);

				//モデル描画
				g_aObject[nCount].pMesh->DrawSubset(nCntMat);
			}
		}
	}
	
	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//========================
//取得処理
//========================
Object *GetObj(void)
{
	return &g_aObject[0];
}
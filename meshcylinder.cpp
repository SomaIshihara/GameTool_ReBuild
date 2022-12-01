//==========================================
//
//メッシュ筒プログラム[meshcylinder.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "meshcylinder.h"
#include "input.h"

//マクロ
#define MESHCYLINDER_UDIVISION	(8)			//縦の分割数
#define MESHCYLINDER_VDIVISION	(2)			//横の分割数
#define MESHCYLINDER_HEIGHT		(40.0f)		//高さ
#define MESHCILINDER_RADIUS		(50.0f)		//半径
#define MESHCYLINDER_IDXNUM		((MESHCYLINDER_UDIVISION + 1) * 2)
#define MESHCYLINDER_POLYNUM	(MESHCYLINDER_IDXNUM - 2)
#define MESHCYLINDER_NORVECTER	(1)		//法線の向き（1で表・-1で裏）

//プロト
WORD *SetIdxSwaingCylinder(int nCntWidth, WORD *pIdx);

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxbuffMeshCylinder;	//頂点バッファポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder;		//テクスチャポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;	//インデックスバッファ
D3DXVECTOR3 g_posMeshCylinder;					//位置
D3DXVECTOR3 g_rotMeshCylinder;					//向き
D3DXMATRIX g_mtxWorldMeshCylinder;				//ワールドマトリックス
D3DCULL g_cullMode = D3DCULL_CCW;				//カリングモード

//========================
//初期化処理
//========================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data\\TEXTURE\\field000.jpg",
		&g_pTextureMeshCylinder);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 18,	//18仮
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxbuffMeshCylinder,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * MESHCYLINDER_IDXNUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	//変数初期化
	g_posMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotMeshCylinder = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_cullMode = D3DCULL_CCW;

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	g_pVtxbuffMeshCylinder->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCntHeight = 0; nCntHeight < MESHCYLINDER_VDIVISION + 1; nCntHeight++)
	{
		for (int nCntDivision = 0; nCntDivision < MESHCYLINDER_UDIVISION + 1; nCntDivision++, pVtx++)
		{
			//計算用
			float fAngle = fmodf(((float)nCntDivision / (MESHCYLINDER_UDIVISION / 2) * D3DX_PI) + D3DX_PI + (D3DX_PI * 2), D3DX_PI * 2) - D3DX_PI;
			D3DXVECTOR3 nor;

			//頂点座標（相対座標）
			pVtx->pos = D3DXVECTOR3(sinf(fAngle) * MESHCILINDER_RADIUS, (MESHCYLINDER_HEIGHT / MESHCYLINDER_VDIVISION) * (MESHCYLINDER_VDIVISION - nCntHeight), -cosf(fAngle) * MESHCILINDER_RADIUS);

			//法線ベクトル
			nor = pVtx->pos;	//頂点位置代入
			nor.y = 0.0f;		//yはいらないので0
			nor.x *= MESHCYLINDER_NORVECTER;
			nor.z *= MESHCYLINDER_NORVECTER;	//xzは表裏指定
			D3DXVec3Normalize(&nor, &nor);		//正規化
			pVtx->nor = nor;					//頂点情報に代入

			//カラー
			pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ座標
			pVtx->tex = D3DXVECTOR2((float)(nCntDivision % (MESHCYLINDER_UDIVISION + 1)), (float)(nCntHeight / MESHCYLINDER_VDIVISION));
		}
	}

	//頂点バッファをアンロック
	g_pVtxbuffMeshCylinder->Unlock();

	//インデックスバッファ設定
	WORD *pIdx;	//インデックス情報へのポインタ
	int nCntWidth = 0;	//インデックスカウンタ

	//バッファロック
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void **)&pIdx, 0);

	for (nCntWidth = 0; nCntWidth < MESHCYLINDER_VDIVISION - 1; nCntWidth++)
	{
		//グネグネパート
		pIdx = SetIdxSwaingCylinder(nCntWidth, pIdx);
		
		//チョン打ちするパート
		//最後のインデックス情報を次のにも入れる
		*pIdx = MESHCYLINDER_VDIVISION + (MESHCYLINDER_VDIVISION + 1) * nCntWidth;
		pIdx++;

		//その次のに次のループで最初に入る数字を入れる
		*pIdx = (MESHCYLINDER_VDIVISION + 1) + (MESHCYLINDER_VDIVISION + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//最後のグネグネパート
	SetIdxSwaingCylinder(nCntWidth, pIdx);
	
	//バッファアンロック
	g_pIdxBuffMeshCylinder->Unlock();
}

//========================
//終了処理
//========================
void UninitMeshCylinder(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxbuffMeshCylinder != NULL)
	{
		g_pVtxbuffMeshCylinder->Release();
		g_pVtxbuffMeshCylinder = NULL;
	}

	//インデックスバッファ破棄
	if (g_pIdxBuffMeshCylinder != NULL)
	{
		g_pIdxBuffMeshCylinder->Release();
		g_pIdxBuffMeshCylinder = NULL;
	}
}

//========================
//更新処理
//========================
void UpdateMeshCylinder(void)
{
	//無
}

//========================
//描画処理
//========================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//カリング設定
	pDevice->SetRenderState(D3DRS_CULLMODE, g_cullMode);

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&g_mtxWorldMeshCylinder);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotMeshCylinder.y, g_rotMeshCylinder.x, g_rotMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, g_posMeshCylinder.x, g_posMeshCylinder.y, g_posMeshCylinder.z);
	D3DXMatrixMultiply(&g_mtxWorldMeshCylinder, &g_mtxWorldMeshCylinder, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldMeshCylinder);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxbuffMeshCylinder, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshCylinder);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureMeshCylinder);

	//ポリゴン描画（インデックスされたやつ）
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (MESHCYLINDER_UDIVISION + 1) * (MESHCYLINDER_VDIVISION + 1), 0, MESHCYLINDER_POLYNUM);

	//カリング戻す
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//========================
//グネグネインデックス設定処理
//========================
WORD *SetIdxSwaingCylinder(int nCntWidth, WORD *pIdx)
{
	//グネグネパート
	for (int nCountHeight = 0; nCountHeight < (MESHCYLINDER_UDIVISION + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (MESHCYLINDER_UDIVISION + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (MESHCYLINDER_VDIVISION + 1) * nCntWidth;
	}
	return pIdx;
}
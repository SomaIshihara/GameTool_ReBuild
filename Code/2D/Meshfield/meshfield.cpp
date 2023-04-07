//==========================================
//
//ポリゴン関係プログラム[meshfield.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "meshfield.h"

//プロト
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx, int width);

//========================
//初期化処理
//========================
cMeshfield::cMeshfield()
{
	//変数初期化
	this->m_meshData.m_pos = INIT_ZERO;
	this->m_meshData.m_rot = INIT_ZERO;
}

//========================
//終了処理
//========================
cMeshfield::~cMeshfield()
{
	//テクスチャの破棄
	if (this->m_meshData.m_pTexture != (LPDIRECT3DTEXTURE9)0xcccccccc)
	{
		this->m_meshData.m_pTexture->Release();
		this->m_meshData.m_pTexture = NULL;
	}

	//頂点バッファの破棄
	if (this->m_meshData.m_pVtxbuff != (LPDIRECT3DVERTEXBUFFER9)0xcccccccc)
	{
		this->m_meshData.m_pVtxbuff->Release();
		this->m_meshData.m_pVtxbuff = NULL;
	}

	//インデックスバッファ破棄
	if (this->m_meshData.m_pIdxBuff != NULL)
	{
		this->m_meshData.m_pIdxBuff->Release();
		this->m_meshData.m_pIdxBuff = NULL;
	}
}

//========================
//更新処理
//========================
void cMeshfield::Update(void)
{
	//無
}

//========================
//描画処理
//========================
void cMeshfield::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&this->m_meshData.m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->m_meshData.m_rot.y, this->m_meshData.m_rot.x, this->m_meshData.m_rot.z);
	D3DXMatrixMultiply(&this->m_meshData.m_mtxWorld, &this->m_meshData.m_mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, this->m_meshData.m_pos.x, this->m_meshData.m_pos.y, this->m_meshData.m_pos.z);
	D3DXMatrixMultiply(&this->m_meshData.m_mtxWorld, &this->m_meshData.m_mtxWorld, &mtxTrans);

	//ワールドマトリックス設定
	pDevice->SetTransform(D3DTS_WORLD, &this->m_meshData.m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, this->m_meshData.m_pVtxbuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデータストリームに設定
	pDevice->SetIndices(this->m_meshData.m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャ設定
	if (this->m_meshData.m_pTexture != (LPDIRECT3DTEXTURE9)0xcccccccc)
	{
		pDevice->SetTexture(0, this->m_meshData.m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	//ポリゴン描画（インデックスされたやつ）
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, (this->m_meshData.m_width + 1) * (this->m_meshData.m_height + 1), 0, 
		((((this->m_meshData.m_width + 1) * this->m_meshData.m_height * 2) + (2 * (this->m_meshData.m_height - 1))) - 2));
}

//========================
//メッシュフィールド配置処理
//========================
void cMeshfield::SetMeshfield(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pPath, int width, int height,float length)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数設定
	this->m_meshData.m_pos = pos;
	this->m_meshData.m_rot = rot;
	this->m_meshData.m_width = width;
	this->m_meshData.m_height = height;
	this->m_meshData.m_length = length;

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice,
		pPath,
		&this->m_meshData.m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * (this->m_meshData.m_width + 1) * (this->m_meshData.m_height + 1),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&this->m_meshData.m_pVtxbuff,
		NULL);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * (((this->m_meshData.m_width + 1) * this->m_meshData.m_height * 2) + (2 * (this->m_meshData.m_height - 1))),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&this->m_meshData.m_pIdxBuff,
		NULL);

	VERTEX_3D *pVtx;

	//バッファロック
	//頂点バッファのロックと頂点情報へのポインタを取得
	this->m_meshData.m_pVtxbuff->Lock(0, 0, (void **)&pVtx, 0);

	//頂点座標+テクスチャ座標
	for (int nCount = 0; nCount < (this->m_meshData.m_height + 1) * (this->m_meshData.m_height + 1); nCount++, pVtx++)
	{
		//頂点座標（相対座標）
		pVtx->pos = D3DXVECTOR3(this->m_meshData.m_length * (nCount % (this->m_meshData.m_height + 1)), 0.0f, -this->m_meshData.m_length * (nCount / (this->m_meshData.m_height + 1)));

		//法線ベクトル
		pVtx->nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//カラー
		pVtx->col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx->tex = D3DXVECTOR2(((float)(nCount % (this->m_meshData.m_height + 1)) / (this->m_meshData.m_height)), ((float)(nCount / (this->m_meshData.m_height + 1)) / (this->m_meshData.m_height)));
	}

	//頂点バッファをアンロック
	this->m_meshData.m_pVtxbuff->Unlock();

	//インデックスバッファ設定
	WORD *pIdx;	//インデックス情報へのポインタ
	int nCntWidth = 0;	//インデックスカウンタ

	//バッファロック
	this->m_meshData.m_pIdxBuff->Lock(0, 0, (void **)&pIdx, 0);

	for (; nCntWidth < this->m_meshData.m_height - 1; nCntWidth++)
	{
		//グネグネパート
		pIdx = SetIdxSwaingField(nCntWidth, pIdx, this->m_meshData.m_height);

		//チョン打ちするパート
		//最後のインデックス情報を次のにも入れる
		*pIdx = this->m_meshData.m_height + (this->m_meshData.m_height + 1) * nCntWidth;
		pIdx++;

		//その次のに次のループで最初に入る数字を入れる
		*pIdx = (this->m_meshData.m_height + 1) + (this->m_meshData.m_height + 1) * (nCntWidth + 1);
		pIdx++;
	}

	//最後のグネグネパート
	SetIdxSwaingField(nCntWidth, pIdx, this->m_meshData.m_height);

	//バッファアンロック
	this->m_meshData.m_pIdxBuff->Unlock();
}

//========================
//グネグネインデックス設定処理
//========================
WORD *SetIdxSwaingField(int nCntWidth, WORD *pIdx,int width)
{
	//グネグネパート
	for (int nCountHeight = 0; nCountHeight < (width + 1) * 2; nCountHeight++, pIdx++)
	{
		*pIdx = (width + 1) * ((nCountHeight % 2) ^ 0x1) + nCountHeight / 2 + (width + 1) * nCntWidth;
	}
	return pIdx;
}
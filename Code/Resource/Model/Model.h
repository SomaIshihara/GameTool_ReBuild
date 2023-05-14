//==========================================
//
//モデルプログラムのヘッダ[cModel.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_MODEL_H_
#define _CLASS_MODEL_H_

#include "..\..\Core\Main\main.h"

//========================
//モデル単体
//========================
class CModel
{
public:
	struct ModelStruct
	{
		//描画関係
		LPD3DXMESH pMesh = NULL;				//メッシュ
		LPD3DXBUFFER pBuffMat = NULL;			//マテリアルポインタ
		DWORD dwNumMatModel = 0;				//マテ数
		LPDIRECT3DTEXTURE9 apTexture[16] = {};	//テクスチャポインタ
		D3DXMATRIX mtxWorld;					//ワールドマトリ

		//変更可能
		D3DXVECTOR3 posOffset = INIT_ZERO;	//位置（オフセット）
		D3DXVECTOR3 rotOffset = INIT_ZERO;	//向き（オフセット）
		int m_IdxModelParent = -1;			//親モデルインデックス

		//使用有無
		bool m_bUse = false;				//使用の有無
	};

	CModel();
	~CModel();
	virtual void Init(void);
	virtual void Uninit(void);

	virtual void Create(const char* pPath);
	virtual void Release(void);

	void DrawModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXMATRIX *pMtxBace, D3DXMATRIX *mtxParent = NULL);
	void SetModelSetup(ModelStruct modelstr);
private:
	ModelStruct m_cModelStr;
};

//========================
//モーション付きモデル
//========================
class cMotionModel : public CModel
{
public:
	//モーションの種類
	typedef enum
	{
		MOTIONTYPE_HOGE = 0,	//ほげ
		MOTIONTYPE_HUGA,		//ふが
		MOTIONTYPE_PIYO,		//ぴよ
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	//キー構造体
	typedef struct
	{
		float m_PosX;	//位置X
		float m_PosY;	//位置Y
		float m_PosZ;	//位置Z
		float m_RotX;	//向きX
		float m_RotY;	//向きY
		float m_RotZ;	//向きZ
	} KEY;

	//キー情報の構造体
	typedef struct
	{
		int m_Frame;				//再生フレーム
		KEY *m_aKey;				//モデルのキー要素（パーツ数と同じ数動的確保）
	} KEY_INFO;

	//モーション状態構造体
	typedef struct
	{
		bool m_Loop;				//ループするか
		int m_numKey;				//キー総数
		KEY_INFO *m_aKeyInfo;		//キーの情報（キー総数と同じ数動的確保）
	} MOTION_INFO;

	//モーション構造体
	typedef struct
	{
		MOTIONTYPE m_motionType;	//モーション種類
		int m_nowKey;				//現在のキーNo.
		int m_counterMotion;		//モーションカウンター
	} Motion;



	cMotionModel();
	~cMotionModel();

	void Init(void);
	void Uninit(void);

	void Create(const char* pPath);
	void Release(void);

	void UpdateMotion(void);
	void SetMotion(MOTIONTYPE type);

	void SetParent(D3DXMATRIX mtx);
	void DrawMotionModel(D3DXMATRIX *mtxBace);
private:
	CModel *m_model;
	Motion m_motion;
	MOTION_INFO m_motionInfo[MOTIONTYPE_MAX];
	D3DXVECTOR3 *m_motionPos;
	D3DXVECTOR3 *m_motionRot;
	float m_move;	//移動量
	float m_jump;	//ジャンプ量
	float m_radius;	//半径（未使用）
	int m_numParts;	//パーツ数

	//モデル数
	int m_numModel;
};

#endif
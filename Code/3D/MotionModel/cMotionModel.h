//==========================================
//
//動かせるモデルプログラムのヘッダ[cMotionModel.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MOTION_MODEL_H_
#define _MOTION_MODEL_H_

#include "../../Core/Main/main.h"
#include "../../Resource/Model/cModel.h"

#define MAX_MOTION_MODEL	(10)	//動くモデルに使える

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
	int m_Frame;					//再生フレーム
	KEY m_aKey[MAX_MOTION_MODEL];	//モデルのキー要素
} KEY_INFO;

//モーション状態構造体
typedef struct
{
	bool m_Loop;				//ループするか
	int m_numKey;				//キー総数
	KEY_INFO m_aKeyInfo[16];	//キーの情報（16は適宜変えて）
} MOTION_INFO;

//モーション構造体
typedef struct
{
	MOTIONTYPE m_motionType;	//モーション種類
	int m_nowKey;				//現在のキーNo.
	int m_counterMotion;		//モーションカウンター
} Motion;

//動くモデル
class cMotionModel
{
public:
	cMotionModel();
	virtual ~cMotionModel();
	void LoadMotionModel(const char* pPath);
	void DrawMotionModel(D3DXMATRIX *mtxBace);
private:
	Motion m_motion;
	MOTION_INFO m_motionInfo[MOTIONTYPE_MAX];
	cModel m_model[MAX_MOTION_MODEL];
	float m_move;	//移動量
	float m_jump;	//ジャンプ量
	float m_radius;	//半径（未使用）
	int m_numParts;	//パーツ数
};

#endif // !_MOTION_MODEL_H_
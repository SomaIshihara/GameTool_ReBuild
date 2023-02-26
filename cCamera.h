//==========================================
//
//カメラプログラムのヘッダ[cCamera.h]
//Author:石原颯馬
//
//==========================================
#ifndef _CLASS_CAMERA_H_
#define _CLASS_CAMERA_H_

#include "main.h"

//カメラ構造体
typedef struct
{
	D3DXVECTOR3 posV;			//視点
	D3DXVECTOR3 posR;			//注視点
	D3DXVECTOR3 vecU;			//上方向ベクトル
	D3DXVECTOR3 rot;			//向き
	float fLength;				//距離
	D3DXMATRIX mtxProjection;	//プロジェクションマトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス
} Camera;

class cCamera
{
public:
	//コンストラクタ・デストラクタ
	cCamera();
	~cCamera();

	//移動
	void MoveCamera(float moveX, float moveY);
	void ResetCamera(float fLength, D3DXVECTOR2 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot);

	//設定
	void SetCamera(void);

	//取得
	Camera* GetCamera(void);
private:
	Camera m_camera;
};

//プロトタイプ宣言
Camera *GetCamera(void);

#endif // !_CAMERA_H_

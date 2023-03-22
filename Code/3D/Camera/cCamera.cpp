//==========================================
//
//カメラ関係プログラム[cCamera.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "cCamera.h"
#include "..\..\Core\Input\input.h"
#include "..\..\Core\Debugproc\cDebugproc.h"

//マクロ
#define CAMERA_MOVE_SPEED		(1.0f)		//カメラ移動速度
#define CAMERA_MOU_ROT_SPEED	(0.0012f)	//マウス移動での回転速度
#define CAMERA_LENGTH			(5200.0f)	//カメラが見える最大距離

//プロト
void FixPosV(Camera *pCamera);
void FixPosR(Camera *pCamera);
void FixRot(D3DXVECTOR3* pRot);

//========================
//コンストラクタ（初期化処理）
//========================
cCamera::cCamera()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
}

//========================
//デストラクタ（何もしない）
//========================
cCamera::~cCamera()
{
	
}

//========================
//移動処理
//========================
void cCamera::MoveCamera(float moveX, float moveY)
{
	//視点設定
	this->m_camera.rot.y -= moveX * CAMERA_MOU_ROT_SPEED;
	this->m_camera.rot.x -= moveY * CAMERA_MOU_ROT_SPEED;
	FixRot(&m_camera.rot);
	this->m_camera.vecU.x = sinf(this->m_camera.rot.x) * sinf(this->m_camera.rot.y);
	this->m_camera.vecU.y = cosf(this->m_camera.rot.x);
	this->m_camera.vecU.z = sinf(this->m_camera.rot.x) * cosf(this->m_camera.rot.y) * -1;
	D3DXVec3Normalize(&this->m_camera.vecU, &this->m_camera.vecU);
	FixPosV(&this->m_camera);
}

//========================
//設定処理
//========================
void cCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//プロジェクションマトリックス初期化
	D3DXMatrixIdentity(&this->m_camera.mtxProjection);

	//作成
	D3DXMatrixPerspectiveFovLH(&this->m_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_LENGTH);

	//設定
	pDevice->SetTransform(D3DTS_PROJECTION, &this->m_camera.mtxProjection);

	
	//ビューマトリックス初期化
	D3DXMatrixIdentity(&this->m_camera.mtxView);

	//作成
	D3DXMatrixLookAtLH(&this->m_camera.mtxView, &this->m_camera.posV, &this->m_camera.posR, &this->m_camera.vecU);

	//設定
	pDevice->SetTransform(D3DTS_VIEW, &this->m_camera.mtxView);
}

//========================
//カメラ位置向きを元に戻す
//========================
void cCamera::ResetCamera(float fLength, D3DXVECTOR2 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot)
{
	this->m_camera.fLength = fLength;
	this->m_camera.posV = D3DXVECTOR3(posV.x, posV.y, -this->m_camera.fLength);
	this->m_camera.posR = D3DXVECTOR3(posR.x, posR.y, posR.z);
	this->m_camera.rot = rot;

	this->m_camera.vecU.x = sinf(this->m_camera.rot.x) * sinf(this->m_camera.rot.y);
	this->m_camera.vecU.y = cosf(this->m_camera.rot.x);
	this->m_camera.vecU.z = sinf(this->m_camera.rot.x) * cosf(this->m_camera.rot.y) * -1;
	D3DXVec3Normalize(&this->m_camera.vecU, &this->m_camera.vecU);
	FixPosV(&this->m_camera);
}

//========================
//カメラ情報取得
//========================
Camera* cCamera::GetCamera(void)
{
	return &this->m_camera;
}

//========================
//視点修正（注視点中心）
//========================
void FixPosV(Camera *pCamera)
{
	pCamera->posV.x = pCamera->posR.x + cosf(pCamera->rot.x) * sinf(pCamera->rot.y) * pCamera->fLength;
	pCamera->posV.y = pCamera->posR.y - sinf(pCamera->rot.x) * pCamera->fLength;
	pCamera->posV.z = pCamera->posR.z - cosf(pCamera->rot.x) * cosf(pCamera->rot.y) * pCamera->fLength;
}

//========================
//注視点修正（視点中心）
//========================
void FixPosR(Camera* pCamera)
{
	pCamera->posR.x = pCamera->posV.x - sinf(pCamera->rot.y) * cosf(pCamera->rot.x) * pCamera->fLength;
	pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * cosf(pCamera->rot.x) * pCamera->fLength;
}

//========================
//角度修正
//========================
void FixRot(D3DXVECTOR3* pRot)
{
	//カメラ1周計算
	pRot->x = FIX_ROT(pRot->x);
	pRot->y = FIX_ROT(pRot->y);
	pRot->z = FIX_ROT(pRot->z);
}
//==========================================
//
//�J�����֌W�v���O����[cCamera.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "cCamera.h"
#include "..\..\Core\Input\input.h"
#include "..\..\Core\Debugproc\cDebugproc.h"

//�}�N��
#define CAMERA_MOVE_SPEED		(1.0f)		//�J�����ړ����x
#define CAMERA_MOU_ROT_SPEED	(0.0012f)	//�}�E�X�ړ��ł̉�]���x
#define CAMERA_LENGTH			(5200.0f)	//�J������������ő勗��

//�v���g
void FixPosV(Camera *pCamera);
void FixPosR(Camera *pCamera);
void FixRot(D3DXVECTOR3* pRot);

//========================
//�R���X�g���N�^�i�����������j
//========================
cCamera::cCamera()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
}

//========================
//�f�X�g���N�^�i�������Ȃ��j
//========================
cCamera::~cCamera()
{
	
}

//========================
//�ړ�����
//========================
void cCamera::MoveCamera(float moveX, float moveY)
{
	//���_�ݒ�
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
//�ݒ菈��
//========================
void cCamera::SetCamera(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�v���W�F�N�V�����}�g���b�N�X������
	D3DXMatrixIdentity(&this->m_camera.mtxProjection);

	//�쐬
	D3DXMatrixPerspectiveFovLH(&this->m_camera.mtxProjection, D3DXToRadian(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, CAMERA_LENGTH);

	//�ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &this->m_camera.mtxProjection);

	
	//�r���[�}�g���b�N�X������
	D3DXMatrixIdentity(&this->m_camera.mtxView);

	//�쐬
	D3DXMatrixLookAtLH(&this->m_camera.mtxView, &this->m_camera.posV, &this->m_camera.posR, &this->m_camera.vecU);

	//�ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &this->m_camera.mtxView);
}

//========================
//�J�����ʒu���������ɖ߂�
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
//�J�������擾
//========================
Camera* cCamera::GetCamera(void)
{
	return &this->m_camera;
}

//========================
//���_�C���i�����_���S�j
//========================
void FixPosV(Camera *pCamera)
{
	pCamera->posV.x = pCamera->posR.x + cosf(pCamera->rot.x) * sinf(pCamera->rot.y) * pCamera->fLength;
	pCamera->posV.y = pCamera->posR.y - sinf(pCamera->rot.x) * pCamera->fLength;
	pCamera->posV.z = pCamera->posR.z - cosf(pCamera->rot.x) * cosf(pCamera->rot.y) * pCamera->fLength;
}

//========================
//�����_�C���i���_���S�j
//========================
void FixPosR(Camera* pCamera)
{
	pCamera->posR.x = pCamera->posV.x - sinf(pCamera->rot.y) * cosf(pCamera->rot.x) * pCamera->fLength;
	pCamera->posR.z = pCamera->posV.z + cosf(pCamera->rot.y) * cosf(pCamera->rot.x) * pCamera->fLength;
}

//========================
//�p�x�C��
//========================
void FixRot(D3DXVECTOR3* pRot)
{
	//�J����1���v�Z
	pRot->x = FIX_ROT(pRot->x);
	pRot->y = FIX_ROT(pRot->y);
	pRot->z = FIX_ROT(pRot->z);
}
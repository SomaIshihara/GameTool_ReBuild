//==========================================
//
//�Q�[���v���O����[game.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "game.h"
//#include "..\..\Core\File\file.h"
#include "..\..\Core\Input\input.h"
#include "..\..\3D\Camera\cCamera.h"
#include "..\..\3D\Light\cLight.h"
#include "..\..\Resource\Model\cModel.h"
#include "..\..\Added\cMotionModel.h"

//�O���[�o��
cCamera g_camera;
cLight g_light;
cModel g_model;
cMotionModel g_motionModel;

//========================
//����������
//========================
void InitGame(void)
{
	//g_model.LoadModel("data\\MODEL\\Rock_xfile\\Rock_01.x");
	g_motionModel.LoadMotionModel("data\\motion_exithuman.txt");
	g_light.SetLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, -0.8f, 0.4f));
}

//========================
//�I������
//========================
void UninitGame(void)
{
	
}

//========================
//�X�V����
//========================
void UpdateGame(void)
{
	
	//�J����
	g_camera.MoveCamera(0.0f, 0.0f);
}

//========================
//�`�揈��
//========================
void DrawGame(void)
{
	//���}�g������
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//�J�����ݒ�
	g_camera.SetCamera();
	g_motionModel.SetMotionModel(&mtxWorld);

	//g_model.SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
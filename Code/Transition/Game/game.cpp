//==========================================
//
//�Q�[���v���O����[game.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "game.h"
#include "..\..\Core\Input\input.h"
#include "..\..\3D\Camera\cCamera.h"
#include "..\..\3D\Light\cLight.h"
#include "..\..\Resource\Model\cModel.h"
#include "..\..\3D\MotionModel\cMotionModel.h"
#include "..\..\Added\Player.h"

//�O���[�o��
cCamera g_camera;
cLight g_light;
cModel g_model;
Player g_Player;

//========================
//����������
//========================
void InitGame(void)
{
	//g_model.LoadModel("data\\MODEL\\Rock_xfile\\Rock_01.x");
	g_Player.LoadMotionModel("data\\motion_exithuman.txt");
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
	g_Player.Update();
	//�J����
	g_camera.MoveCamera(0.0f, 0.0f);
}

//========================
//�`�揈��
//========================
void DrawGame(void)
{
	//�J�����ݒ�
	g_camera.SetCamera();

	//�v���C���[�`��
	g_Player.Draw();

	//g_model.SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
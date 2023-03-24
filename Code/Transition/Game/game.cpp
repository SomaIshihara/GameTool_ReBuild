//==========================================
//
//ゲームプログラム[game.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "game.h"
//#include "..\..\Core\File\file.h"
#include "..\..\Core\Input\input.h"
#include "..\..\3D\Camera\cCamera.h"
#include "..\..\3D\Light\cLight.h"
#include "..\..\Resource\Model\cModel.h"

//グローバル
cCamera g_camera;
cLight g_light;
cModel g_model;

//========================
//初期化処理
//========================
void InitGame(void)
{
	g_model.LoadModel("data\\MODEL\\Rock_xfile\\Rock_01.x");
	g_light.SetLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, -0.8f, 0.4f));
}

//========================
//終了処理
//========================
void UninitGame(void)
{
	
}

//========================
//更新処理
//========================
void UpdateGame(void)
{
	//カメラ
	g_camera.MoveCamera(0.0f, 0.0f);
}

//========================
//描画処理
//========================
void DrawGame(void)
{
	//カメラ設定
	g_camera.SetCamera();

	g_model.SetModel(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}
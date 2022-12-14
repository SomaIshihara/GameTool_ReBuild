//==========================================
//
//ゲームプログラム[game.cpp]
//Author:石原颯馬
//
//==========================================
#include "main.h"
#include "game.h"
#include "result.h"
#include "wall.h"
#include "player.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "sky.h"
#include "object.h"
#include "file.h"
#include "input.h"
#include "camera.h"

//========================
//初期化処理
//========================
void InitGame(void)
{
	//オブジェクト初期化
	InitSky();
	InitMeshfield();
	InitWall();
	InitBullet();
	InitShadow();
	InitPlayer();
	InitObject();

	//壁生成
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1120.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f);		//前
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1120.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f);	//後ろ
	SetWall(D3DXVECTOR3(-1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f);	//左
	SetWall(D3DXVECTOR3(1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f);		//右

	//ファイル読み込み・オブジェクト生成
	LoadMapFile();
}

//========================
//終了処理
//========================
void UninitGame(void)
{
	//終了処理
	UninitObject();
	UninitPlayer();
	UninitShadow();
	UninitBullet();
	UninitWall();
	UninitMeshfield();
	UninitSky();
}

//========================
//更新処理
//========================
void UpdateGame(void)
{
	//影
	UpdateShadow();

	//空
	UpdateSky();

	//メッシュフィールド
	UpdateMeshfield();

	//壁
	UpdateWall();

	//弾
	UpdateBullet();

	//プレイヤー
	UpdatePlayer();

	//オブジェクト
	UpdateObject();


	//リザルト移行
	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		SetResult(RESULT_CLEAR);
		SetMode(MODE_RESULT);
		ResetCamera();
	}
	else if (GetKeyboardTrigger(DIK_F3) == true)
	{
		SetResult(RESULT_OVER);
		SetMode(MODE_RESULT);
		ResetCamera();
	}
}

//========================
//描画処理
//========================
void DrawGame(void)
{
	//空
	DrawSky();

	//メッシュフィールド
	DrawMeshfield();

	//壁
	DrawWall();

	//影
	DrawShadow();

	

	//プレイヤー
	DrawPlayer();

	//オブジェクト
	DrawObject();

	//弾
	DrawBullet();
}
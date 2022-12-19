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

//マクロ
#define GAME_CLEAR_TIME	(0 * 60)	//ゲームクリアにするまでかかる滞在時間

//グローバル
int g_nCnterSafeAreaTime;

//========================
//初期化処理
//========================
void InitGame(void)
{
	//変数初期化
	g_nCnterSafeAreaTime = 0;

	//オブジェクト初期化
	InitSky();
	InitMeshfield();
	InitWall();
	InitBullet();
	InitShadow();
	InitPlayer();
	InitObject();

	//壁生成（デジャブ）
	//普通の壁
	SetWall(D3DXVECTOR3(0.0f, 0.0f, 1120.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f, false);		//前
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -1120.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 2720.0f, 80.0f, false);		//後
	SetWall(D3DXVECTOR3(-1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f, false);	//左
	SetWall(D3DXVECTOR3(1360.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 2240.0f, 50.0f, false);		//右

	//大人の壁
	SetWall(D3DXVECTOR3(-960.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-480.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(960.0f, 0.0f, 800.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-400.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-80.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(80.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(400.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, 720.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(-1040.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-880.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-560.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-400.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(-80.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(560.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(880.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, -0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(1040.0f, 0.0f, 240.0f), D3DXVECTOR3(0.0f, 0.5f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

	SetWall(D3DXVECTOR3(0.0f, 0.0f, 160.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(0.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, 160.0f), D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);
	SetWall(D3DXVECTOR3(480.0f, 0.0f, -160.0f), D3DXVECTOR3(0.0f, 0.0f * D3DX_PI, 0.0f), 160.0f, 200.0f, true);

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
	Player *pPlayer = GetPlayer();
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

	//セーフエリアに入っているか確認
	if (pPlayer->bIntoSafeArea == true)
	{
		g_nCnterSafeAreaTime++;
		if (g_nCnterSafeAreaTime >= GAME_CLEAR_TIME)
		{
			SetResult(RESULT_CLEAR);
			SetMode(MODE_RESULT);
			ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
		}
	}
	else
	{
		g_nCnterSafeAreaTime = 0;
	}

	//リザルト移行
	if (GetKeyboardTrigger(DIK_F2) == true)
	{
		SetResult(RESULT_CLEAR);
		SetMode(MODE_RESULT);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
	}
	else if (GetKeyboardTrigger(DIK_F3) == true)
	{
		SetResult(RESULT_OVER);
		SetMode(MODE_RESULT);
		ResetCamera(200.0f, D3DXVECTOR2(0.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
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
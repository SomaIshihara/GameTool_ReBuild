//==========================================
//
//ゲーム全般を管理するプログラムのヘッダ[main.h]
//Author:石原颯馬
//
//==========================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <XInput.h>
#include <string.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	//ビルド時の警告対処
#include "dinput.h"
#include "xaudio2.h"

//ImGUI
#include "..\..\ImGUI\imgui.h"
#include "..\..\ImGUI\imgui_impl_win32.h"
#include "..\..\ImGUI\imgui_impl_dx9.h"
#include <d3d9.h>
#include <tchar.h>
#include <vector>

//ライブラリのリンク
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")

//画面モード
typedef enum
{
	MODE_TITLE = 0,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
} MODE;

//マクロ定義
#define CLASS_NAME			"WindowClass"
#define WINDOW_NAME			"hogehoge"
#define SCREEN_WIDTH		(1280)		//クライアント領域の幅
#define SCREEN_HEIGHT		(720)		//クライアント領域の高さ
#define MAX_FPS				(60)		//最大フレームレート
#define MAX_PATH_STR		(1024)		//ファイルパスの長さ
#define FVF_VERTEX_2D		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2D
#define FVF_VERTEX_3D		(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//3D
#define INIT_ZERO			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))

//頂点情報[2D]
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換係数（1.0fで固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

//頂点情報[3D]
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 nor;	//法線ベクトル
	D3DCOLOR col;		//カラー
	D3DXVECTOR2 tex;	//テクスチャ
} VERTEX_3D;

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetShowCursor(bool bDisp);
void SetMode(MODE mode);
MODE GetMode(void);

#endif // !_MAIN_H_

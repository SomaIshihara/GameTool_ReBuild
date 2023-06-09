//==========================================
//
//ゲーム全般を管理するプログラム[main.cpp]
//Author:石原颯馬
//
//==========================================
//main
#include "main.h"
#include "..\..\Core\Input\input.h"
#include "..\..\3D\Camera\cCamera.h"
#include "..\..\3D\Light\cLight.h"
#include "..\..\Resource\Model\cModel.h"
#include "..\..\Core\Input\input.h"
#include "..\..\Core\DebugProc\cDebugproc.h"
#include "..\..\Transition\Game\game.h"

//マクロ定義
#define PROC_SPEED	(1000 / MAX_FPS)
#define FPS_SPEED	(500)
#define SHOWCURSOR_COUNTER		(2)	//カーソル表示非表示が正常にされるカウンタ

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(HWND hWnd);
void Draw(void);
void UpdateShowCursor(void);
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;	//Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//Direct3Dデバイスへのポインタ
int g_nCountFPS;			//FPSカウンタ
MODE g_mode = MODE_TITLE;
bool g_bShowCursor = true;
bool g_bDebug = true;

//クラス
cKeyboard g_keyboard;
cMouse g_mouse;
cDebugProc *g_pDebugProc;

//========================
//メイン関数
//========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int CmdShow)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };	//ウィンドウの領域（書き換え不可の定数）

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					//メモリサイズ
		CS_CLASSDC,							//ウィンドウのスタイル
		WindowProc,							//ウィンドウプロシージャ
		0,									//使用しない
		0,									//使用しない
		hInstance,							//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),		//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),			//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),			//クライアント領域の背景色
		NULL,								//メニューバー
		CLASS_NAME,							//クラスの名前
		LoadIcon(NULL,IDI_APPLICATION)		//アプリケーションのアイコン
	};

	HWND hWnd;	//ウィンドウハンドル
	MSG msg;	//メッセージ格納

	//時刻関係
	DWORD dwCurrentTime;		//現在時刻
	DWORD dwExecLastTime;		//最後に処理した時刻

	//デバッグ（FPS関係）
	DWORD dwFrameCount;		//フレームカウント
	DWORD dwFPSLastTime;	//最後にFPSを計測した時刻

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定サイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(
		0,						//拡張ウィンドウスタイル
		CLASS_NAME,				//ウィンドウクラスの名前
		WINDOW_NAME,			//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,	//ウィンドウスタイル
		CW_USEDEFAULT,						//ウィンドウの左上X座標
		CW_USEDEFAULT,						//ウィンドウの左上Y座標
		(rect.right - rect.left),			//ウィンドウの幅
		(rect.bottom - rect.top),			//ウィンドウの高さ
		NULL,								//親ウィンドウのハンドル
		NULL,					//メニューハンドルまたは子ウィンドウID
		hInstance,				//インスタンスハンドル
		NULL					//ウィンドウ作成データ
	);

	//初期化
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//分解能設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;		//初期化
	dwExecLastTime = timeGetTime();

	//デバッグ（FPS計測）
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//ウィンドウの表示
	ShowWindow(hWnd, CmdShow);
	UpdateWindow(hWnd);

	//カーソルを消す
	SetShowCursor(true);

	//メッセージループ
	while (1)
	{
#if 0
		if (GetMousePos().x > 0.0f && GetMousePos().x < SCREEN_WIDTH && GetMousePos().y > 0.0f && GetMousePos().y < SCREEN_HEIGHT)
		{
			SetShowCursor(false);
		}
		else
		{
			SetShowCursor(true);
		}
#endif

		//カーソル表示非表示更新
		UpdateShowCursor();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= FPS_SPEED)
			{//0.5秒経過
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= PROC_SPEED)
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;

				//更新処理
				Update(hWnd);

				//描画処理
				Draw();

				//フレームカウント加算
				dwFrameCount++;
			}
		}
	}

	//カーソル表示
	while (ShowCursor(TRUE) < 0);
	while (ShowCursor(FALSE) > 0);

	Uninit();

	//クラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//========================
//ウィンドウプロシージャ
//========================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;

	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			SetShowCursor(true);
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);	//Destroyメッセージを送る
			}
			SetShowCursor(false);
			break;
		}
		break;
	case WM_CLOSE:
		SetShowCursor(true);
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			DestroyWindow(hWnd);	//Destroyメッセージを送る
		}
		else
		{
			SetShowCursor(false);
			return 0;
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//========================
//初期化処理
//========================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;
	D3DPRESENT_PARAMETERS d3dpp;

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のスクリーンモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;			//画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;			//バックバッファの形式
	d3dpp.BackBufferCount = 1;						//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;		//ダブルバッファの切り替え（同期）
	d3dpp.EnableAutoDepthStencil = TRUE;			//デプスバッファとステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;		//デプスバッファとして16ビット使用
	d3dpp.Windowed = bWindow;						//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

	//Direr3Dデバイスの生成
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//オブジェクトの初期化処理
	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステート設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステート設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//ImGUI系
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.Fonts->AddFontFromFileTTF("data//FONTS//meiryo.ttc", 20.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//ImGui::StyleColorsLight();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(GetDevice());// GetGlyphRangesJapanese

	//オブジェクト初期化
	
	return S_OK;
}

//========================
//終了処理
//========================
void Uninit(void)
{
	//終了処理（自分が作ったものを捨てる）

	//ImGUI
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//XInput終了
	XInputEnable(false);

	//デバイス破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//オブジェクト破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//========================
//更新処理
//========================
void Update(HWND hWnd)
{
	//まとまったものから選ぶ
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateGame();
		break;
	case MODE_GAME:
		UpdateGame();
		break;
	case MODE_RESULT:
		UpdateGame();
		break;
	}
}

//========================
//描画処理
//========================
void Draw(void)
{
	//画面クリア（バックバッファとZバッファのクリア
#if 0
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
#endif
#if 1
	g_pD3DDevice->Clear(0, NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(50, 50, 50, 0), 1.0f, 0);
#endif


	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//成功した場合
		//オブジェクト描画
		//まとまったものから選ぶ
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawGame();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawGame();
			break;
		}

		//デバッグ表示
		g_pDebugProc->DrawDebugProc();

		//描画終了処理
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//========================
//デバイス取得
//========================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//========================
//カーソル表示設定
//========================
void SetShowCursor(bool bDisp)
{
	//カーソル表示有無の設定
	g_bShowCursor = bDisp;

	if (g_bShowCursor)
	{
		ShowCursor(TRUE);
		while (ShowCursor(TRUE) <= SHOWCURSOR_COUNTER);
	}
	else
	{
		ShowCursor(FALSE);
		while (ShowCursor(FALSE) > SHOWCURSOR_COUNTER);
	}
}

//========================
//カーソル更新処理（内部カウンタを小さくする）
//========================
void UpdateShowCursor(void)
{
	//小さくする処理
	if (g_bShowCursor)
	{
		while (ShowCursor(FALSE) > SHOWCURSOR_COUNTER);
		ShowCursor(TRUE);
	}
	else
	{
		while (ShowCursor(TRUE) <= -SHOWCURSOR_COUNTER);
		ShowCursor(FALSE);
	}
}

//========================
//設定処理
//========================
void SetMode(MODE mode)
{
	//現在の画面終了
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitGame();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitGame();
		break;
	}

	//次の画面初期化
	switch (mode)
	{
	case MODE_TITLE:
		InitGame();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitGame();
		break;
	}

	//代入
	g_mode = mode;
}

//========================
//取得処理
//========================
MODE GetMode(void) 
{
	return g_mode;
}
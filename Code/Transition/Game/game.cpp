//==========================================
//
//ゲームプログラム[game.cpp]
//Author:石原颯馬
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
#include <vector>

//プロトタイプ宣言
void UpdateImGui(void);

//グローバル
cCamera g_camera;
cLight g_light;
Player g_Player;

//ファイルパス
std::vector<const char*> g_StrFilePath = {};
std::vector<cModel> g_aModel = {};

//========================
//初期化処理
//========================
void InitGame(void)
{
	//モデルクラスのvector枠確保
	g_aModel.reserve(128);

	g_Player.LoadMotionModel("data\\motion_ino.txt");
	g_light.SetLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, -0.8f, 0.4f));
}

//========================
//終了処理
//========================
void UninitGame(void)
{
	//ファイルパス破棄
	for (const char* item : g_StrFilePath) {
		free((void*)item);
	}
}

//========================
//更新処理
//========================
void UpdateGame(void)
{
	//ImGui
	UpdateImGui();

	//プレイヤー
	g_Player.Update();
	//カメラ
	g_camera.MoveCamera();
	//g_camera.MoveCamera(0.0f, 0.0f);
}

//========================
//描画処理
//========================
void DrawGame(void)
{
	//カメラ設定
	g_camera.SetCamera();

	D3DXMATRIX hogeMtx;
	D3DXMatrixIdentity(&hogeMtx);

	//モデル描画
	for (int cntModel = 0; cntModel < g_aModel.size(); cntModel++)
	{
		g_aModel.at(cntModel).DrawModel(INIT_ZERO, INIT_ZERO, INIT_ZERO, &hogeMtx);
	}

	//プレイヤー描画
	g_Player.Draw();

	//ImGUI
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//========================
//ImGui更新処理
//========================
void UpdateImGui(void)
{
	//ImGUI
	ImGuiIO& io = ImGui::GetIO();

	static bool hogehoge = false;
	static int item_current = 0;

	// Demonstrate the various window flags. Typically you would just use the default!
	static bool no_titlebar = false;
	static bool no_scrollbar = false;
	static bool no_menu = false;
	static bool no_move = false;
	static bool no_resize = false;
	static bool no_collapse = false;
	static bool no_close = false;
	static bool no_nav = false;
	static bool no_background = false;
	static bool no_bring_to_front = false;
	static bool unsaved_document = false;

	ImGuiWindowFlags window_flags = 0;
	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (unsaved_document)   window_flags |= ImGuiWindowFlags_UnsavedDocument;

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowSize(ImVec2(335, 580), ImGuiCond_Once);	// サイズ
	ImGui::Begin(u8"hoge", NULL, window_flags);				// 名前

															// Menu Bar
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Open Model"))
			{
				static OPENFILENAME     ofn;
				static TCHAR            szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = FindWindow(NULL, TEXT(WINDOW_NAME));
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("Xファイル(*.x)\0*.x\0");
					ofn.lpstrTitle = TEXT("モデルファイルを選択");
					ofn.Flags = OFN_FILEMUSTEXIST;
				}
				if (GetOpenFileName(&ofn)) {
					g_StrFilePath.push_back(_strdup(szFile));
					item_current = g_StrFilePath.size() - 1;
				}
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Examples"))
		{
			ImGui::MenuItem("Main menu bar", NULL, &hogehoge);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::MenuItem("Main menu bar", NULL, &hogehoge);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	ImGui::Combo("Select Model", &item_current, g_StrFilePath.data(), g_StrFilePath.size());
	if (ImGui::Button("Add Model"))
	{
		if (g_StrFilePath.size() != 0)
		{
			cModel model;
			g_aModel.push_back(model);
			g_aModel.back().LoadModel(g_StrFilePath.at(item_current));
		}
	}

	ImGui::End();

	ImGui::EndFrame();
}
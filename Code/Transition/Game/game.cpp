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
#include "..\..\2D\Meshfield\meshfield.h"
#include <vector>

//プロトタイプ宣言
void UpdateImGui(void);

//グローバル
cCamera g_camera;
cLight g_light;
cPlayer g_Player;

//ファイルパス
std::vector<const char*> g_StrFilePath = {};
std::vector<cModel> g_aModel = {};
std::vector<cMeshfield>g_aMeshfield = {};

//========================
//初期化処理
//========================
void InitGame(void)
{
	//モデルクラスのvector枠確保
	g_aModel.reserve(128);
	g_aMeshfield.reserve(128);

	//プレイヤーの初期化処理
	g_Player.LoadMotionModel("data\\motion_ino.txt");
	*g_Player.GetLinkCamera() = g_camera.LinkedCamera();

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
		g_aModel.at(cntModel).DrawModel(
			g_aModel.at(cntModel).GetModel().posOffset,
			g_aModel.at(cntModel).GetModel().rotOffset,
			INIT_ZERO, &hogeMtx);
	}

	//メッシュフィールド描画
	for (int cntModel = 0; cntModel < g_aMeshfield.size(); cntModel++)
	{
		g_aMeshfield.at(cntModel).Draw();
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

	//ほげ
	static bool hogehoge = false;

	//共通
	static float pos[4] = { 0.00f, 0.00f, 0.00f, 0.44f };
	static float rot[4] = { 0.00f, 0.00f, 0.00f, 0.44f };

	//モデル
	static int item_current = 0;

	//メッシュフィールド
	static int width = 1;
	static int height = 1;
	static float length = 100.0f;

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
	ImGui::Begin(u8"Inspector", NULL, window_flags);				// 名前

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

	ImGui::Text("------------------Commons---------------");
	ImGui::InputFloat3("Pos", pos);
	ImGui::InputFloat3("Rot", rot);
	ImGui::Text("-------------------Model-------------------");
	ImGui::Text("Select Model");
	ImGui::Combo(" ", &item_current, g_StrFilePath.data(), g_StrFilePath.size());
	if (ImGui::Button("Add Model"))
	{
		if (g_StrFilePath.size() != 0)
		{
			//プッシュ用変数宣言
			cModel model;
			ModelStruct modelstr;

			//Pos・RotをD3DXVECTOR3型に変換
			D3DXVECTOR3 dxPos = D3DXVECTOR3(pos[0], pos[1], pos[2]);
			D3DXVECTOR3 dxRot = D3DXVECTOR3(rot[0], rot[1], rot[2]);

			//プッシュするデータを設定
			modelstr.posOffset = dxPos;
			modelstr.rotOffset = dxRot;
			modelstr.m_IdxModelParent = -1;

			g_aModel.push_back(model);
			g_aModel.back().LoadModel(g_StrFilePath.at(item_current));
			g_aModel.back().SetModelSetup(modelstr);
		}
	}
	ImGui::Text("-----------------Meshfield-----------------");
	//分割数を最低1にする
	if (width < 1)width = 1;
	if (height < 1)height = 1;

	//長さを最低0.1にする
	if (length < 0.1f)length = 0.1f;

	ImGui::InputInt("Width", &width);
	ImGui::InputInt("Height", &height);
	ImGui::InputFloat("Length", &length);
	if (ImGui::Button("Generate"))
	{
		//Pos・RotをD3DXVECTOR3型に変換
		D3DXVECTOR3 dxPos = D3DXVECTOR3(pos[0], pos[1], pos[2]);
		D3DXVECTOR3 dxRot = D3DXVECTOR3(rot[0], rot[1], rot[2]);

		//メッシュフィールドの設置
		cMeshfield meshfield;
		g_aMeshfield.push_back(meshfield);
		g_aMeshfield.back().SetMeshfield(dxPos, dxRot, "hoge", width, height, length);
	}

	ImGui::End();

	ImGui::EndFrame();
}
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
#include "..\..\2D\Meshfield\meshfield.h"
#include <vector>

//�v���g�^�C�v�錾
void UpdateImGui(void);

//�O���[�o��
cCamera g_camera;
cLight g_light;
cPlayer g_Player;

//�t�@�C���p�X
std::vector<const char*> g_StrFilePath = {};
std::vector<cModel> g_aModel = {};
std::vector<cMeshfield>g_aMeshfield = {};

//========================
//����������
//========================
void InitGame(void)
{
	//���f���N���X��vector�g�m��
	g_aModel.reserve(128);
	g_aMeshfield.reserve(128);

	//�v���C���[�̏���������
	g_Player.LoadMotionModel("data\\motion_ino.txt");
	*g_Player.GetLinkCamera() = g_camera.LinkedCamera();

	g_light.SetLight(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.2f, -0.8f, 0.4f));
}

//========================
//�I������
//========================
void UninitGame(void)
{
	//�t�@�C���p�X�j��
	for (const char* item : g_StrFilePath) {
		free((void*)item);
	}
}

//========================
//�X�V����
//========================
void UpdateGame(void)
{
	//ImGui
	UpdateImGui();

	//�v���C���[
	g_Player.Update();
	//�J����
	g_camera.MoveCamera();
}

//========================
//�`�揈��
//========================
void DrawGame(void)
{
	//�J�����ݒ�
	g_camera.SetCamera();

	D3DXMATRIX hogeMtx;
	D3DXMatrixIdentity(&hogeMtx);

	//���f���`��
	for (int cntModel = 0; cntModel < g_aModel.size(); cntModel++)
	{
		g_aModel.at(cntModel).DrawModel(
			g_aModel.at(cntModel).GetModel().posOffset,
			g_aModel.at(cntModel).GetModel().rotOffset,
			INIT_ZERO, &hogeMtx);
	}

	//���b�V���t�B�[���h�`��
	for (int cntModel = 0; cntModel < g_aMeshfield.size(); cntModel++)
	{
		g_aMeshfield.at(cntModel).Draw();
	}

	//�v���C���[�`��
	g_Player.Draw();

	//ImGUI
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

//========================
//ImGui�X�V����
//========================
void UpdateImGui(void)
{
	//ImGUI
	ImGuiIO& io = ImGui::GetIO();

	//�ق�
	static bool hogehoge = false;

	//����
	static float pos[4] = { 0.00f, 0.00f, 0.00f, 0.44f };
	static float rot[4] = { 0.00f, 0.00f, 0.00f, 0.44f };

	//���f��
	static int item_current = 0;

	//���b�V���t�B�[���h
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

	ImGui::SetNextWindowSize(ImVec2(335, 580), ImGuiCond_Once);	// �T�C�Y
	ImGui::Begin(u8"Inspector", NULL, window_flags);				// ���O

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
					ofn.lpstrInitialDir = szPath;       // �����t�H���_�ʒu
					ofn.lpstrFile = szFile;       // �I���t�@�C���i�[
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrFilter = TEXT("X�t�@�C��(*.x)\0*.x\0");
					ofn.lpstrTitle = TEXT("���f���t�@�C����I��");
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
			//�v�b�V���p�ϐ��錾
			cModel model;
			ModelStruct modelstr;

			//Pos�ERot��D3DXVECTOR3�^�ɕϊ�
			D3DXVECTOR3 dxPos = D3DXVECTOR3(pos[0], pos[1], pos[2]);
			D3DXVECTOR3 dxRot = D3DXVECTOR3(rot[0], rot[1], rot[2]);

			//�v�b�V������f�[�^��ݒ�
			modelstr.posOffset = dxPos;
			modelstr.rotOffset = dxRot;
			modelstr.m_IdxModelParent = -1;

			g_aModel.push_back(model);
			g_aModel.back().LoadModel(g_StrFilePath.at(item_current));
			g_aModel.back().SetModelSetup(modelstr);
		}
	}
	ImGui::Text("-----------------Meshfield-----------------");
	//���������Œ�1�ɂ���
	if (width < 1)width = 1;
	if (height < 1)height = 1;

	//�������Œ�0.1�ɂ���
	if (length < 0.1f)length = 0.1f;

	ImGui::InputInt("Width", &width);
	ImGui::InputInt("Height", &height);
	ImGui::InputFloat("Length", &length);
	if (ImGui::Button("Generate"))
	{
		//Pos�ERot��D3DXVECTOR3�^�ɕϊ�
		D3DXVECTOR3 dxPos = D3DXVECTOR3(pos[0], pos[1], pos[2]);
		D3DXVECTOR3 dxRot = D3DXVECTOR3(rot[0], rot[1], rot[2]);

		//���b�V���t�B�[���h�̐ݒu
		cMeshfield meshfield;
		g_aMeshfield.push_back(meshfield);
		g_aMeshfield.back().SetMeshfield(dxPos, dxRot, "hoge", width, height, length);
	}

	ImGui::End();

	ImGui::EndFrame();
}
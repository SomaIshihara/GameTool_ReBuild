//==========================================
//
//プレイヤープログラム[Player.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\Core\Main\main.h"
#include "..\Core\Input\input.h"
#include "Player.h"
#include "..\Mathysics\Culc\Culc.h"

#define PLAYER_MOVE_SPEED	(1.5f)	//移動速度

//角度
#define ROT_WD	(-0.75f * D3DX_PI)
#define ROT_WA	(0.75f * D3DX_PI)
#define ROT_W	(1.0f * D3DX_PI)
#define ROT_SD	(-0.25f * D3DX_PI)
#define ROT_SA	(0.25f * D3DX_PI)
#define ROT_S	(0.0f * D3DX_PI)
#define ROT_D	(-0.5f * D3DX_PI)
#define ROT_A	(0.5f * D3DX_PI)

//プロトタイプ宣言
void SetPos(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRot);

//========================
//コンストラクタ
//========================
cPlayer::cPlayer()
{

}

//========================
//デストラクタ
//========================
cPlayer::~cPlayer()
{

}

//========================
//更新処理
//========================
void cPlayer::Update(void)
{
	//キーボードの情報取得
	if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_W) == true)
	{
		//角度指定
		if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
		{
			this->m_player.rot.y = FIX_ROT(ROT_WD - this->m_pCamera->rot.y);
		}
		else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
		{
			this->m_player.rot.y = FIX_ROT(ROT_WA - this->m_pCamera->rot.y);
		}
		else
		{
			this->m_player.rot.y = FIX_ROT(ROT_W - this->m_pCamera->rot.y);
		}

		//位置指定
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_S) == true)
	{
		//角度指定
		if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
		{
			this->m_player.rot.y = FIX_ROT(ROT_SD - this->m_pCamera->rot.y);
		}
		else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
		{
			this->m_player.rot.y = FIX_ROT(ROT_SA - this->m_pCamera->rot.y);
		}
		else
		{
			this->m_player.rot.y = FIX_ROT(ROT_S - this->m_pCamera->rot.y);
		}

		//位置指定
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
	{
		//角度指定
		this->m_player.rot.y = FIX_ROT(ROT_D - this->m_pCamera->rot.y);

		//位置指定
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
	{
		//角度指定
		this->m_player.rot.y = FIX_ROT(ROT_A - this->m_pCamera->rot.y);

		//位置指定
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else
	{
		this->SetMotion(MOTIONTYPE_HOGE);
	}

	//モーション更新
	this->UpdateMotion();
}

//========================
//描画処理
//========================
void cPlayer::Draw(void)
{
	//仮マトリ生成
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&this->m_player.mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->m_player.rot.y, this->m_player.rot.x, this->m_player.rot.z);
	D3DXMatrixMultiply(&this->m_player.mtxWorld, &this->m_player.mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, this->m_player.pos.x, this->m_player.pos.y, this->m_player.pos.z);
	D3DXMatrixMultiply(&this->m_player.mtxWorld, &this->m_player.mtxWorld, &mtxTrans);

	DrawMotionModel(&this->m_player.mtxWorld);
}

//========================
//プレイヤーの取得処理
//========================
Player *cPlayer::GetPlayer(void)
{
	return &this->m_player;
}

//========================
//リンク用カメラの取得処理
//========================
Camera **cPlayer::GetLinkCamera(void)
{
	return &this->m_pCamera;
}

//========================
//プレイヤーの位置設定処理
//========================
void SetPos(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRot)
{
	pPos->x -= sinf(pRot->y) * PLAYER_MOVE_SPEED;
	pPos->z -= cosf(pRot->y) * PLAYER_MOVE_SPEED;
}
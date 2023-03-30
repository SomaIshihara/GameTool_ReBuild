//==========================================
//
//プレイヤープログラム[Player.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\Core\Main\main.h"
#include "..\Core\Input\input.h"
#include "Player.h"

#define PLAYER_MOVE_SPEED	(1.5f)	//移動速度

//========================
//コンストラクタ
//========================
Player::Player()
{

}

//========================
//デストラクタ
//========================
Player::~Player()
{

}

//========================
//更新処理
//========================
void Player::Update(void)
{
	//キーボードの情報取得
	if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_W) == true)
	{
		//角度指定
		if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
		{
			this->rot.y = -0.75f * D3DX_PI;
		}
		else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
		{
			this->rot.y = 0.75f * D3DX_PI;
		}
		else
		{
			this->rot.y = 1.0f * D3DX_PI;
		}

		//位置指定
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_S) == true)
	{
		//角度指定
		if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
		{
			this->rot.y = -0.25f * D3DX_PI;
		}
		else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
		{
			this->rot.y = 0.25f * D3DX_PI;
		}
		else
		{
			this->rot.y = 0.0f * D3DX_PI;
		}

		//位置指定
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
	{
		//角度指定
		this->rot.y = -0.5f * D3DX_PI;

		//位置指定
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
	{
		//角度指定
		this->rot.y = 0.5f * D3DX_PI;

		//位置指定
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
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
void Player::Draw(void)
{
	//仮マトリ生成
	D3DXMATRIX mtxRot, mtxTrans;

	//ワールドマトリックス初期化
	D3DXMatrixIdentity(&this->mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->mtxWorld, &this->mtxWorld, &mtxRot);

	//位置反映
	D3DXMatrixTranslation(&mtxTrans, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->mtxWorld, &this->mtxWorld, &mtxTrans);

	DrawMotionModel(&this->mtxWorld);
}
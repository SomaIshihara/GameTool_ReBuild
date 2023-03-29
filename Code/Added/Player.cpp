//==========================================
//
//プレイヤープログラム[Player.cpp]
//Author:石原颯馬
//
//==========================================
#include "..\Core\Main\main.h"
#include "..\Core\Input\input.h"
#include "Player.h"

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
		this->pos.z += 1.0f;
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_S) == true)
	{
		this->pos.z -= 1.0f;
	}
	if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
	{
		this->pos.x += 1.0f;
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
	{
		this->pos.x -= 1.0f;
	}
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
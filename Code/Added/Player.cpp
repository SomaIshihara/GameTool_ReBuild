//==========================================
//
//�v���C���[�v���O����[Player.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\Core\Main\main.h"
#include "..\Core\Input\input.h"
#include "Player.h"

#define PLAYER_MOVE_SPEED	(1.5f)	//�ړ����x

//========================
//�R���X�g���N�^
//========================
Player::Player()
{

}

//========================
//�f�X�g���N�^
//========================
Player::~Player()
{

}

//========================
//�X�V����
//========================
void Player::Update(void)
{
	//�L�[�{�[�h�̏��擾
	if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_W) == true)
	{
		//�p�x�w��
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

		//�ʒu�w��
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_S) == true)
	{
		//�p�x�w��
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

		//�ʒu�w��
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
	{
		//�p�x�w��
		this->rot.y = -0.5f * D3DX_PI;

		//�ʒu�w��
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
	{
		//�p�x�w��
		this->rot.y = 0.5f * D3DX_PI;

		//�ʒu�w��
		this->pos.x -= sinf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->pos.z -= cosf(this->rot.y) * PLAYER_MOVE_SPEED;
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else
	{
		this->SetMotion(MOTIONTYPE_HOGE);
	}

	//���[�V�����X�V
	this->UpdateMotion();
}

//========================
//�`�揈��
//========================
void Player::Draw(void)
{
	//���}�g������
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&this->mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->rot.y, this->rot.x, this->rot.z);
	D3DXMatrixMultiply(&this->mtxWorld, &this->mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, this->pos.x, this->pos.y, this->pos.z);
	D3DXMatrixMultiply(&this->mtxWorld, &this->mtxWorld, &mtxTrans);

	DrawMotionModel(&this->mtxWorld);
}
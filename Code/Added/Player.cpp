//==========================================
//
//�v���C���[�v���O����[Player.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\Core\Main\main.h"
#include "..\Core\Input\input.h"
#include "Player.h"

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
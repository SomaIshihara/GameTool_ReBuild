//==========================================
//
//�v���C���[�v���O����[Player.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\Core\Main\main.h"
#include "..\Core\Input\input.h"
#include "Player.h"
#include "..\Mathysics\Culc\Culc.h"

#define PLAYER_MOVE_SPEED	(1.5f)	//�ړ����x

//�p�x
#define ROT_WD	(-0.75f * D3DX_PI)
#define ROT_WA	(0.75f * D3DX_PI)
#define ROT_W	(1.0f * D3DX_PI)
#define ROT_SD	(-0.25f * D3DX_PI)
#define ROT_SA	(0.25f * D3DX_PI)
#define ROT_S	(0.0f * D3DX_PI)
#define ROT_D	(-0.5f * D3DX_PI)
#define ROT_A	(0.5f * D3DX_PI)

//�v���g�^�C�v�錾
void SetPos(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRot);

//========================
//�R���X�g���N�^
//========================
cPlayer::cPlayer()
{

}

//========================
//�f�X�g���N�^
//========================
cPlayer::~cPlayer()
{

}

//========================
//�X�V����
//========================
void cPlayer::Update(void)
{
	//�L�[�{�[�h�̏��擾
	if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_W) == true)
	{
		//�p�x�w��
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

		//�ʒu�w��
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_S) == true)
	{
		//�p�x�w��
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

		//�ʒu�w��
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_D) == true)
	{
		//�p�x�w��
		this->m_player.rot.y = FIX_ROT(ROT_D - this->m_pCamera->rot.y);

		//�ʒu�w��
		SetPos(&this->m_player.pos, &this->m_player.rot);
		this->SetMotion(MOTIONTYPE_HUGA);
	}
	else if (cKeyboard::GetKeyboard(INPUTTYPE_PRESS, DIK_A) == true)
	{
		//�p�x�w��
		this->m_player.rot.y = FIX_ROT(ROT_A - this->m_pCamera->rot.y);

		//�ʒu�w��
		SetPos(&this->m_player.pos, &this->m_player.rot);
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
void cPlayer::Draw(void)
{
	//���}�g������
	D3DXMATRIX mtxRot, mtxTrans;

	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&this->m_player.mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, this->m_player.rot.y, this->m_player.rot.x, this->m_player.rot.z);
	D3DXMatrixMultiply(&this->m_player.mtxWorld, &this->m_player.mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, this->m_player.pos.x, this->m_player.pos.y, this->m_player.pos.z);
	D3DXMatrixMultiply(&this->m_player.mtxWorld, &this->m_player.mtxWorld, &mtxTrans);

	DrawMotionModel(&this->m_player.mtxWorld);
}

//========================
//�v���C���[�̎擾����
//========================
Player *cPlayer::GetPlayer(void)
{
	return &this->m_player;
}

//========================
//�����N�p�J�����̎擾����
//========================
Camera **cPlayer::GetLinkCamera(void)
{
	return &this->m_pCamera;
}

//========================
//�v���C���[�̈ʒu�ݒ菈��
//========================
void SetPos(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pRot)
{
	pPos->x -= sinf(pRot->y) * PLAYER_MOVE_SPEED;
	pPos->z -= cosf(pRot->y) * PLAYER_MOVE_SPEED;
}
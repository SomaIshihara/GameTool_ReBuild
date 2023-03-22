//==========================================
//
//���C�g�֌W�v���O����[light.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "cLight.h"

//========================
//�R���X�g���N�^
//========================
cLight::cLight()
{
	//�ԍ�����U��
	this->m_thisLightNum = cLight::m_allLightNum;

	//���C�g�����Z
	cLight::m_allLightNum++;
}

//========================
//�f�X�g���N�^
//========================
cLight::~cLight()
{

}

//========================
//�ݒ菈��
//========================
void cLight::SetLight(D3DLIGHTTYPE type,D3DCOLORVALUE col,D3DXVECTOR3 vecDir)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//���C�g���N���A
	ZeroMemory(&this->m_light, sizeof(D3DLIGHT9));

	//���C�g��ސݒ�
	this->m_light.Type = type;

	//���C�g�g�U���ݒ�
	this->m_light.Diffuse = col;

	//���C�g�̕���
	D3DXVec3Normalize(&vecDir, &vecDir);

	this->m_light.Direction = vecDir;

	//���C�g�ݒ�
	pDevice->SetLight(this->m_thisLightNum, &this->m_light);

	//���C�g�L����
	pDevice->LightEnable(this->m_thisLightNum, TRUE);
}

//========================
//�L���E����������
//========================
void cLight::EnableLight(bool bEnable)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	
	//���C�g�L���E������
	pDevice->LightEnable(0, bEnable ? TRUE : FALSE);
}
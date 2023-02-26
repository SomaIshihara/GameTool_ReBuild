//==========================================
//
//���C�g�v���O�����̃w�b�_[cLight.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_LIGHT_H_
#define _CLASS_LIGHT_H_

#include "main.h"

class cLight
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	cLight();
	~cLight();

	//�ݒ�
	void SetLight(D3DLIGHTTYPE type, D3DCOLORVALUE col, D3DXVECTOR3 vecDir);

	//�L���E�������؊���
	void EnableLight(bool bEnable);
private:
	//���C�g���
	D3DLIGHT9 m_light;

	//���̃J�����̔ԍ�
	int m_thisLightNum;

	//�J������
	static int m_allLightNum;
};

int cLight::m_allLightNum = 0;

#endif // !_LIGHT_H_

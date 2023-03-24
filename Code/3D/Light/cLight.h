//==========================================
//
//���C�g�v���O�����̃w�b�_[cLight.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_LIGHT_H_
#define _CLASS_LIGHT_H_

#include "..\..\Core\Main\main.h"

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

	//�J������
	static int m_allLightNum;
private:
	//���C�g���
	D3DLIGHT9 m_light;

	//���̃J�����̔ԍ�
	int m_thisLightNum;
};

#endif // !_LIGHT_H_

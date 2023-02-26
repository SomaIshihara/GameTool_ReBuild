//==========================================
//
//�J�����v���O�����̃w�b�_[cCamera.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_CAMERA_H_
#define _CLASS_CAMERA_H_

#include "main.h"

//�J�����\����
typedef struct
{
	D3DXVECTOR3 posV;			//���_
	D3DXVECTOR3 posR;			//�����_
	D3DXVECTOR3 vecU;			//������x�N�g��
	D3DXVECTOR3 rot;			//����
	float fLength;				//����
	D3DXMATRIX mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X
} Camera;

class cCamera
{
public:
	//�R���X�g���N�^�E�f�X�g���N�^
	cCamera();
	~cCamera();

	//�ړ�
	void MoveCamera(float moveX, float moveY);
	void ResetCamera(float fLength, D3DXVECTOR2 posV, D3DXVECTOR3 posR, D3DXVECTOR3 rot);

	//�ݒ�
	void SetCamera(void);

	//�擾
	Camera* GetCamera(void);
private:
	Camera m_camera;
};

//�v���g�^�C�v�錾
Camera *GetCamera(void);

#endif // !_CAMERA_H_

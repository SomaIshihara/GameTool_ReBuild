//==========================================
//
//�v�Z�v���O�����̃w�b�_[Culc.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CULC_H_
#define _CULC_H_

//�}�N��
#define ACCELERATION_GRAVITY	(9.8f)		//�d�͉����x

//�֗��}�N���֐�
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��
#define fatof(x)				(float)atof(x)										//�ʏ��atof����double�^�ŕԂ��Ă���̂�float�L���X�g���s���悤�ɂ�������
#define TASUKIGAKE(ax,az,bx,bz)	((az * bx) - (ax * bz))								//���O�̒ʂ�B����ȏ�̐����͂Ȃ��B
#define PYTHAGORAS(a,b)			sqrtf(powf(a,2) + powf(b,2))						//�O�����̒藝
#define CONVERT_FPS(x)			(int)(x * MAX_FPS)									//�b����FPS�ɕϊ�

//�v���g�^�C�v�錾
void UpdateCulc(void);

#endif // !_BILLBOARD_H_

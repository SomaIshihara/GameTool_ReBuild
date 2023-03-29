//==========================================
//
//�������郂�f���v���O�����̃w�b�_[cMotionModel.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _MOTION_MODEL_H_
#define _MOTION_MODEL_H_

#include "../../Core/Main/main.h"
#include "../../Resource/Model/cModel.h"

#define MAX_MOTION_MODEL	(10)	//�������f���Ɏg����

//���[�V�����̎��
typedef enum
{
	MOTIONTYPE_HOGE = 0,	//�ق�
	MOTIONTYPE_HUGA,		//�ӂ�
	MOTIONTYPE_PIYO,		//�҂�
	MOTIONTYPE_MAX
} MOTIONTYPE;

//�L�[�\����
typedef struct
{
	float m_PosX;	//�ʒuX
	float m_PosY;	//�ʒuY
	float m_PosZ;	//�ʒuZ
	float m_RotX;	//����X
	float m_RotY;	//����Y
	float m_RotZ;	//����Z
} KEY;

//�L�[���̍\����
typedef struct
{
	int m_Frame;					//�Đ��t���[��
	KEY m_aKey[MAX_MOTION_MODEL];	//���f���̃L�[�v�f
} KEY_INFO;

//���[�V������ԍ\����
typedef struct
{
	bool m_Loop;				//���[�v���邩
	int m_numKey;				//�L�[����
	KEY_INFO m_aKeyInfo[16];	//�L�[�̏��i16�͓K�X�ς��āj
} MOTION_INFO;

//���[�V�����\����
typedef struct
{
	MOTIONTYPE m_motionType;	//���[�V�������
	int m_nowKey;				//���݂̃L�[No.
	int m_counterMotion;		//���[�V�����J�E���^�[
} Motion;

//�������f��
class cMotionModel
{
public:
	cMotionModel();
	virtual ~cMotionModel();
	void LoadMotionModel(const char* pPath);
	void DrawMotionModel(D3DXMATRIX *mtxBace);
private:
	Motion m_motion;
	MOTION_INFO m_motionInfo[MOTIONTYPE_MAX];
	cModel m_model[MAX_MOTION_MODEL];
	float m_move;	//�ړ���
	float m_jump;	//�W�����v��
	float m_radius;	//���a�i���g�p�j
	int m_numParts;	//�p�[�c��
};

#endif // !_MOTION_MODEL_H_
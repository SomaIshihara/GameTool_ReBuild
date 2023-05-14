//==========================================
//
//���f���v���O�����̃w�b�_[cModel.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _CLASS_MODEL_H_
#define _CLASS_MODEL_H_

#include "..\..\Core\Main\main.h"

//========================
//���f���P��
//========================
class CModel
{
public:
	struct ModelStruct
	{
		//�`��֌W
		LPD3DXMESH pMesh = NULL;				//���b�V��
		LPD3DXBUFFER pBuffMat = NULL;			//�}�e���A���|�C���^
		DWORD dwNumMatModel = 0;				//�}�e��
		LPDIRECT3DTEXTURE9 apTexture[16] = {};	//�e�N�X�`���|�C���^
		D3DXMATRIX mtxWorld;					//���[���h�}�g��

		//�ύX�\
		D3DXVECTOR3 posOffset = INIT_ZERO;	//�ʒu�i�I�t�Z�b�g�j
		D3DXVECTOR3 rotOffset = INIT_ZERO;	//�����i�I�t�Z�b�g�j
		int m_IdxModelParent = -1;			//�e���f���C���f�b�N�X

		//�g�p�L��
		bool m_bUse = false;				//�g�p�̗L��
	};

	CModel();
	~CModel();
	virtual void Init(void);
	virtual void Uninit(void);

	virtual void Create(const char* pPath);
	virtual void Release(void);

	void DrawModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXMATRIX *pMtxBace, D3DXMATRIX *mtxParent = NULL);
	void SetModelSetup(ModelStruct modelstr);
private:
	ModelStruct m_cModelStr;
};

//========================
//���[�V�����t�����f��
//========================
class cMotionModel : public CModel
{
public:
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
		int m_Frame;				//�Đ��t���[��
		KEY *m_aKey;				//���f���̃L�[�v�f�i�p�[�c���Ɠ��������I�m�ہj
	} KEY_INFO;

	//���[�V������ԍ\����
	typedef struct
	{
		bool m_Loop;				//���[�v���邩
		int m_numKey;				//�L�[����
		KEY_INFO *m_aKeyInfo;		//�L�[�̏��i�L�[�����Ɠ��������I�m�ہj
	} MOTION_INFO;

	//���[�V�����\����
	typedef struct
	{
		MOTIONTYPE m_motionType;	//���[�V�������
		int m_nowKey;				//���݂̃L�[No.
		int m_counterMotion;		//���[�V�����J�E���^�[
	} Motion;



	cMotionModel();
	~cMotionModel();

	void Init(void);
	void Uninit(void);

	void Create(const char* pPath);
	void Release(void);

	void UpdateMotion(void);
	void SetMotion(MOTIONTYPE type);

	void SetParent(D3DXMATRIX mtx);
	void DrawMotionModel(D3DXMATRIX *mtxBace);
private:
	CModel *m_model;
	Motion m_motion;
	MOTION_INFO m_motionInfo[MOTIONTYPE_MAX];
	D3DXVECTOR3 *m_motionPos;
	D3DXVECTOR3 *m_motionRot;
	float m_move;	//�ړ���
	float m_jump;	//�W�����v��
	float m_radius;	//���a�i���g�p�j
	int m_numParts;	//�p�[�c��

	//���f����
	int m_numModel;
};

#endif
//==========================================
//
//�����蔻��v���O�����̃w�b�_[collision.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "..\..\Core\Main\main.h"

//�����蔻��͈͍\����
typedef struct
{
	D3DXVECTOR3 pos0, pos1, pos2, pos3;
} CollisionPos;

typedef struct
{
	CollisionPos m_collPos;		//�����蔻��Ɏg���_
	D3DXVECTOR3 m_pos;			//���S�ʒu
	D3DXVECTOR3 m_rot;			//�����蔻��̌���
	D3DXVECTOR3 m_vecNor;		//�@���x�N�g��
} Collision;

//�̓����蔻��
class cCollision
{
public:
	void SetCollision(D3DXVECTOR3 rot, CollisionPos collPos);
	bool CollisionCheck(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *posCloss = NULL);
private:
	Collision m_coll;
};

//���̓����蔻��
class cBoxCollider
{
public:
	void SetBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth);
private:
	cCollision m_collPlane[6];
};

//�v���g�^�C�v�錾
#if 0
bool CollisionPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth);										//�v���C���[���m�̏Փ˔���
bool CollisionHipDropPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth, float fRadius, float fPower);	//�q�b�v�h���b�v���̏Փ˔���
bool CollisionFence(Player *pPlayer, float fFenceWidth, float fPlayerHeight, float fFenceDepth, float fenceSize);		//�t�F���X�̏Փˏ���
#endif

#endif // !_COLLISION_H_

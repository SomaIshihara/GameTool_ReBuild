//==========================================
//
//�����蔻��v���O����[collision.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "collision.h"

//�v���g
void GenerateCollision(CollisionPos *pGeneratedColl, CollisionPos rawColl, D3DXVECTOR3 pos, D3DXVECTOR3 rot);
#if 0
void RefrectPlayer(Player *pPlayer, Fence *pFence, float fRate, D3DXVECTOR3 vecLine);
bool HitPlayerToPlayer(Player *pATKPlayer, Player *pHitPlayer, D3DXVECTOR3 collPos, D3DXVECTOR3 vecLine, float fRate);
#endif

#if 0
//========================
//�v���C���[���m�̏Փ˔��菈��
//========================
bool CollisionPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth)
{
	//=pos0~pos3�̐���==================
	// pos3		pos2
	//	�E<-----�E		���:vecLine
	//	�b		��
	//	�b		�b
	//	��		�b
	//	�E----->�E
	// pos0		pos1
	//==================================

	//���_
	CollisionPos collPos;

	//�x�N�g��
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove[2];

	//�v���C���[
	Player *pPlayer = GetPlayer();

	//2��2���_��2
	float fAreaARight[2], fAreaALeft[2], fAreaBRight[2], fAreaBLeft[2];
	float fAreaAUp[2], fAreaADown[2], fAreaBUp[2], fAreaBDown[2];

	//�����f�̈ʒu�l��
	D3DXVECTOR3 posTemp = pATKPlayer->pos +pATKPlayer->move;

	for (int nCntOtherPlayer = 0; nCntOtherPlayer < MAX_USE_GAMEPAD; nCntOtherPlayer++,pPlayer++)
	{
		if (pPlayer !=pATKPlayer)
		{
			//���_�ݒ�
			GenerateCollision(pPlayer->pos,pPlayer->rot, &collPos, fWidth, fDepth);

			//�x�N�g�����߂�
			//move
			for (int nCntCollision = 0; nCntCollision < 2; nCntCollision++)
			{
				vecMove[nCntCollision] = (posTemp + pATKPlayer->faceCollider[nCntCollision]) - (pATKPlayer->posOld + pATKPlayer->faceCollider[nCntCollision]);
			}

			//X
			//�E�����̌v�Z
			vecLineRight = collPos.pos1 - collPos.pos0;
			vecToPosRight = posTemp - collPos.pos0;
			vecToPosOldRight = pATKPlayer->posOld - collPos.pos0;

			//�������̌v�Z
			vecLineLeft = collPos.pos3 - collPos.pos2;
			vecToPosLeft = posTemp - collPos.pos2;
			vecToPosOldLeft = pATKPlayer->posOld - collPos.pos2;

			//Z
			//������̌v�Z
			vecLineUp = collPos.pos2 - collPos.pos1;
			vecToPosUp = posTemp - collPos.pos1;
			vecToPosOldUp = pATKPlayer->posOld - collPos.pos1;
			//�������̌v�Z
			vecLineDown = collPos.pos0 - collPos.pos3;
			vecToPosDown = posTemp - collPos.pos3;
			vecToPosOldDown = pATKPlayer->posOld - collPos.pos3;

			//�����蔻��{��
			for (int nCntCollision = 0; nCntCollision < 2; nCntCollision++)
			{
				//X
				//�ʐϋ��߂�
				fAreaARight[nCntCollision] = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaALeft[nCntCollision] = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBRight[nCntCollision] = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBLeft[nCntCollision] = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);

				//����AND�͈͓�
				if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
				{
					if (fAreaARight[nCntCollision] / fAreaBRight[nCntCollision] >= 0.0f && fAreaARight[nCntCollision] / fAreaBRight[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaARight[nCntCollision] / fAreaBRight[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos0, vecLineRight, fRate);
							break;
						}
					}
				}
				else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
				{
					if (fAreaALeft[nCntCollision] / fAreaBLeft[nCntCollision] >= 0.0f && fAreaALeft[nCntCollision] / fAreaBLeft[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaALeft[nCntCollision] / fAreaBLeft[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos2, vecLineLeft, fRate);
							break;
						}
					}
				}

				//Z
				//�ʐϋ��߂�
				fAreaAUp[nCntCollision] = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaADown[nCntCollision] = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBUp[nCntCollision] = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);
				fAreaBDown[nCntCollision] = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove[nCntCollision].x, vecMove[nCntCollision].z);

				//����AND�͈͓�
				if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
				{
					if (fAreaAUp[nCntCollision] / fAreaBUp[nCntCollision] >= 0.0f && fAreaAUp[nCntCollision] / fAreaBUp[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaAUp[nCntCollision] / fAreaBUp[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos1, vecLineUp, fRate);
							break;
						}
					}
				}
				else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
				{
					if (fAreaADown[nCntCollision] / fAreaBDown[nCntCollision] >= 0.0f && fAreaADown[nCntCollision] / fAreaBDown[nCntCollision] <= 1.0f)
					{
						if (posTemp.y >= pPlayer->pos.y && posTemp.y <= pPlayer->pos.y + fHeight)
						{
							float fRate = fAreaADown[nCntCollision] / fAreaBDown[nCntCollision];
							return HitPlayerToPlayer(pATKPlayer, pPlayer, collPos.pos3, vecLineDown, fRate);
							break;
						}
					}
				}
			}
		}
	}
	return false;
}

//========================
//�q�b�v�h���b�v���̏Փˏ���
//========================
bool CollisionHipDropPP(Player *pATKPlayer, float fWidth, float fHeight, float fDepth, float fRadius, float fPower)
{
	//=pos0~pos2�̐���==================
	//
	//		�Eg_ap[nPNum].posOld
	//		��
	//		�Eg_ap[nPNum].pos
	// pos1		pos0
	//	�E<-----�E		���:vecLine
	//	�b
	//	�b
	//	��
	//�@�E
	// pos2
	//==================================

	//���_
	CollisionPos collPos;

	//�x�N�g��
	D3DXVECTOR3 vecLineX, vecToPosX, vecToPosOldX;
	D3DXVECTOR3 vecLineZ, vecToPosZ, vecToPosOldZ;
	D3DXVECTOR3 vecMove;

	//�v���C���[
	Player *pPlayer = GetPlayer();

	//�ʐ�
	float fAreaAX, fAreaBX, fAreaAZ, fAreaBZ;

	//�����f�̈ʒu�l��
	D3DXVECTOR3 posTemp = pATKPlayer->pos + pATKPlayer->move;

	for (int nCntOtherPlayer = 0; nCntOtherPlayer < MAX_USE_GAMEPAD; nCntOtherPlayer++)
	{
		if (pPlayer != pATKPlayer)
		{
			//���_�ݒ�
			GenerateCollision(pPlayer->pos, pPlayer->rot, &collPos, fWidth, fDepth);

			//�x�N�g�����߂�
			//move
			vecMove = posTemp - pATKPlayer->posOld;

			//X
			vecLineX = collPos.pos1 - collPos.pos0;
			vecToPosX = posTemp - collPos.pos0;
			vecToPosOldX = pATKPlayer->posOld - collPos.pos0;

			//Z
			vecLineZ = collPos.pos2 - collPos.pos1;
			vecToPosZ = posTemp - collPos.pos1;
			vecToPosOldZ = pATKPlayer->posOld - collPos.pos1;

			//�����蔻��{��
			//X
			//�ʐϋ��߂�
			fAreaAX = TASUKIGAKE(vecToPosX.x, vecToPosX.y, vecMove.x, vecMove.y);
			fAreaBX = TASUKIGAKE(vecLineX.x, vecLineX.y, vecMove.x, vecMove.y);
			fAreaAZ = TASUKIGAKE(vecToPosZ.z, vecToPosZ.y, vecMove.z, vecMove.y);
			fAreaBZ = TASUKIGAKE(vecLineZ.z, vecLineZ.y, vecMove.z, vecMove.y);
			//����AND�͈͓�
			float fHeight = posTemp.y - pPlayer->pos.y;
			if (fHeight <= fHeight)
			{
				float fRadius = PYTHAGORAS(pPlayer->pos.x - posTemp.x,
					pPlayer->pos.z - posTemp.z);

				if (fRadius <= fRadius)
				{
					//�ړ��ʌv�Z
					float fAngleHipDrop = atan2f(pPlayer->pos.x - posTemp.x,
						pPlayer->pos.z - posTemp.z);
					pPlayer->move.x = sinf(fAngleHipDrop) * fPower;
					pPlayer->move.z = -cosf(fAngleHipDrop) * fPower;

					//������Ɣ�΂�
					pPlayer->moveV0.y = fPower;
					pPlayer->jumpTime = 0;

					//�U�����ꂽ�����ɂ���
					pPlayer->nLastHitPlayer = pATKPlayer->nPlayerNum;
				}
			}
		}
	}
	return false;
}

//========================
//�t�F���X�̏Փˏ����i�ړ��������ɍs���j
//========================
bool CollisionFence(Player *pPlayer, float fFenceWidth, float fPlayerHeight, float fFenceDepth, float fenceSize)
{
	//���_
	CollisionPos collPos;

	//�x�N�g��
	D3DXVECTOR3 vecLineRight, vecToPosRight, vecToPosOldRight;
	D3DXVECTOR3 vecLineLeft, vecToPosLeft, vecToPosOldLeft;
	D3DXVECTOR3 vecLineUp, vecToPosUp, vecToPosOldUp;
	D3DXVECTOR3 vecLineDown, vecToPosDown, vecToPosOldDown;
	D3DXVECTOR3 vecMove;

	//�t�F���X
	Fence *pFence = GetFence();

	//2��2���_��2
	float fAreaARight, fAreaALeft, fAreaBRight, fAreaBLeft;
	float fAreaAUp, fAreaADown, fAreaBUp, fAreaBDown;

	//�����f�̈ʒu�l��
	D3DXVECTOR3 posTemp = pPlayer->pos + pPlayer->move;

	for (int nCntFence = 0; nCntFence < MAX_USE_FENCE; nCntFence++, pFence++)
	{
		//���_�ݒ�
		GenerateCollision(pFence->pos, pFence->rot, &collPos, fFenceWidth * fenceSize, fFenceDepth * fenceSize);

		//�x�N�g�����߂�
		//move
		vecMove = posTemp - pPlayer->posOld;

		//X
		//�E�����̌v�Z
		vecLineRight = collPos.pos1 - collPos.pos0;
		vecToPosRight = posTemp - collPos.pos0;
		vecToPosOldRight = pPlayer->posOld - collPos.pos0;

		//�������̌v�Z
		vecLineLeft = collPos.pos3 - collPos.pos2;
		vecToPosLeft = posTemp - collPos.pos2;
		vecToPosOldLeft = pPlayer->posOld - collPos.pos2;

		//Z
		//������̌v�Z
		vecLineUp = collPos.pos2 - collPos.pos1;
		vecToPosUp = posTemp - collPos.pos1;
		vecToPosOldUp = pPlayer->posOld - collPos.pos1;
		//�������̌v�Z
		vecLineDown = collPos.pos0 - collPos.pos3;
		vecToPosDown = posTemp - collPos.pos3;
		vecToPosOldDown = pPlayer->posOld - collPos.pos3;

		//�����蔻��{��
		//X
		//�ʐϋ��߂�
		fAreaARight = TASUKIGAKE(vecToPosRight.x, vecToPosRight.z, vecMove.x, vecMove.z);
		fAreaALeft = TASUKIGAKE(vecToPosLeft.x, vecToPosLeft.z, vecMove.x, vecMove.z);
		fAreaBRight = TASUKIGAKE(vecLineRight.x, vecLineRight.z, vecMove.x, vecMove.z);
		fAreaBLeft = TASUKIGAKE(vecLineLeft.x, vecLineLeft.z, vecMove.x, vecMove.z);

		//����AND�͈͓�
		if ((vecLineRight.z * vecToPosRight.x) - (vecLineRight.x * vecToPosRight.z) <= 0.0f && (vecLineRight.z * vecToPosOldRight.x) - (vecLineRight.x * vecToPosOldRight.z) >= 0.0f)
		{
			if (fAreaARight / fAreaBRight >= 0.0f && fAreaARight / fAreaBRight <= 1.0f)
			{
				//�������߂�
				float fRate = fAreaARight / fAreaBRight;

				//���ˏ���
				RefrectPlayer(pPlayer, pFence, fRate, vecLineRight);

				//�I��
				return true;
			}
		}
		else if ((vecLineLeft.z * vecToPosLeft.x) - (vecLineLeft.x * vecToPosLeft.z) <= 0.0f && (vecLineLeft.z * vecToPosOldLeft.x) - (vecLineLeft.x * vecToPosOldLeft.z) >= 0.0f)
		{
			if (fAreaALeft / fAreaBLeft >= 0.0f && fAreaALeft / fAreaBLeft <= 1.0f)
			{
				//�������߂�
				float fRate = fAreaALeft / fAreaBLeft;

				//���ˏ���
				RefrectPlayer(pPlayer, pFence, fRate, vecLineLeft);

				//�I��
				return true;
			}
		}

		//Z
		//�ʐϋ��߂�
		fAreaAUp = TASUKIGAKE(vecToPosUp.x, vecToPosUp.z, vecMove.x, vecMove.z);
		fAreaADown = TASUKIGAKE(vecToPosDown.x, vecToPosDown.z, vecMove.x, vecMove.z);
		fAreaBUp = TASUKIGAKE(vecLineUp.x, vecLineUp.z, vecMove.x, vecMove.z);
		fAreaBDown = TASUKIGAKE(vecLineDown.x, vecLineDown.z, vecMove.x, vecMove.z);

		//����AND�͈͓�
		if ((vecLineUp.z * vecToPosUp.x) - (vecLineUp.x * vecToPosUp.z) <= 0.0f && (vecLineUp.z * vecToPosOldUp.x) - (vecLineUp.x * vecToPosOldUp.z) >= 0.0f)
		{
			if (fAreaAUp / fAreaBUp >= 0.0f && fAreaAUp / fAreaBUp <= 1.0f)
			{
				//�������߂�
				float fRate = fAreaAUp / fAreaBUp;

				//���ˏ���
				RefrectPlayer(pPlayer, pFence, fRate, vecLineUp);

				//�I��
				return true;
			}
		}
		else if ((vecLineDown.z * vecToPosDown.x) - (vecLineDown.x * vecToPosDown.z) <= 0.0f && (vecLineDown.z * vecToPosOldDown.x) - (vecLineDown.x * vecToPosOldDown.z) >= 0.0f)
		{
			if (fAreaADown / fAreaBDown >= 0.0f && fAreaADown / fAreaBDown <= 1.0f)
			{
				//�������߂�
				float fRate = fAreaADown / fAreaBDown;

				//���ˏ���
				RefrectPlayer(pPlayer, pFence, fRate, vecLineDown);

				//�I��
				return true;
			}
		}
	}
	return false;
}
#endif

//�����蔻�蒸�_��
typedef enum
{//M = �}�C�i�X, P = �v���X
	BOXCOLLPOINT_MXMYMZ = 0,
	BOXCOLLPOINT_PXMYMZ,
	BOXCOLLPOINT_MXMYPZ,
	BOXCOLLPOINT_PXMYPZ,
	BOXCOLLPOINT_MXPYMZ,
	BOXCOLLPOINT_PXPYMZ,
	BOXCOLLPOINT_MXPYPZ,
	BOXCOLLPOINT_PXPYPZ,
	BOXCOLLPOINT_MAX
} BOXCOLLPOINT;

const BOXCOLLPOINT c_aBoxCollPoint[6][4] = 
{
	{ BOXCOLLPOINT_MXPYMZ ,BOXCOLLPOINT_PXPYMZ ,BOXCOLLPOINT_PXPYPZ ,BOXCOLLPOINT_MXPYPZ },	//���
	{ BOXCOLLPOINT_MXMYPZ ,BOXCOLLPOINT_MXMYMZ ,BOXCOLLPOINT_MXPYMZ ,BOXCOLLPOINT_MXPYPZ },	//������
	{ BOXCOLLPOINT_PXMYMZ ,BOXCOLLPOINT_PXMYPZ ,BOXCOLLPOINT_PXPYPZ ,BOXCOLLPOINT_PXPYMZ },	//�E����
	{ BOXCOLLPOINT_MXMYMZ ,BOXCOLLPOINT_PXMYMZ ,BOXCOLLPOINT_PXPYMZ ,BOXCOLLPOINT_MXPYMZ },	//�O����
	{ BOXCOLLPOINT_PXMYPZ ,BOXCOLLPOINT_MXMYPZ ,BOXCOLLPOINT_MXPYPZ ,BOXCOLLPOINT_PXPYPZ },	//������
	{ BOXCOLLPOINT_MXMYMZ ,BOXCOLLPOINT_PXMYMZ ,BOXCOLLPOINT_PXMYPZ ,BOXCOLLPOINT_MXMYPZ }	//����
};

//*********************************************
//�̓����蔻��
//*********************************************
//========================
//�����蔻�萶��
//========================
void cCollision::SetCollision(D3DXVECTOR3 rot, CollisionPos collPos)
{
	//memo-------------------------------------------------------------
	//		�@	��
	//		�@�E-|------�E
	//		�^	 |	  �^
	//	  �^		�^
	//	�E--------�E
	//
	//	���ꂪ0.0f,0.0f,0.0f ����ɍ��킹�ď����@���x�N�g���ݒ肵�Ă���
	//memo-------------------------------------------------------------

	//���[�J���ϐ�
	D3DXVECTOR3 vecNor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxRot;

	//�����蔻�蒸�_�ݒ�
	GenerateCollision(
		&this->m_coll.m_collPos, 
		collPos, 
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),	//��
		rot);

	//�p�x�ݒ�
	this->m_coll.m_rot = rot;

	//�P�ʍs��쐬
	D3DXMatrixIdentity(&mtxRot);

	//�@���x�N�g������
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXVec3TransformCoord(&this->m_coll.m_vecNor, &vecNor, &mtxRot);
}

//========================
//�����蔻��m�F
//========================
bool cCollision::CollisionCheck(D3DXVECTOR3 pos, D3DXVECTOR3 posOld, D3DXVECTOR3 *posCloss)
{
	return false;
}

//*********************************************
//���̓����蔻��
//*********************************************
//========================
//�����蔻�萶��
//========================
void cBoxCollider::SetBoxCollider(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, float fDepth)
{
	//���_����
	D3DXVECTOR3 posPoint[BOXCOLLPOINT_MAX];

	for (int nCntPoint = 0; nCntPoint < 8; nCntPoint++)
	{
		posPoint[nCntPoint] = D3DXVECTOR3(
			pos.x + ((fWidth / 2) * ((nCntPoint % 2 == 0) ? -1 : 1)),
			pos.y + ((fHeight / 2) * ((nCntPoint / 4 == 0) ? -1 : 1)),
			pos.z + ((fDepth / 2) * (((nCntPoint / 2) % 2 == 0) ? -1 : 1)));
	}

	for (int nCntCollider = 0; nCntCollider < 6; nCntCollider++)
	{
		CollisionPos collPos = CollisionPos{
			posPoint[c_aBoxCollPoint[nCntCollider][0]],
			posPoint[c_aBoxCollPoint[nCntCollider][1]],
			posPoint[c_aBoxCollPoint[nCntCollider][2]],
			posPoint[c_aBoxCollPoint[nCntCollider][3]]};

		this->m_collPlane[nCntCollider].SetCollision(rot, collPos);
	}
}


//*********************************************
//CPP���̂ݎg�p
//*********************************************
//========================
//�����蔻��p�_����
//========================
void GenerateCollision(CollisionPos *pGeneratedColl, CollisionPos rawColl, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�e���_�����߂�̂ɕK�v�ȕϐ�
	D3DXMATRIX mtxWorld;	//��]�̃x�[�X�ƂȂ郏�[���h�}�g��
	D3DXMATRIX mtxRot;		//��]�s��
	D3DXMATRIX mtxTrans;	//���ׂĕϊ���̍s��
	D3DXVECTOR3 vtxTrans;	//�ϊ���̓_

	//-mtx----------------------------------------------------------------------------------------------------------------------------
	//��]�s������
	D3DXMatrixIdentity(&mtxWorld);

	//�������f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixRotationY(&mtxRot, rot.y);
	D3DXMatrixMultiply(&mtxWorld, &mtxRot, &mtxWorld);

	//�ʒu���f
	mtxWorld._41 = pos.x;
	mtxWorld._42 = pos.y;
	mtxWorld._43 = pos.z;

	//-mtx----------------------------------------------------------------------------------------------------------------------------

	//-pos0---------------------------------------------------------------------------------------------------------------------------
	//��]�s������Ƃɒ��_����]����
	//�x�[�X���R�s�[
	mtxTrans = mtxWorld;

	//0�x�̂Ƃ��̓_��u��
	D3DXVECTOR3 vtxPos = rawColl.pos0;

	//��]�s��Ƃ������킹��
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	pGeneratedColl->pos0.x = vtxTrans.x;
	pGeneratedColl->pos0.y = vtxTrans.y;
	pGeneratedColl->pos0.z = vtxTrans.z;
	//-pos0---------------------------------------------------------------------------------------------------------------------------

	//-pos1---------------------------------------------------------------------------------------------------------------------------
	//��]�s������Ƃɒ��_����]����
	//�x�[�X���R�s�[
	mtxTrans = mtxWorld;

	//0�x�̂Ƃ��̓_��u��
	vtxPos = rawColl.pos1;

	//��]�s��Ƃ������킹��
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	//�ϊ���̓_�̏ꏊ����
	pGeneratedColl->pos1.x = vtxTrans.x;
	pGeneratedColl->pos1.y = vtxTrans.y;
	pGeneratedColl->pos1.z = vtxTrans.z;
	//-pos1---------------------------------------------------------------------------------------------------------------------------

	//-pos2---------------------------------------------------------------------------------------------------------------------------
	//��]�s������Ƃɒ��_����]����
	//�x�[�X���R�s�[
	mtxTrans = mtxWorld;

	//0�x�̂Ƃ��̓_��u��
	vtxPos = rawColl.pos2;

	//��]�s��Ƃ������킹��
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	//�ϊ���̓_�̏ꏊ����
	pGeneratedColl->pos2.x = vtxTrans.x;
	pGeneratedColl->pos2.y = vtxTrans.y;
	pGeneratedColl->pos2.z = vtxTrans.z;
	//-pos2---------------------------------------------------------------------------------------------------------------------------

	//-pos3---------------------------------------------------------------------------------------------------------------------------
	//��]�s������Ƃɒ��_����]����
	//�x�[�X���R�s�[
	mtxTrans = mtxWorld;

	//0�x�̂Ƃ��̓_��u��
	vtxPos = rawColl.pos3;

	//��]�s��Ƃ������킹��
	D3DXVec3TransformCoord(&vtxTrans, &vtxPos, &mtxTrans);

	//�ϊ���̓_�̏ꏊ����
	pGeneratedColl->pos3.x = vtxTrans.x;
	pGeneratedColl->pos3.y = vtxTrans.y;
	pGeneratedColl->pos3.z = vtxTrans.z;
	//-pos3---------------------------------------------------------------------------------------------------------------------------
}

#if 0
//========================
//���ˏ���
//========================
void RefrectPlayer(Player *pPlayer, Fence *pFence, float fRate, D3DXVECTOR3 vecLine)
{
	//�x�N�g���̊������߂�
	//�Ƃ肠����������Ă��钸�_�����߂�
	D3DXVECTOR3 posCross = vecLine / fRate;

	//���_�����ƂɃx�N�g�����߂�
	D3DXVECTOR3 vecCross = pPlayer->pos - posCross;

	//���߂��x�N�g�������ƂɊ������߂�
	float fRateRemaining = D3DXVec3Length(&vecCross) / D3DXVec3Length(&pPlayer->move);


	//��U�i�߂邾���i�߂�
	pPlayer->pos = posCross;


	//�ړ��ʂ̃x�N�g������
	D3DXVECTOR3 vecMove = pPlayer->move;

	//�t�F���X�̖@���x�N�g�������߂�
	D3DXVECTOR3 vecNor;
	vecNor.x = -sinf(pFence->rot.y);
	vecNor.y = 0.0f;
	vecNor.z = -cosf(pFence->rot.y);

	//�Ƃ肠�������K��
	D3DXVec3Normalize(&vecMove, &vecMove);
	D3DXVec3Normalize(&vecNor, &vecNor);

	//�h�b�g�ρi���ρj���߂�
	float fDot = D3DXVec3Dot(&vecMove, &vecNor);

	//���˃x�N�g�������߂�
	D3DXVECTOR3 vecRefrect = vecMove - 2 * fDot * vecNor;

	//���ۂ̈ړ��ʂ�ݒ�
	float fVecLength = D3DXVec3Length(&pPlayer->move);
	vecRefrect *= fVecLength / fRateRemaining;

	//�����ƈړ�����
	pPlayer->pos += vecRefrect;
}

//========================
//�����������̏����i�Ԃ�l�͓����Ă��邩�ǂ����j
//========================
bool HitPlayerToPlayer(Player *pATKPlayer, Player *pHitPlayer, D3DXVECTOR3 collPos, D3DXVECTOR3 vecLine, float fRate)
{
	bool bMove = false;
	if (fabsf(pATKPlayer->move.x) > 0.0f || fabsf(pATKPlayer->move.z) > 0.0f)
	{//�����Ă�
		pATKPlayer->nFrameAtkPlayer = pHitPlayer->nPlayerNum;
		pHitPlayer->nLastHitPlayer = pATKPlayer->nPlayerNum;

		bMove = true;
	}
	//1.0f = pushback
	pATKPlayer->pos.x = collPos.x + (vecLine.x * fRate) - sinf(pHitPlayer->rot.y) / D3DX_PI * 1.0f;
	pATKPlayer->pos.z = collPos.z + (vecLine.z * fRate) - cosf(pHitPlayer->rot.y) / D3DX_PI * 1.0f;

	//�����Ă��邩�Ԃ�
	return bMove;
}
#endif
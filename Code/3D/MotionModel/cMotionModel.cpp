//==========================================
//
//�������郂�f���v���O����[cMotionModel.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "cMotionModel.h"
#include "..\..\Core\File\file.h"
#include "..\..\Mathysics\Culc\Culc.h"
#include <stdio.h>
#include <assert.h>

//���[�V�����r���[���[�p�R�[�h
//����
#define CODE_NUM_MODEL			"NUM_MODEL"			//���f����
#define CODE_MODEL_FILENAME		"MODEL_FILENAME"	//���f���̃t�@�C���p�X
#define CODE_CHARACTERSET		"CHARACTERSET"		//�L�����N�^�[���
#define CODE_END_CHARACTERSET	"END_CHARACTERSET"

//�p�[�c�ݒ�
#define CODE_PARTSSET			"PARTSSET"			//�p�[�c�ݒ�J�n
#define CODE_END_PARTSSET		"END_PARTSSET"		//�p�[�c�ݒ�I��

//���[�V�����ݒ�
#define CODE_MOTIONSET			"MOTIONSET"			//���[�V�����ݒ�J�n
#define CODE_END_MOTIONSET		"END_MOTIONSET"		//���[�V�����ݒ�I��
//�L�[�Z�b�g�ݒ�
#define CODE_KEYSET				"KEYSET"			//�L�[�Z�b�g�ݒ�J�n
#define CODE_END_KEYSET			"END_KEYSET"		//�L�[�Z�b�g�ݒ�I��
//�L�[�ݒ�
#define CODE_KEY				"KEY"				//�L�[�ݒ�J�n
#define CODE_END_KEY			"END_KEY"			//�L�[�ݒ�I��

//���[�V�����r���[���[�p�p�����[�^�[
#define CODE_MOVE				"MOVE"				//�ړ���
#define CODE_JUMP				"JUMP"				//�W�����v��
#define CODE_NUM_PARTS			"NUM_PARTS"			//�p�[�c��
#define CODE_INDEX				"INDEX"				//�ԍ�
#define CODE_PARENT				"PARENT"			//�e���f���̔ԍ�
#define CODE_LOOP				"LOOP"				//���[�v���邩�̐ݒ�
#define CODE_NUM_KEY			"NUM_KEY"			//�L�[��
#define CODE_FRAME				"FRAME"				//�t���[����

//�ǂݎ���ԗ�
typedef enum
{
	//����
	READSTAT_MOTION_NONE = 0,	//�������ĂȂ�
	//--���[�V�����r���[���[------------------
	READSTAT_MOTION_CHARACTERSET,
	READSTAT_MOTION_PARTSSET,
	READSTAT_MOTION_MOTIONSET,
	READSTAT_MOTION_KEYSET,
	READSTAT_MOTION_KEY,
	//----------------------------------------
	READSTAT_MOTION_MAX
} READSTAT_MOTION;

//========================
//�R���X�g���N�^
//========================
cMotionModel::cMotionModel()
{
	
}

//========================
//�f�X�g���N�^
//========================
cMotionModel::~cMotionModel()
{
	for (int cntModel = 0; cntModel < MAX_MOTION_MODEL; cntModel++)
	{
		this->m_model[cntModel].~cModel();
	}
}

//========================
//���[�V�����r���[���[�̃t�@�C�����擾
//========================
void cMotionModel::LoadMotionModel(const char *pPath)
{
	FILE *pFile;
	char aCode[MAX_STR_LENGTH];
	char *pSprit;
	bool bRead = false;

	READSTAT_MOTION readstat = READSTAT_MOTION_NONE;
	int counterReadModel = 0;
	int counterSetModel = 0;
	int counterMotionInfo = 0;
	int counterKeyInfo = 0;
	int counterKey = 0;
	int idxPartsSet = 0;

	//���u��
	ModelStruct modelstr;

	//���[�V�������
	//�ǂݍ��݃t�@�C���ݒ�
	pFile = fopen(pPath, "r");

	//�G�z�u�����擾
	if (pFile != NULL)
	{
		while (1)
		{
			fgets(&aCode[0], MAX_STR_LENGTH, pFile);

			//�R�����g�A�E�g�`�F�b�N
			char *pCharPos = strchr(&aCode[0], '#');
			if (pCharPos != nullptr)
			{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
				*pCharPos = '\0';
			}

			//�^�u����
			while (aCode[0] == '\t')
			{
				char aCodeBackup[MAX_STR_LENGTH];
				strcpy(&aCodeBackup[0], &aCode[0]);
				strcpy(&aCode[0], &aCodeBackup[1]);
			}

			//������`�F�b�N
			if (strncmp(&aCode[0], CODE_SCRIPT, sizeof CODE_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��J�n
				bRead = true;
			}
			else if (strncmp(&aCode[0], CODE_END_SCRIPT, sizeof CODE_END_SCRIPT / sizeof(char) - 1) == 0)
			{//�ǂݎ��I��
				bRead = false;
				break;
			}
			else if (aCode[0] == EOF)
			{//EOF��������Ȃ�
				if (feof(pFile))
				{//����A�����EOF��
					bRead = false;
					break;
				}
			}
			else if (bRead == true)
			{//�ǂݎ��
				switch (readstat)
				{
				case READSTAT_MOTION_NONE:	//�����擾
					if (strncmp(&aCode[0], CODE_MODEL_FILENAME, sizeof CODE_MODEL_FILENAME / sizeof(char) - 1) == 0)
					{
						if (counterReadModel < MAX_MOTION_MODEL)
						{
							char aStrPath[MAX_STR_LENGTH];
							pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

							//���
							strcpy(&aStrPath[0], strtok(NULL, " =\n"));
							//�^�u�����������Ă���Ƃ��������
							char *pCharPos = strchr(&aStrPath[0], '\t');
							if (pCharPos != nullptr)
							{//strchr�̕Ԃ�l���ʂ�ۂł͂Ȃ�
								*pCharPos = '\0';
							}

							//�ǂݍ���
							this->m_model[counterReadModel].LoadModel(aStrPath);

							//���Z
							counterReadModel++;
						}
					}
					if (strncmp(&aCode[0], CODE_CHARACTERSET, sizeof CODE_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_CHARACTERSET;
					}
					if (strncmp(&aCode[0], CODE_MOTIONSET, sizeof CODE_MOTIONSET / sizeof(char) - 1) == 0)
					{
						if (counterMotionInfo < MOTIONTYPE_MAX)
						{
							readstat = READSTAT_MOTION_MOTIONSET;
						}
					}
					break;
				case READSTAT_MOTION_CHARACTERSET:		//���f�����擾
					if (strncmp(&aCode[0], CODE_END_CHARACTERSET, sizeof CODE_END_CHARACTERSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_NONE;
					}
					else if (strncmp(&aCode[0], CODE_PARTSSET, sizeof CODE_PARTSSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_PARTSSET;
					}
					else if (strncmp(&aCode[0], CODE_MOVE, sizeof CODE_MOVE / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ړ��ʎ擾
						pSprit = strtok(NULL, " =\n");
						this->m_move = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_JUMP, sizeof CODE_JUMP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�W�����v�ʎ擾
						pSprit = strtok(NULL, " =\n");
						this->m_jump = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_RADIUS, sizeof CODE_RADIUS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//���a�擾
						pSprit = strtok(NULL, " =\n");
						this->m_radius = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_NUM_PARTS, sizeof CODE_NUM_PARTS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�p�[�c���擾
						pSprit = strtok(NULL, " =\n");
						this->m_numParts = atoi(pSprit);
					}
					break;
				case READSTAT_MOTION_PARTSSET:
					if (strncmp(&aCode[0], CODE_END_PARTSSET, sizeof CODE_END_PARTSSET / sizeof(char) - 1) == 0)
					{
						//�擾�������̂���������|�C���^�ɑ��
						this->m_model[idxPartsSet].SetModelSetup(modelstr);

						//�擾�������̂�����
						modelstr = {};

						//�L�����N�^�[�ݒ��Ԃɖ߂�
						readstat = READSTAT_MOTION_CHARACTERSET;
					}
					else if (strncmp(&aCode[0], CODE_INDEX, sizeof CODE_INDEX / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�ԍ��擾
						pSprit = strtok(NULL, " =\n");
						idxPartsSet = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_PARENT, sizeof CODE_PARENT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//�e�ԍ��擾
						pSprit = strtok(NULL, " =\n");
						modelstr.m_IdxModelParent = atoi(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						modelstr.posOffset.x = fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						modelstr.posOffset.y = fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						modelstr.posOffset.z = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						modelstr.rotOffset.x = fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						modelstr.rotOffset.y = fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						modelstr.rotOffset.z = fatof(pSprit);
					}
					break;
				case READSTAT_MOTION_MOTIONSET:
					if (strncmp(&aCode[0], CODE_KEYSET, sizeof CODE_KEYSET / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_END_MOTIONSET, sizeof CODE_END_MOTIONSET / sizeof(char) - 1) == 0)
					{
						counterMotionInfo++;
						counterKeyInfo = 0;
						readstat = READSTAT_MOTION_NONE;
					}
					else if (strncmp(&aCode[0], CODE_LOOP, sizeof CODE_LOOP / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//���[�v�ۓǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_Loop = atoi(pSprit) ? true : false;
					}
					else if (strncmp(&aCode[0], CODE_NUM_KEY, sizeof CODE_NUM_KEY / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//�L�[���ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_numKey = atoi(pSprit);
					}
					break;
				case READSTAT_MOTION_KEYSET:
					if (strncmp(&aCode[0], CODE_KEY, sizeof CODE_KEY / sizeof(char) - 1) == 0)
					{
						readstat = READSTAT_MOTION_KEY;
					}
					else if (strncmp(&aCode[0], CODE_END_KEYSET, sizeof CODE_END_KEYSET / sizeof(char) - 1) == 0)
					{
						counterKeyInfo++;
						counterKey = 0;
						readstat = READSTAT_MOTION_MOTIONSET;
					}
					else if (strncmp(&aCode[0], CODE_FRAME, sizeof CODE_FRAME / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//�t���[�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_Frame = atoi(pSprit);
					}
					break;
				case READSTAT_MOTION_KEY:
					if (strncmp(&aCode[0], CODE_END_KEY, sizeof CODE_END_KEY / sizeof(char) - 1) == 0)
					{
						counterKey++;
						readstat = READSTAT_MOTION_KEYSET;
					}
					else if (strncmp(&aCode[0], CODE_POS, sizeof CODE_POS / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//X���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_PosX = fatof(pSprit);

						//Y���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_PosY = fatof(pSprit);

						//Z���W�ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_PosZ = fatof(pSprit);
					}
					else if (strncmp(&aCode[0], CODE_ROT, sizeof CODE_ROT / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

															//X�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_RotX = fatof(pSprit);

						//Y�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_RotY = fatof(pSprit);

						//Z�����ǂݎ��
						pSprit = strtok(NULL, " =\n");
						this->m_motionInfo[counterMotionInfo].m_aKeyInfo[counterKeyInfo].m_aKey[counterKey].m_RotZ = fatof(pSprit);
					}
					break;
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
	else
	{
		assert(pFile != NULL);
	}
}

//========================
//���[�V�����X�V����
//========================
void cMotionModel::UpdateMotion(void)
{
	//���̃L�[�Ǝ��̃L�[�����Ă���
	int nNowKey = this->m_motion.m_nowKey;
	int nNextKey = this->m_motion.m_nowKey + 1;

	for (int CntModel = 0; CntModel < MAX_MOTION_MODEL; CntModel++)
	{
		if (this->m_model[CntModel].GetModel().m_bUse == true)
		{
			//�I�t�Z�b�g�����Ă���
			this->m_motionPos[CntModel] = this->m_model[CntModel].GetModel().posOffset;
			this->m_motionRot[CntModel] = this->m_model[CntModel].GetModel().rotOffset;

			//�����Z�o
			float posDiffX = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNextKey].m_aKey[CntModel].m_PosX -
				this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_PosX;
			float posDiffY = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNextKey].m_aKey[CntModel].m_PosY -
				this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_PosY;
			float posDiffZ = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNextKey].m_aKey[CntModel].m_PosZ -
				this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_PosZ;
			float rotDiffX = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNextKey].m_aKey[CntModel].m_RotX -
				this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_RotX;
			float rotDiffY = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNextKey].m_aKey[CntModel].m_RotY -
				this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_RotY;
			float rotDiffZ = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNextKey].m_aKey[CntModel].m_RotZ -
				this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_RotZ;

			//�ʒu�����Z�o
			float posDemandX = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_PosX +
				posDiffX * ((float)this->m_motion.m_counterMotion / this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame);
			float posDemandY = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_PosY +
				posDiffY * ((float)this->m_motion.m_counterMotion / this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame);
			float posDemandZ = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_PosZ +
				posDiffZ * ((float)this->m_motion.m_counterMotion / this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame);
			float rotDemandX = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_RotX +
				rotDiffX * ((float)this->m_motion.m_counterMotion / this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame);
			float rotDemandY = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_RotY +
				rotDiffY * ((float)this->m_motion.m_counterMotion / this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame);
			float rotDemandZ = this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_aKey[CntModel].m_RotZ +
				rotDiffZ * ((float)this->m_motion.m_counterMotion / this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame);

			//�p�[�c�̈ʒu�����ݒ�
			this->m_motionPos[CntModel] += D3DXVECTOR3(posDemandX, posDemandY, posDemandZ);
			this->m_motionRot[CntModel] += D3DXVECTOR3(rotDemandX, rotDemandY, rotDemandZ);
		}
	}
	this->m_motion.m_counterMotion++;

	//�Đ��t���[����̋���
	if (this->m_motion.m_counterMotion == this->m_motionInfo[this->m_motion.m_motionType].m_aKeyInfo[nNowKey].m_Frame)
	{//�Đ��t���[�����ɒB������
	 //�J�E���^�[�����Z�b�g���ăL�[������₷
		this->m_motion.m_counterMotion = 0;
		this->m_motion.m_nowKey++;

		//�L�[�̍ő吔�ɒB�����烋�[�v���邩�ۂ��ɉ����čĐݒ肷��
		if (this->m_motion.m_nowKey == this->m_motionInfo[this->m_motion.m_motionType].m_numKey)
		{
			if (this->m_motionInfo[this->m_motion.m_motionType].m_Loop == true)
			{//���[�v������
				this->m_motion.m_nowKey = 0;
			}
			else
			{//�ʏ��NEUTRAL��Ԃɂ���
				this->SetMotion(MOTIONTYPE_HOGE);
			}
		}
	}
}

//========================
//���[�V�����ݒ菈��
//========================
void cMotionModel::SetMotion(MOTIONTYPE type)
{
	if (this->m_motion.m_motionType != type)
	{
		this->m_motion.m_motionType = type;
		this->m_motion.m_nowKey = 0;
		this->m_motion.m_counterMotion = 0;
	}
}

//========================
//���f���`��
//========================
void cMotionModel::DrawMotionModel(D3DXMATRIX *mtxBace)
{
	D3DXMATRIX mtxParent;
	for (int cntModel = 0; cntModel < MAX_MOTION_MODEL; cntModel++)
	{
		if (this->m_model[cntModel].GetModel().m_bUse == true)
		{
			if (this->m_model[cntModel].GetModel().m_IdxModelParent != -1)
			{
				mtxParent = this->m_model[this->m_model[cntModel].GetModel().m_IdxModelParent].GetModel().mtxWorld;
				this->m_model[cntModel].DrawModel(this->m_motionPos[cntModel], this->m_motionRot[cntModel], INIT_ZERO, mtxBace, &mtxParent);
			}
			else
			{
				this->m_model[cntModel].DrawModel(this->m_motionPos[cntModel], this->m_motionRot[cntModel], INIT_ZERO, mtxBace);
			}
		}
	}
}
//==========================================
//
//���f���֌W�v���O����[cModel.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "..\..\Core\Main\main.h"
#include "..\..\Core\File\file.h"
#include "Model.h"

#define fatof(x)				(float)atof(x)										//�ʏ��atof����double�^�ŕԂ��Ă���̂�float�L���X�g���s���悤�ɂ�������

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

//****************************************************
//�P�̃��f��
//****************************************************
//========================
//�R���X�g���N�^
//========================
CModel::CModel()
{
	this->m_cModelStr = {};
}

//========================
//�f�X�g���N�^
//========================
CModel::~CModel()
{
	
}

//========================
//���f��������
//========================
void CModel::Init(void)
{
	this->Release();
}

//========================
//���f���I��
//========================
void CModel::Uninit(void)
{
	this->Release();
}

//========================
//���f���j��
//========================
void CModel::Release(void)
{
	//���b�V���̔j��
	if (this->m_cModelStr.pMesh != NULL)
	{
		this->m_cModelStr.pMesh->Release();
		this->m_cModelStr.pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (this->m_cModelStr.pBuffMat != NULL)
	{
		this->m_cModelStr.pBuffMat->Release();
		this->m_cModelStr.pBuffMat = NULL;
	}
}

//========================
//���f���ǂݍ���
//========================
void CModel::Create(const char* pPath)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	if (SUCCEEDED(D3DXLoadMeshFromX(
		pPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&this->m_cModelStr.pBuffMat,
		NULL,
		&this->m_cModelStr.dwNumMatModel,
		&this->m_cModelStr.pMesh)))
	{
		//�e�N�X�`���ǂݍ���
		D3DXMATERIAL* pMat;	//�}�e���A���|�C���^

		//�}�e���A�����ɑ΂���|�C���^�擾
		pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

		//�e�N�X�`���ǂݍ���
		for (int nCntTex = 0; nCntTex < (int)this->m_cModelStr.dwNumMatModel; nCntTex++)
		{
			if (pMat[nCntTex].pTextureFilename != NULL)
			{
				//�e�N�X�`���ǂݍ���
				D3DXCreateTextureFromFile(pDevice,
					pMat[nCntTex].pTextureFilename,
					&this->m_cModelStr.apTexture[nCntTex]);
			}
		}

		//�g�p���Ă����Ԃɂ���
		this->m_cModelStr.m_bUse = true;
	}
	else
	{
		//�g�p���Ă��Ȃ�
		this->m_cModelStr.m_bUse = false;
	}
}

//========================
//���f���ݒ�
//========================
void CModel::SetModelSetup(ModelStruct modelstr)
{
	this->m_cModelStr.posOffset = modelstr.posOffset;
	this->m_cModelStr.rotOffset = modelstr.rotOffset;
	this->m_cModelStr.m_IdxModelParent = modelstr.m_IdxModelParent;
}

//========================
//�`�揈��
//========================
void CModel::DrawModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXMATRIX *mtxBace, D3DXMATRIX *mtxParent)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans, mtxTexture;	//�v�Z�p
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//���f���擾
	//���[���h�}�g���b�N�X������
	D3DXMatrixIdentity(&this->m_cModelStr.mtxWorld);

	//�g�k�𔽉f
	//D3DXMatrixScaling(&mtxScall, FENCE_SCALE, FENCE_SCALE, FENCE_SCALE);
	//D3DXMatrixMultiply(&g_aFence[nCount].mtxWorld, &g_aFence[nCount].mtxWorld, &mtxScall);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxRot);

	//�ʒu���f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, &mtxTrans);

	//�p�[�c�̐e�}�g���ݒ�
	if (mtxParent != NULL)
	{
		//�p�[�c�̃}�g���Ɛe�}�g�����������킹��
		D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, mtxParent);
	}
	else
	{
		//�p�[�c�̃}�g���ƃx�[�X�}�g�����������킹��
		D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, mtxBace);
	}

	//���[���h�}�g���b�N�X�ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &this->m_cModelStr.mtxWorld);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)this->m_cModelStr.pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)this->m_cModelStr.dwNumMatModel; nCntMat++)
	{
		//�}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, this->m_cModelStr.apTexture[nCntMat]);

		//���f���`��
		this->m_cModelStr.pMesh->DrawSubset(nCntMat);
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

ModelStruct CModel::GetModel(void)
{
	return this->m_cModelStr;
}

//****************************************************
//�������f��
//****************************************************
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
	
}

//========================
//������
//========================
void Init(void)
{
	
}

//========================
//�I��
//========================
void Uninit(void)
{

}

//========================
//���[�V�����r���[���[�̃t�@�C�����擾
//========================
void cMotionModel::Create(const char *pPath)
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
						if (counterReadModel < this->m_numModel)
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
							this->m_model[counterReadModel].Create(aStrPath);

							//���Z
							counterReadModel++;
						}
					}
					if (strncmp(&aCode[0], CODE_NUM_MODEL, sizeof CODE_NUM_MODEL / sizeof(char) - 1) == 0)
					{
						pSprit = strtok(&aCode[0], " =\n");	//�������e�̕�������

						//���f�����擾
						pSprit = strtok(NULL, " =\n");
						this->m_numModel = atoi(pSprit);
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
//���f���j��
//========================
void cMotionModel::Release(void)
{
	for (int cntModel = 0; cntModel < this->m_numParts; cntModel++)
	{
		this->m_model[cntModel].Release();
	}
	this->m_numModel = 0;
}

//========================
//���[�V�����X�V����
//========================
void cMotionModel::UpdateMotion(void)
{
	//���̃L�[�Ǝ��̃L�[�����Ă���
	int nNowKey = this->m_motion.m_nowKey;
	int nNextKey = this->m_motion.m_nowKey + 1;

	for (int CntModel = 0; CntModel < this->m_numParts; CntModel++)
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
	for (int cntModel = 0; cntModel < this->m_numParts; cntModel++)
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
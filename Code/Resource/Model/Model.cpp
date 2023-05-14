//==========================================
//
//���f���֌W�v���O����[cModel.cpp]
//Author:�Ό��D�n
//
//==========================================
#include "Model.h"

//*******************************************************************
//�P�̃��f��
//*******************************************************************
//==========================================
//�R���X�g���N�^
//==========================================
CModel::CModel()
{
	this->m_cModelStr = {};
}

//==========================================
//�f�X�g���N�^
//==========================================
CModel::~CModel()
{

}

//==========================================
//����������
//==========================================
void CModel::Init(void)
{
	this->m_cModelStr = {};
}

//==========================================
//�I������
//==========================================
void CModel::Uninit(void)
{

}

//==========================================
//��������
//==========================================
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

//==========================================
//�j������
//==========================================
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

//==========================================
//�`�揈��
//==========================================
void CModel::DrawModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, D3DXMATRIX *pMtxBace, D3DXMATRIX *mtxParent = NULL)
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
		D3DXMatrixMultiply(&this->m_cModelStr.mtxWorld, &this->m_cModelStr.mtxWorld, pMtxBace);
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

//*******************************************************************
//���[�V�����t�����f��
//*******************************************************************
//==========================================
//�R���X�g���N�^
//==========================================
cMotionModel::cMotionModel()
{
	
}

//==========================================
//�f�X�g���N�^
//==========================================
cMotionModel::~cMotionModel()
{

}

//==========================================
//����������
//==========================================
void cMotionModel::Init(void)
{
	
}

//==========================================
//�I������
//==========================================
void cMotionModel::Uninit(void)
{

}